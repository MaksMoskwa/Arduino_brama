#include <Servo.h>
#include <IRremote.hpp>

Servo serwo1, serwo2;

#define IR_PIN 10
#define POWER 0x00
#define LED 12
#define PIR_PIN 4

// ILE STOPNI MA SIĘ COFNĄĆ po zatrzymaniu (zmień 5 na inną wartość, np. 3-10)
#define COFANIE_STOPNI 5

int pozycja1 = 0, pozycja2 = 180;
int cel1 = 0, cel2 = 180;
int stan = 0, kierunek = 0;

bool ruch = false;

unsigned long czas = 0, przycisk = 0;

// ---------- STANY ----------

// STAN 0 - ZAMKNIETA
void zamknieta() {
  cel1 = 0;
  cel2 = 180;
  stan = 0;
  ruch = false;
}

// STAN 1 - OTWARTA
void otwarta() {
  cel1 = 90;
  cel2 = 90;
  stan = 1;
  ruch = false;
}

// STAN 4 - OTWIERANIE
void otwieranie() {
  cel1 = 90;
  cel2 = 90;
  stan = 4;
  kierunek = 4;
  ruch = true;
}

// STAN 5 - ZAMYKANIE
void zamykanie() {
  cel1 = 0;
  cel2 = 180;
  stan = 5;
  kierunek = 5;
  ruch = true;
}

// STAN 6 - COFNIĘCIE / ZATRZYMANIE
void zatrzymanie() {
  kierunek = (stan == 4) ? 5 : 4;

  // ---------- COFNIĘCIE ----------
  cel1 = pozycja1;
  cel2 = pozycja2;

  // Jeśli otwieraliśmy (kierunek ruchu == 4), cofnij o COFANIE_STOPNI
  // Jeśli zamykaliśmy (kierunek ruchu == 5), cofnij w drugą stronę
  if (kierunek == 4) {
    // otwieraliśmy -> cofnij w stronę zamknięcia
    cel1 = max(0, pozycja1 - COFANIE_STOPNI);
    cel2 = min(180, pozycja2 + COFANIE_STOPNI);
  } else {
    // zamykaliśmy -> cofnij w stronę otwarcia
    cel1 = min(90, pozycja1 + COFANIE_STOPNI);
    cel2 = max(90, pozycja2 - COFANIE_STOPNI);
  }

  ruch = true;   // nadal ruch, aby serwa poszły w stronę cofnięcia
  stan = 6;
}

// ---------- OBSŁUGA POWER ----------

void obslugaPower() {
  if (ruch) {
    zatrzymanie();   // cofnij i zatrzymaj
  }
  else if (stan == 0) {
    otwieranie();
  }
  else if (stan == 1) {
    zamykanie();
  }
  else if (stan == 6) {
    // po cofnięciu: kontynuuj w kierunku, z którego cofnięcie przyszło
    if (kierunek == 4) otwieranie();
    else zamykanie();
  }
}

// ---------- OBSŁUGA PIR ----------

void obslugaPIR() {
  if (digitalRead(PIR_PIN) != HIGH) return;

  if (ruch) {
    zatrzymanie();   // cofnij i zatrzymaj (bezpieczeństwo)
  } else if (stan == 0 || (stan == 6 && kierunek == 5)) {
    otwieranie();    // ktoś podchodzi -> otwórz
  }
}

// ---------- STEROWANIE SERWAMI ----------

void sterowanieSerwami() {
  if (!ruch || millis() - czas < 15) return;

  czas = millis();

  if (pozycja1 < cel1) pozycja1++;
  else if (pozycja1 > cel1) pozycja1--;

  if (pozycja2 < cel2) pozycja2++;
  else if (pozycja2 > cel2) pozycja2--;

  serwo1.write(pozycja1);
  serwo2.write(pozycja2);

  // Kiedy serwa dojadą do celu cofnięcia
  if (pozycja1 == cel1 && pozycja2 == cel2) {
    ruch = false;
    // Stan 6 = cofnięcie zakończone, brama stoi
    // Jeśli PIR nadal aktywny i brama była otwierana -> otwórz ponownie
    // Jeśli PIR był przyczyną -> pozostaw zamkniętą w tej pozycji cofnięcia
  }
}

// ---------- OBSŁUGA PILOTA ----------

void obslugaPilota() {
  if (!IrReceiver.decode()) return;

  if (IrReceiver.decodedIRData.command == POWER &&
      !(IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_REPEAT) &&
      millis() - przycisk > 300) {

    przycisk = millis();
    obslugaPower();
  }

  IrReceiver.resume();
}

// ---------- SETUP ----------

void setup() {
  serwo1.attach(3);
  serwo2.attach(5);

  pinMode(LED, OUTPUT);
  pinMode(PIR_PIN, INPUT);

  serwo1.write(pozycja1);
  serwo2.write(pozycja2);

  IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);
}

// ---------- LOOP ----------

void loop() {
  obslugaPIR();
  obslugaPilota();
  sterowanieSerwami();

  digitalWrite(LED, ruch);
}

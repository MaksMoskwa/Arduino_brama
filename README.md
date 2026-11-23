🚧 Automatyczna brama Arduino – sterowanie pilotem IR i czujnikiem ruchu PIR
📌 Opis projektu

Projekt przedstawia automatyczną bramę sterowaną za pomocą płytki Arduino, dwóch serwomechanizmów, pilota na podczerwień oraz czujnika ruchu PIR.

Brama może być otwierana i zamykana za pomocą pilota IR. Dodatkowo zastosowany czujnik PIR wykrywa zbliżającą się osobę i automatycznie inicjuje otwieranie bramy.

Program posiada również funkcję bezpieczeństwa, która pozwala zatrzymać poruszającą się bramę i cofnąć ją o określoną liczbę stopni.

⚙️ Funkcje projektu
📡 Sterowanie pilotem IR – otwieranie, zamykanie oraz zatrzymywanie bramy.
🚶 Automatyczne otwieranie – czujnik PIR wykrywa ruch i uruchamia otwieranie bramy.
🛑 Funkcja bezpieczeństwa – wykrycie ruchu podczas pracy bramy powoduje zatrzymanie i cofnięcie serwomechanizmów.
↩️ Cofanie po zatrzymaniu – brama cofa się o określoną liczbę stopni, aby ograniczyć ryzyko przytrzaśnięcia przeszkody.
💡 Sygnalizacja LED – dioda informuje o aktualnym ruchu bramy.
🔄 Płynny ruch – serwomechanizmy zmieniają pozycję stopniowo, zamiast wykonywać gwałtowny ruch.
🧰 Wykorzystane komponenty
Komponent	Ilość
Arduino (np. UNO)	1
Serwomechanizm	2
Odbiornik podczerwieni IR	1
Pilot IR	1
Czujnik ruchu PIR (np. HC-SR501)	1
Dioda LED	1
Rezystor do diody LED	1
Przewody połączeniowe	Według potrzeb
🔌 Podłączenie elementów

Poniższa tabela przedstawia przypisanie pinów Arduino zgodnie z programem.

Element	Pin Arduino
Serwomechanizm 1 – sygnał	D3
Serwomechanizm 2 – sygnał	D5
Odbiornik IR – sygnał	D10
Dioda LED	D12
Czujnik PIR – sygnał OUT	D4

Zasilanie:

Serwomechanizmy należy zasilić odpowiednim źródłem napięcia.
Odbiornik IR i czujnik PIR należy zasilić zgodnie z ich specyfikacją.
Przy zastosowaniu zewnętrznego zasilania serwomechanizmów należy połączyć masę zasilacza z masą Arduino (GND).
📚 Wymagane biblioteki

Do poprawnego działania programu wymagane są następujące biblioteki:

Servo.h – obsługa serwomechanizmów.
IRremote.hpp – odbieranie i dekodowanie sygnałów z pilota IR.

Bibliotekę IRremote można zainstalować w Arduino IDE za pomocą Library Manager.

🎮 Obsługa bramy
Sterowanie pilotem

Do sterowania bramą wykorzystywany jest przycisk POWER na pilocie IR.

Aktualny stan bramy	Działanie po naciśnięciu POWER
Zamknięta	Rozpoczęcie otwierania
Otwarta	Rozpoczęcie zamykania
W trakcie otwierania	Zatrzymanie i cofnięcie
W trakcie zamykania	Zatrzymanie i cofnięcie
Po zatrzymaniu	Kontynuowanie wcześniejszego kierunku ruchu

Program ignoruje powtarzające się sygnały pilota i stosuje blokadę czasową 300 ms, aby uniknąć przypadkowego wielokrotnego wywołania funkcji.

Automatyczne sterowanie czujnikiem PIR

Czujnik PIR odpowiada za wykrywanie ruchu w pobliżu bramy.

Gdy brama jest zamknięta i czujnik wykryje ruch, rozpoczyna się otwieranie.
Gdy podczas ruchu bramy czujnik wykryje ruch, brama zatrzymuje się i cofa.
Czujnik nie inicjuje automatycznego zamykania bramy.
🔄 Zasada działania programu

Program wykorzystuje kilka stanów określających aktualne działanie bramy.

Numer stanu	Nazwa	Opis
0	ZAMKNIĘTA	Brama znajduje się w pozycji zamkniętej.
1	OTWARTA	Brama znajduje się w pozycji otwartej.
4	OTWIERANIE	Brama wykonuje ruch w kierunku otwierania.
5	ZAMYKANIE	Brama wykonuje ruch w kierunku zamykania.
6	ZATRZYMANIE	Brama wykonuje cofnięcie i zatrzymuje się.

Serwomechanizmy poruszają się stopniowo. Program aktualizuje ich pozycję co 15 ms, zwiększając lub zmniejszając kąt o jeden stopień.

⚙️ Konfiguracja cofania bramy

Jednym z najważniejszych parametrów programu jest liczba stopni, o którą brama cofa się po zatrzymaniu.

cpp
#define COFANIE_STOPNI 5


Domyślna wartość wynosi 5 stopni.

Można ją dowolnie zmieniać, przykładowo:

3 – niewielkie cofnięcie.
5 – ustawienie domyślne.
10 – większe cofnięcie.

Zmiana tej wartości pozwala dostosować zachowanie mechanizmu do konstrukcji bramy.

💡 Sygnalizacja LED

Dioda LED podłączona do pinu D12 informuje o aktualnym ruchu bramy.

LED świeci – brama jest w ruchu.
LED nie świeci – brama nie wykonuje ruchu.
🚀 Uruchomienie projektu
Podłącz wszystkie elementy zgodnie z tabelą połączeń.
Zainstaluj wymagane biblioteki w Arduino IDE.
Otwórz plik programu .ino.
Wybierz odpowiednią płytkę Arduino oraz port COM.
Wgraj program do mikrokontrolera.
Uruchom układ i sprawdź działanie pilota oraz czujnika PIR.
⚠️ Uwagi dotyczące bezpieczeństwa

Projekt ma charakter edukacyjny i demonstracyjny.

Zastosowany czujnik PIR nie jest certyfikowanym systemem wykrywania przeszkód. Nie gwarantuje wykrycia wszystkich obiektów, a mechanizm cofania sterowany serwomechanizmami nie zastępuje profesjonalnych zabezpieczeń przeciw przytrzaśnięciu.

Przed zastosowaniem w rzeczywistej bramie należy wykorzystać odpowiednie zabezpieczenia mechaniczne, fotokomórki, ograniczniki ruchu oraz niezależny układ awaryjnego zatrzymania.

👨‍💻 Technologie
Arduino / C++
Arduino IDE
Biblioteka Servo
Biblioteka IRremote
Komunikacja podczerwieni IR
Czujnik ruchu PIR

Projekt edukacyjny – automatyczna brama sterowana za pomocą Arduino, pilota IR i czujnika ruchu PIR.

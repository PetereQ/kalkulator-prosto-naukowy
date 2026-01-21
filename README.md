# Kalkulator prosto-naukowy 🧮

![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Qt](https://img.shields.io/badge/Qt-%23217346.svg?style=for-the-badge&logo=Qt&logoColor=white)
![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)
![Windows](https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white)

Uniwersytet Wrocławski: PWI 2025 - Projekt grupowy Zespół 2

Projekt grupowy realizowany w ramach przedmiotu **Podstawowy Warsztat Informatyka** na Uniwersytecie Wrocławskim.

Aplikacja to nowoczesny kalkulator graficzny łączący prostotę obsługi (tryb podstawowy) z funkcjami naukowymi i programistycznymi. Napisany w nowoczesnym C++ z wykorzystaniem frameworka Qt 6.

## 👥 Zespół

- **Piotr Kościelny 354663** - Frontend, UI, Logika interfejsu
- **Barttomiej Kuźma 361997** - Bugfixy przy funkcjach, przesuwanie sie po tekscie
- **Alicja Wiercioch 360189** -
- **Julia Garboś 353775** -
- **Anna Yatsyshyna 263058** -
- **Adam Raczyński 359082** - Integracja logiki obliczen z UI, architektura projektu, UX, bugfixy w calym projekcie

## 📦 Jak uruchomić projekt?

Wykonaj instrukcję dla swojego systemu:

### 🐧 Linux (Terminal)

Pobierz kod z GitHuba (np. używając `git clone`), a następnie upewnij się, że masz zainstalowane biblioteki Qt6 i CMake.

`sudo apt install qt6-base-dev cmake build-essential`

**Kompilacja i uruchomienie:**

1. Otwórz terminal w folderze projektu.
2. Wykonaj komendy:

   `mkdir build`

   `cd build`

   `cmake ..`

   `make`

   `./kalculator`

### 🚀 Windows (Plik .zip)

Jeśli chcesz tylko korzystać z kalkulatora (bez instalowania środowiska programistycznego):

1. Przejdź do zakładki **[Releases](../../releases)** (po prawej stronie na GitHubie).
2. Pobierz najnowszy plik `.zip` (`kalkulator_final.zip`).
3. **Wypakuj całe archiwum** do dowolnego folderu (Ważne! Nie uruchamiaj bezpośrednio z ZIP-a).
4. Znajdź i uruchom plik `kalculator.exe`.

> **Uwaga:** Aplikacja działa w trybie "Portable" – nie wymaga instalacji, ale plik `.exe` musi znajdować się w tym samym folderze co towarzyszące mu pliki `.dll`.

### 🪟 Windows (2 opcja, z użyciem środowiska Qt)

1. Pobierz kod z GitHuba. (np. używając `git clone`)
2. Pobierz i zainstaluj **Qt Creator** (Open Source).
3. Wybierz opcję **"Otwórz projekt"** i wskaż plik `CMakeLists.txt` z tego folderu.
4. Kliknij zielony trójkąt (Run).

## 💡 Funkcjonalności

### 🧮 Matematyka

- **Podstawowe:** +, -, \*, /.
- **Trygonometria:** sin, cos, tan, ctg (obsługa w stopniach).
- **Potęgi i Pierwiastki:** x², xⁿ, √, ⁿ√.
- **Logarytmy:** log (dziesiętny), ln (naturalny).
- **Nawiasy:** Obsługa kolejności działań ( ).

### 💻 Informatyka

- **Konwersja BIN:** Zamiana liczb całkowitych na system binarny.

### 🎨 Interfejs (UI/UX)

- **Dark Mode:** Ciemny motyw przyjazny dla oczu.
- **Responsywność:** Okno skaluje się, a przyciski dopasowują rozmiar.
- **Live Calc:** Wynik obliczany na żywo w trakcie wpisywania (w miarę możliwości).
- **Historia:** Przycisk = przepisuje wynik do pola edycji dla dalszych obliczeń.

## ⌨️ Skróty klawiszowe

Aplikacja jest w pełni obsługiwana z klawiatury fizycznej:

| Klawisz                   | Akcja                                      |
| :------------------------ | :----------------------------------------- |
| `0-9`, `+`, `-`, `*`, `/` | Wprowadzanie cyfr i znaków działań         |
| `(`, `)`                  | Wprowadanie nawiasowania                   |
| `Enter`                   | Oblicz wynik (`=`)                         |
| `Backspace`               | Usuń ostatni znak (`DEL`)                  |
| `Esc`                     | Wyczyść wszystko (`C`)                     |
| `.` (kropka)              | Wstawia przecinek (działa zamiennie z `,`) |
| `^`                       | Potęgowanie                                |
| `P`                       | Podnoszenie do kwadratu                    |
| `S`                       | Sinus                                      |
| `C`                       | Cosinus                                    |
| `T`                       | Tangens                                    |
| `Shift+T`                 | Cotangens                                  |
| `^`                       | Potęgowanie                                |
| `Shift+L`                 | Logarytm naturalny                         |
| `L`                       | Logarytm                                   |
| `Shift+B`                 | Zamiana na system binarny                  |
| `Shift+S`                 | Pierwiastek kwadratowy                     |
| `F1`                      | Funkcja 1                                  |
| `F2`                      | Funkcja 2                                  |
| `F3`                      | Funkcja 3                                  |
| `^`                       | Potęgowanie                                |
## 🛠️ Technologie

- **Język:** C++17
- **GUI:** Qt Widgets 6.x
- **Build System:** CMake
- **IDE:** Qt Creator

© 2025 Zespół 2 - Instytut Informatyki Uniwersytetu Wrocławskiego

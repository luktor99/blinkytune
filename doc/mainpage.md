# BlinkyTune

<p align="center">
<img src="../blinkytune_big.png">
</p>

## Autorzy
Łukasz Kilaszewski (259822)<br />
Marcin Baran (Z59804)

## Opis projektu
BlinkyTune to aplikacja, która na podstawie analizy strumienia audio kontroluje pasek adresowalnych diod LED RGB.
Kolory poszczególnych diod dobierane są w taki sposób, aby generować ciekawe efekty świetlne, zsynchronizowane np. z odtwarzaną aktualnie muzyką.
Użytkownik ma możliwość wyboru źródła analizowanego dźwięku, jednego z dostępnych efektów, a także wartości jego ustawień.
Każdy efekt posiada indywidualny zbiór parametrów, które wpływają na jego zachowanie.
Urządzenie, odpowiadające za wyświetlanie efektów świetlnych, złożone jest z paska 60 diod LED WS2812B, podłączonych do modułu opartego o układ Espressif ESP8266.
Układ ten umożliwia podłączenie urządzenia do domowej sieci WiFi, a następnie komunikację z komputerem za pomocą protokołu UDP.
Wykorzystanie łączności bezprzewodowej pozwala na wyświetlanie efektów z dala od komputera.
Program dla modułu ESP8266, odpowiadający za odbieranie danych od aplikacji i sterowanie paskiem LED, nie wchodzi w skład projektu.

## Interfejs użytkownika
TODO

## Zasada działania
### Protokół komunikacji z paskiem LED
Do przesyłania danych o składowych kolorów poszczególnych diod LED wykorzystywany jest protokół UDP.
Pojedyncza ramka, stanowiąca podstawę działania systemu komunikacji, ma następującą strukturę:
| Dioda LED 1 | Dioda LED 2 | ... | Dioda LED N |
|:---:|:---:|:---:|:---:|
|<span style="color:red">Red</span> <span style="color:green">Green</span> <span style="color:blue">Blue</span> (3 bajty)|<span style="color:red">Red</span> <span style="color:green">Green</span> <span style="color:blue">Blue</span> (3 bajty)| ... |<span style="color:red">Red</span> <span style="color:green">Green</span> <span style="color:blue">Blue</span> (3 bajty)|

Łącznie pojedyncza ramka ma `3*N` bajtów, gdzie `N` to liczba diod LED w pasku. Ramka ta reprezentuje pojedynczą klatkę animacji.

### Przetwarzanie dźwięku
W celu wyznaczenia interesujących cech dźwięku, na podstawie których można generować efekty, program wykonuje szereg czynności:
- pobieranie próbek audio z wybranego urządzenia audio
- wyznaczanie widma przechwyconego sygnału audio
- filtracja i analiza widma

Za czynności te odpowiadają osobne wątki, które wymieniają ze sobą dane za pomocą kolejek FIFO. Próbki audio przetwarzane są przez wątki potokowo.
Osobno przekazywane są dane dla lewego i prawego kanału audio. Ich ewentualne połączenie następuje dopiero podczas generowania konkrentego efektu świetlnego.

#### Akwizycja próbek audio
Pobieranie próbek odbywa się w wątku obsługiwanym przez klasę SamplesCollector. Interfejs biblioteki PortAudio umożliwia synchroniczne pobieranie buforów zawierających najnowsze próbki.
Wątek przekazuje pobrane próbki do kolejnego, wyznaczającego widmo, za pomocą kolejki FIFO łączącej oba wątki.

#### Wyznaczanie widma
Po odebraniu próbek audio z kolejki FIFO, wątek SpectrumGenerator wywołuje funkcje biblioteki kfr umożliwiające wyznaczenie widma sygnału za pomocą szybkiej transofrmaty Fouriera (FFT - ang. Fast Fourier Transform).
Po wyznaczeniu pierwotnego widma następuje jego przetworzenie na skalę [mel](https://pl.wikipedia.org/wiki/Mel_(skala)). Dzięki temu zabiegowi, kolejne częstotliowści rozmieszczone w widmie są odbierane przez człowieka jako liniowo narastające, co poprawia wizalną jakość generowanych efektów.
Tak przetworzone widmo sygnału trafia poprzez kolejkę FIFO do kolejnego wątku, dokonującego analizy.

### Analiza widma
Wątek SpectrumAnalyzer wyznacza na podstawie widma i próbek takie parametry, jak:
- głośność sygnału (jako chwilowa energia)
- średnia głośność sygnału (jako średnia energia), na podstawie przechowywanej historii danych
- dominujące częstotliwości w widmie
- zgrupowane amplitudy dla tonów niskich, średnich i wysokich

W celu poprawienia płynności efektów, wątek ten filtruje też widmo, aplikując wygładzanie wykładnicze do każdej z wartości amplitud widma lewego i prawego kanału.
W celu wyznaczenia amplitud tonów niskich, średnich i wysokich widmo dzielone jest na 3 części, a następnie dla każdej części obliczana jest średnia amplituda.

Wyznaczone wartości wysyłane są poprzez kolejkę FIFO do wątku generującego efekty.

### Generowanie efektów
Generowanie efektów odbywa się w wątku obsługiwanym przez klasę EffectsRenderer.
Odbiera ona z kolejki FIFO dane dotyczące analizy sygnału audio, a następnie wykonuje operacje na pasku LED zależne od wybranego efektu.
W przypadku efektów niezależnych od dźwięku, dane analizy audio nie są wykorzystywane.

### Zarządzanie potokiem generowania efektów
Za zarządzanie aktywnym efektem odpowiada klasa EffectsController, stanowiaca fasadę całego systemu generowania efektów.
Każdy z efektów przypisany jest do jednej z grup efektów, reprezentowanych przez odpowiednie klasy abstrakcyjne:
- efekty zależne od dźwięku (klasa SoundEffect)
- efekty niezależne od dźwięku (klasa NoSoundEffect)

W zależności od typu wybranego efektu, klasa startuje jedną z grup wątków stanowiących kompletny potok generowania efektów:
- SamplesCollector, SpectrumGenerator, SpectrumAnalyzer, EffectsRenderer (dla efektów o klasie bazowej SoundEffect)
- TickGenerator, EffectsRenderer (dla efektów o klasie bazowej NoSoundEffect)

Klasa TickGenerator, wraz ze swoim wątkiem, odpowiada za cykliczne wstawianie do wejściowej kolejki FIFO wątku EffectsRenderer pustych buforów, reprezentujących "fałszywą" (pustą) analizę audio.
Dzięki temu, w przypadku, gdy wybrany jest efekt z rodziny NoSoundEffect, nie są pobierane, ani przetwarzane próbki audio, aby nie marnować zasobów.
Puste bufory odebrane z kolejki są przez klasę EffectsRenderer ignorowane - napływające bufory stanowią tylko podstawę czasu dla generowania efektów niezależnych od dźwięku.

## Wykorzytane techniki i wzorce projektowe
Program korzysta między innymi z następujących wzorców projektowych:
- singleton (klasy AudioInterface, EffectsController, EffectsFactory)
- fabryka obiektów (klasa EffectsFactory)
- fasada (klasa EffectsController)
- monitor (klasa FIFOQueue)
- adapter (UDPSender)

Oprócz tego wykorzystywane są zaawansowane elementy języka C++, takie jak:
- klasy szablonowe (klasa FIFOQueue)
- wielowątkowość (np. klasy SamplesCollector, SpectrumGenerator)
- hierarchiczne dziedziczenie (rodzina klas Effect)

## Statystyki
- liczba linii kodu (obliczona za pomocą narzędzia [SLOCCount](https://www.dwheeler.com/sloccount/)): 1990
- liczba testów jednostkowych: 5
- liczba godzin pracy nad projektem: ~150

## Napotkane problemy i dalszy rozwoju projektu
Podczas implementacji programu napotykaliśmy głównie problemy związane z szeroko pojętą tematyką cyfrowego przetwarzania sygnałów.
Projekt pozwolił na dogłebne zapoznanie się z transformatą Fouriera oraz filtracją sygnałów.

Planowany jest dalszy rozwój programu, w tym między innymi:
- dodanie większej ilości efektów
- wykorzystanie bardziej zaawansowanych algorytmów analizy dźwięku (np. wykrywanie uderzeń, tempa)

Aktualnie zaimplementowane funkcjonalności nie wykazują żadnych widocznych problemów z wydajnością lub stabilnością.
Z tego względu, program zaimplementowany w ramach projektu stanowi dobrą bazę do dalszego rozwoju umiejętności autorów.

## Budowanie projektu

Projekt korzysta z następujących bibliotek:

- portaudio: [Portaudio](http://www.portaudio.com/)
- kfr: [kfr](https://www.kfrlib.com/)
- Qt5: [Qt5](https://www.qt.io/)
- Boost (version >= 1.34.0) [Boost](http://www.boost.org/)

Źródła bibliotek Portaudio i kfr są dołączone do repozytorium.
Pozostałe biblioteki muszą zostać manualnie zainstalowane w systemie.

### Zależności projektu:

#### Linux:

- GCC (wersja obsługująca standard C++14)
- CMake (wersja >= 3.5)
- Git

#### Windows:

- Microsoft Visual C++ (wersja >= Visual Studio 2015 Update 2)
- CMake (wersja >= 3.5)
- Git

### Kompilacja

#### Linux:

```
git clone --recursive https://github.com/luktor99/blinkytune.git
mkdir cmake-build
cd cmake-build
cmake -DQt5_DIR=/path/to/Qt5 ..
make -j 4
```

#### Windows:

Należy wykonać następujące polecenia w Visual Studio Command Prompt:

```
git clone --recursive https://github.com/luktor99/blinkytune.git
mkdir cmake-build
cd cmake-build
cmake -G "Visual Studio 14 2015" -DQt5_DIR=C:\path\to\Qt5 ..
msbuild blinkytune.sln
```





# Fejlesztői dokumentáció

## Install

Linux:

- Fel kell telepíteni az ncurses csomagot (`libncurses5-dev` & `libncurses6`)
- `make all`
- a futtatható fájl neve: `main`

Windows: MinGW-vel kell varázsolni, de a lépések kb. ugyan azok (pontos leírás később)

## Kódbázis

### Main

Itt inicializáljuk a `curses` könyvtárat.

Innen hívjuk meg a menüt, aminek visszatérési értéke meghatározza a feladatot, amit cél függvények dolgoznak fel.

### Menu

```c
int show_menu(char **menu_items, int items_n, int border_size);
```

Megjeleníti  menüt.

`char **menu_items` : A menüelemek nevei

`int items_n` : A menüelemek száma

`int border_size` : Keret méret karakterhosszban. (Érdemes kettővel oszthatót választani.)

### File

```c
Pattern *load_file();
```
Bekér egy fájlnevet (Pl.: glider.txt) ellenőrzi fájl a tartalmát (static bool file_valid) majd betölti azt egy új `Pattern` struktúrába, amivel visszatér.

```c
void save_pattern(Pattern *pattern);
```
Bekér egy nevet, ami a fájlnév ([név].txt), és a fájlon belül a pattern neve lesz. (!Name: [név])

### Status

```c
void print_status(Statustype message_type, char *message);
```
`Statustype message_type` : 4 lehetőség van: `error`, `warning`, `info`, `succesful`. Színeket állít be.

`char *message` : A megjelenítendő üzenet

```c
void init_status();
```
Egyszer, a curses színek (`start_color()`) inicializálása után kell meghívni, színeket, színpárokat állít be.

### Input

```c
char *get_input(char *message);
```
Bekér egy string-et a felhasználótól, amit dinamikusan lefoglalt területen visszaad a hívónak.

Használat után a string tömböt fel kell szabadítani memóriaszivárgás elkerülése végett.

### Pattern

```c
void free_pattern(Pattern *pattern);
```

Felszabadítja a `Pattern` struktúra dinamikusan lefoglalt elemeit, illetve magát a struktúrát

### Play

```c
void play_pattern(Pattern *pattern);
```

Megnyitja a pattern-t, és megjeleníti.

[To be continued...👷
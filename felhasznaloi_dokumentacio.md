# Felhasználói dokumentáció

## A program futása

Indításkor az alábbi menüpontok közül választhat:
| Menüpont     | Leírás                    |
| ------------ | ------------------------- |
| New pattern  | Új élettér létrehozása    |
| Load pattern | Élettér betöltése fájlból |
| Play         | Élettér "lejátszása"      |
| Edit         | Élettér Módosítása        |
| Save         | Élettér mentése fájlba    |
| Exit         | Kilépés a programból      |

### New pattern

- Adja meg az élettér nevét
- Adja meg az élettér méreteit (magasság, szélesség)

### Load pattern

- Adja meg a betöltendő élettér fájl nevét (Pl.: glider.txt)

### Play

#### Módok:
-  Folyamatos:
Minden másodpercben `n`-szer lépünk. A lejátszás sebessége lépés/másodperc-ben adható meg.
**Minimum 1 lépés/másodperc.**

- Lépésenkénti:
A `space` gomb megnyomása esetén megteszünk egy lépést.

#### Gombok:

`space` :

- Ha a lejátszó lépésenkénti üzemmódban van: a lejátszó lép egy generációt.
- Ha a lejátszó folyamatos üzemmódban van: megállítja/elindítja a lejátszást.
  
---

`c` :
- A lejátszót a folyamatos és lépésenkénti üzemmódok között állítja.

---

A folyamatos lejátszás sebességét 1 lépés/másodperc-cel:

- `Felfelé nyíl`: Növeli
- `Lefelé nyíl`: Csökkenti
  
---

`x` :

1. A grafikus felület bezárul,
2. Vissza tér a főmenübe a módosított élettérrel

### Edit

[később 👷]

### Save

- Adja meg az élettér nevét, ami a mentés fájl neve is lesz. (Pl.: Glider)

### Exit

Kilépés a programból.

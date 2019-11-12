# Specifikáció

Az életjáték szabályai szerint működő programot kell készíteni.

## Szabályok/fogalmak

Adott egy 2 dimenziós rács (ezt hívjuk élettérnek)
Az élettér választható méretű.

Egy cellának két állapota lehet: Élő vagy Halott.
Egy cellának 8 szomszédja van. (Tehát a sarokkal érintkező cella is szomszédos cellának számít)

Egy állapotát az élettérnek generációnak is lehet nevezni.

Egy következő generációbeli cella állapotát a jelenlegi generációbeli szomszédos cellák határozzák meg.

A John Conway nevével fémjelzett, implementálandó szabályrendszer a következő:
Ha a jelenlegi cella ÉL és a szomszédos cellák közül:

- kevesebb mint 2 él, vagy 3-nál több él, a jelenlegi cella meghal.
- 2 vagy 3 él, a jelenlegi cella élve marad.

Ha a jelenlegi cella HALOTT, de a szomszédos cellák közül:

- pontosan 3 él, a jelenlegi cella élővé változik.

Ha az élettér választható méretű, vannak határai. Mivel Conway végtelen méretűre tervezte a "játékot", erre nincs hivatalos szabály. Tegyük fel hogy az életteren kívül nincs élet, tehát a szélső cellák élettéren kívül eső szomszédai mindig halottak.

## A program futása

Indításkor a felhasználó választhat hogy:

- új életteret szeretne létrehozni
- már létező tervet szeretne beolvasni.

Ha új életteret szeretne létrehozni a felhasználó, meg kell kérdezni hogy mekkora legyen az élettér. Alapértelmezetten, az összes cella halott.

### Ha az élettér betöltésre került:

A program alapvetően három dolgot tud csinálni a beolvasott életterekkel:

- Módosítani
- Lejátszani
- Menteni

Ez mondható a program főmenüjének.

Van még egy opció, új élettér betöltése/létrehozása. Ezzel a program az indítási alapállapotába kerül vissza.

A felhasználótól meg kell kérdezni minden életteret módosító funkció futattása előtt hogy el akarja-e menteni a jelenlegi állapotot, kivéve ha az élettér éppen most lett betöltve egy mentett fájlból.

## Módosítás

Úgy módosítható egy élettér, hogy:

1. Megjelenítjük azt egy grafikus felületen
2. Ha rákattint a felhasználó egy cellára, megváltozik az állapota ( halott -> élő / élő -> halott )

### Gombok:

`x` gombnyomásra:

1. A grafikus felület bezárul,
2. Vissza tér a főmenübe a módosított élettérrel

## Lejátszás:
Grafikus felületen meg kell jeleníteni az életteret.

Egy lépés azt jelenti, hogy az élettéren egyszer elvégezzük a szabályrendszer által előírt műveleteket.

### Módok:
-  Folyamatos:
Minden másodpercben `n`-szer lépünk. A lejátszás sebessége lépés/másodperc-ben adható meg.
**Minimum 1 lépés/másodperc.**

- Lépésenkénti:
A `space` gomb megnyomása esetén megteszünk egy lépést.

### Alaphelyzet:
1 lépés/mp, lépésenkénti üzemmód.

### Gombok:

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

## Mentés
A programbba betöltött életteret el lehet menteni `plaintext` formátumban.

1. Meg kell kérdezni hogy mi legyen az élettér neve. (Ez lesz a fájl név is.)
2. El kell menteni az életteret a programmal azonos mappába.

## Beolvasás
A programba be lehet tölteni életteret `plaintext` formátumban.

1. Meg kell kérdezni a felhasználót az élettér-fájl helyéről
2. Be kell olvasni a programba a fájl tartalmát a formátum szerint.

## Plaintext formátum

Az élettereket importálni, exportálni txt formátumban lehet.

- Az első sor tartalmazza az élettér nevét.

```
!Name: [élettér neve]
```

- A többi sor ha `!` jellel kezdődik, figyelmen kívül lehet hagyni ( = kommentek, leírások )
- Az élő cellák `O` (nagy o)-val, a halott cellák `.`-al vannak jelölve.
- Ha más hibás karaktert talál a beolvasó, hibát kell visszaadnia a funkciónak.   
- Az élettér szélessége akkora, mint az első sor hossza.
- Az élettér hossza akkora, ahány nem `!`-jellel jelölt sora van.

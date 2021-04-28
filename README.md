# HA 1 Fabian Bär, Marco Naumann

Abdunkeln und Aufhellen wird erreicht, in dem der Helligkeitswert jedes Pixels mit einer Zahl multipliziert wird.
Diese errechnet sich aus dem input Parameter: `Multiplikator = (heller+100)/100`. (bei eingabe -100 ist er 0, bei 0 ist er 1 und bei 100 ist er 2, ...)  

Falls der Helligkeitswert nach der Multiplikation größer als 255 ist, wird die Sättigung verringert und der Helligkeitswert auf 255 gesetzt.
Die verringerung der Sättigung erfolgt durch division: `neueSättigung = neueSättigung/( helligkeitswert/255 )` (Die Sättigung wird zum Beispiel halbiert, wenn der helligkeitswert doppelt so groß ist, wie er eigentlich sein darf). Durch die Entsättigung nähert sich die Farbe immer mehr an Weiß an.

## Compillieren:

`make`

## Programmaufruf:

`./helligkeit.out DATEINAME_BILD aufhellungszahl`

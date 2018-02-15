#include <stdio.h>

typedef enum {Angeln, Suchen, Exit} Auswahl;

/* Addressen von Array bei Verschiebung von 0,0 in die Mitte:
[-1,-1] [+0,-1] [+1,-1]
[-1,+0] [+0,+0] [+1,+0]
[-1,+1] [+0,+1] [+1,+1]

Daraus ergeben sich folgende Quadranten:

      -----> +x
   N-W   |   N-E    
  x = -  |  x = +   |
  y = -  |  y = -   |
------------------- |
  x = -  |  x = +   V
  y = +  |  y = +   +y
   S-W   |   S-E

*/
// Quadranten nach obiger Regel
struct Quadrant {
    int x;
    int y;
};

const struct Quadrant NW = {-1, -1};
const struct Quadrant NE = {+1, -1};
const struct Quadrant SW = {-1, +1};
const struct Quadrant SE = {+1, +1};

/* * Funktion max
 * Gibt den größeren der beiden Parameter zurück, oder j, falls i == j.
 * 
 * @param i Eine Zahl
 * @param j Eine weitere Zahl
 * @return Die größere der beiden Zahlen, oder j
 */ 
float max(double i, double j)
{
    return i > j ? i : j;
}

/* * Funktion min
 * Gibt den kleineren der beiden Parameter zurück, oder j, falls i == j.
 * 
 * @param i Eine Zahl
 * @param j Eine weitere Zahl
 * @return Die kleinere der beiden Zahlen, oder j
 */ 
float min(double i, double j)
{
    return i < j ? i : j;
}

/* * Funktion clear_stdin
 * Löscht alle verbleibenden Zeichen bis zum nächsten Zeilenumbruch (einschließlich) aus stdin.
 * 
 * @return Die Anzahl an Zeichen, die entfernt wurden.
 */
int clear_stdin()
{
    int removed = 0;
    while (getchar() != '\n')
        removed++;
    return removed;
}

/* * Funktion placeFish
 * Entscheidet, ob an der Position i, j ein Fisch platziert werden soll.
 * 
 * @param size Die gesamtgröße des Arrays
 * @param i Zeile
 * @param j Spalte
 * @param fish Die Anzahl der verbleibenden Fische, welche im Teich verteilt werden sollen
 * 
 * @return 0 falls erfoglreich, 1 bei fish > rows*5
 */
int placeFish(int size, int i, int j, int fish)
{
    // Die absolute position von i, j ergibt sich aus reihe(i)*länge_jeder_Zeile(5) + position_in_Zeile(j)
    int position = i*5 + j;
    // Wenn alle Fische platziert wurden, dann gib falsch zurück
    if (fish == 0)
        return 0;
    // An jeder zweiten Stelle platziere einen Fisch
    if (position % 2)
        return 1;
    // Wenn die verbleibenden Fische nicht mehr in die Hälfte aller verbleibenden Felder passen, platziere zusätzlichen Fisch.
    if (fish > (size - position) / 2)
        return 1;
    return 0;
}

/* * Funktion initPond
 * Füllt ein Array der Größe rows,5 mit n=fish Fischen.
 * 
 * @param pond Das Array, welches zu füllen ist
 * @param rows Die Anzahl der Zeilen des Arrays
 * @param fish Die Anzahl der Fische, welche im Teich verteilt werden sollen
 * 
 * @return 0 falls erfoglreich, 1 bei fish > rows*5
 */
int initPond(int pond[][5], int rows, int fish)
{
    int i, j, size = rows*5;
    // Wenn fish > Größe des Arrays -> Fehler
    if (fish > size)
        return 1;
    
    // Durch gesamtes Array iterieren
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < 5; j++)
        {
            if (placeFish(size, i, j, fish))
            {
                // Fisch platzieren und Anzahl der verbleibenden Fische um 1 verringern
                pond[i][j] = 1;
                fish--;
            }
            else
                pond[i][j] = 0;
        }
    }
    return 0;
}

/* * Funktion menu
 * Druckt ein Menu, wartet auf eine gültige Benutzereingabe und gibt diese zurück.
 * 
 * @return Eine gültige Benutzereingabe aus Auswahl.
 */
Auswahl menu(void)
{
    int auswahl = 0;
    // Bei gültiger Eingabe kehrt die Funktion zurück
    while (1)
    {
        // Menu anzeigen
        printf("(1) Angel auswerfen\n");
        printf("(2) Fische suchen\n");
        printf("(3) Exit\n");
        printf("Auswahl: ");
        // Benutzereingabe
        scanf("%d", &auswahl);
        // Inputbuffer leeren
        clear_stdin();
        // Eingabe verarbeiten
        switch (auswahl)
        {
            case 1:
                return Angeln;
            case 2:
                return Suchen;
            case 3:
                return Exit;
            // Keine gültige Eingabe -> Fehler ausgeben.
            default:
                printf("Bitte eine Gültige Auswahl treffen!\n");
        }
    }
}

/* * Funktion search
 * Gibt das Teich-Array aus. Fische werden hierbei durch ein 'F', leere Felder durch ein '-' gekennzeichnet.
 * 
 * @param pond Das Array, welches auszugeben ist.
 * @param rows Die Anzahl der Zeilen des Arrays
 * 
 * @return Die verbleibende Anzahl an Fischen.
 */
int search(int pond[][5], int rows)
{
    // Gesamtzahl an Fischen, startet bei 0
    int total = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            // Wenn an i, j ein Fisch ist, gib 'F' aus und erhöhe total. Sonst, gib '-' aus.
            if (pond[i][j])
            {
                printf("F");
                total++;
            }
            else
                printf("-");
        }
        // Zeilenumbruch nach jeder Zeile des Arrays
        printf("\n");
    }
    return total;
}

/* * Funktion direction
 * Fragt die Richtung ab und gibt ein struct Quadrant zurück, welches den Quadranten repräsentiert
 *
 * @return Quadrant {x, y}
 */
struct Quadrant direction()
{
    char _1 = ' ', _2 = ' ';
    // Bei gültiger Eingabe kehrt die Funktion zurück
    while (1)
    {
        printf("Bitte Himmelsrichtung eingeben (NW, NE, SW, SE): ");
        // Benutzereingabe einlesen
        // Beispiel: Eingabe von "nW\n" resultiert in: _1 = n, _2 = W
        _1 = getchar();
        _2 = getchar();
        // Inputbuffer leeren
        clear_stdin();
        if (_1 == 'n' || _1 == 'N')
        {
            // North...
            // ... West
            if (_2 == 'w' || _2 == 'W')
                return NW;
            // ... East
            if (_2 == 'e' || _2 == 'E')
                return NE;
        }
        else if (_1 == 's' || _1 == 'S')
        {
            // South...
            // ... West
            if (_2 == 'w' || _2 == 'W')
                return SW;
            // ... East
            if (_2 == 'e' || _2 == 'E')
                return SE;
        }
    }
}

/* * Funktion fish
 * Fragt den Benutzer nach einer Richtungsangabe und versucht dort zu Angeln.
 * 
 * @param pond Das Array, welches auszugeben ist.
 * @param rows Die Anzahl der Zeilen des Arrays
 * 
 * @return Die verbleibende Anzahl an Fischen.
 */
int fish(int pond[][5], int rows)
{
    // Gesamtzahl an Fischen, startet bei 0
    int total = 0, done = 0;
    // Quadranten aus Benutzereingabe holen
    struct Quadrant q = direction();

    // Größe des Quadranten berechnen:
    float size_x = 5/2.0f;
    float size_y = rows/2.0f;

    // Linken und rechten Rand berechnen:
    float x_min = size_x + size_x * q.x;
    float x_max = max(x_min, size_x);
    x_min = min(x_min, size_x);
    
    // Unteren und oberen Rand berechnen:
    float y_min = size_y + size_y * q.y;
    float y_max = max(y_min, size_y);
    y_min = min(y_min, size_y);
    
    for (float i = y_min; i < y_max && i < rows && !done; i++)
    {
        for (float j = x_min; j <= x_max && j < 5 && !done; j++)
        {
            if (pond[(int) i][(int) j])
            {
                pond[(int) i][(int) j] = 0;
                done = 1;
                printf("Fisch gefangen:!\n");
            }
        }
    }
    if (!done)
        printf("Leider keinen fisch gefangen!\n");
    
    // Verbleibende Fische zählen ...
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < 5; j++)
            total += pond[i][j];
    // ... und zurückgeben
    return total;
}

/* * Funktion main, Hauptroutine
 *
 *
 * return 0 falls erfolgreich, 1 bei Fehlern.
 */
int main(void)
{
    // Teich Array deklarieren (größe 5x4, wie im Beispiel)
    int pond[4][5];
    // Teich Array initialisieren
    if (initPond(pond, 4, 12))
    {
        printf("Fehler beim initialisieren des Teiches!");
        return 1;
    }

    while (1)
    {
        switch (menu())
        {
            case Angeln:
            {
                // Falls keine Fische mehr im Teich sind wird die Ausführung beendet.
                if (!fish(pond, 4))
                {
                    printf("Alle Fische wurden gefangen!\n\n");
                    return 0;
                }
                break;
            }
            case Suchen:
            {
                search(pond, 4);
                break;
            }
            case Exit:
            {
                // Programmausführung beenden
                printf("Programm wird beendet.\n\n");
                return 0;
            }
        }
    }
}
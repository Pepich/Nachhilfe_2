#include <stdio.h>

int existiert(char *datei)
{
  // Struct "FILE", siehe C | Struct -> Komplexer Datentyp -> Pointer
  FILE *file;
  // 
  if ((file = fopen(datei, "r")) != NULL)
    {
      fclose(file);
      return 1;
    }
  return 0;
}

int vergleiche(char *datei1, char *datei2)
{
  // Wenn Fehler -> -1 zurückgeben

  // Prüfe ob existiert datei1
  if (!existiert(datei1))
    return -1;
  // Prüfe ob existiert datei2
  if (!existiert(datei2))
    return -1;
  
  // Zählvariable für Anzahl treffer
  int treffer = 0;
  // Beide Dateien existieren -> Dateien öffnen und einlesen
  
  // Übereinstimmungen zählen (Abbruch bei erstem "Fehler")

  // Übereinstimmungen zurückgeben
  return treffer;
}

int main(void)
{
  char datei1[] = "/Users/Pepich/Datei1";
  char datei2[] = "/Users/Pepich/Datei2";
  int vergleich1 = vergleiche(datei1, datei2);
  printf("Vergleich ergibt: %d\n\n", vergleich1);
  return 0;
}

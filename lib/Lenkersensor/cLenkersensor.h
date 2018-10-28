/*  Autor: Julian Schweizerhof
    Name: cLenksensor.h */



////////////// global h //////////////
const unsigned char pinPoti = 4;  // Pin Definition
struct lenkerDaten  // Struct mit Daten für den Lenker
{
  float lenkwinkel; // Winkel des Lenkers in °, in der Mitte: 0, nach links: positv, nach rechts: negativ
  float lenkgeschwindigkeit;  // Winkelgeschwindigkeit in °/s, nach links: positv, nach rechts: negativ
  float lenkbeschleunigung; // Winkelbeschleunigung °/s², nach rechts: positv, nach rechts: negativ
};
const unsigned int lenksensor_anzahl = 1; // Anzahl an Messwerten für die Glättung
const unsigned char lenksensor_anzahl_loeschen = 0; // Anzahl an Werten die je oben und unten ausgeworfen werden

void quickSort(float  arr[], int left, int right) { // Quelle: http://www.algolist.net/Algorithms/Sorting/Quicksort
  int i = left, j = right;
  float tmp;
  float pivot = arr[(left + right) / 2];
  /* partition */
  while (i <= j) {
    while (arr[i] < pivot)
      i++;
    while (arr[j] > pivot)
      j--;
    if (i <= j) {
      tmp = arr[i];
      arr[i] = arr[j];
      arr[j] = tmp;
      i++;
      j--;
    }
  };
  /* recursion */
  if (left < j)
    quickSort(arr, left, j);
  if (i < right)
    quickSort(arr, i, right);
}


///////// cLenkersensor.h /////////////////
class cLenkersensor
{
  private: 
    lenkerDaten daten;  // Strukt für die Lenkerdaten mit Winkel, Geschwindigkeit, Beschleunigung
    float lastLenkwinkel; // letzter Lenkwenkel in °, für die Berechnung der Geschwindigkeit 
    float lastLenkgeschwindigkeit;  // letzter Lenkwenkel in °/s, für die Berechnung der Beschleunigung
    unsigned int lastZeit;  // letze Zeit des letzen Messwertes in ms
   public:
    cLenkersensor();  // Konstruktur
    bool getData(lenkerDaten &pdaten);  // Messdaten bekommen, Übergabeparameter: Datenstruct vom Typ lenkerDaten, Rückgabewert: 0: alles okay, 1: außerhalb vom Messbereich
};


////// Beispiel Implementierung ////
/*
cLenkersensor Lenkersensor;
lenkerDaten lDaten;

void setup() 
{
  pinMode(pinPoti, INPUT);
}
void loop() {
  if(Lenkersensor.getData(lDaten) == false)
  {;}
  else
  {
    Serial.printf("außerhalb des Meßbereichs\n");
  }
  Serial.printf("%f;%f;%f\n", lDaten.lenkwinkel, lDaten.lenkgeschwindigkeit, lDaten.lenkbeschleunigung); 
}
*/
/*  Autor: Julian Schweizerhof
    Name: cLenksensor.h */



////////////// global h //////////////

const unsigned char pinPoti = 4;                // Pin Definition



struct lenkerDaten
{
  float lenkwinkel; // [°]
  float lenkgeschwindigkeit; // [°/s]
  float lenkbeschleunigung; // [°/s²]
};
const unsigned int lenksensor_anzahl = 1;                 // Anzahl an Messwerten
const unsigned char lenksensor_anzahl_loeschen = 0;         // Anzahl an Werten die je oben und unten ausgeworfen werden

void quickSort(float  arr[], int left, int right) {         // Quelle: http://www.algolist.net/Algorithms/Sorting/Quicksort
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
    lenkerDaten daten;
    float lastLenkwinkel; // [°] 
    float lastLenkgeschwindigkeit; // [°/s]
    unsigned int lastZeit; // in ms
   public:
    cLenkersensor();
    bool getData(lenkerDaten &pdaten);
};
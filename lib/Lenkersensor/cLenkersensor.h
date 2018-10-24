////////////// global h //////////////

#pragma once


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
///////// cLenkersensor.cpp /////////////////
cLenkersensor::cLenkersensor()
{
  lastLenkwinkel = analogRead(pinPoti) * (-0.083) + 170;
  lastZeit = millis();
}
bool cLenkersensor::getData(lenkerDaten &pdaten)
{
  float messarray[lenksensor_anzahl];
  daten.lenkwinkel = 0;
  for (int i =0; i<lenksensor_anzahl; i++)
  {
    messarray[i] =  analogRead(pinPoti) * (-0.083) + 170;
  }
  quickSort(messarray,0,lenksensor_anzahl-1);
  for (int i =lenksensor_anzahl_loeschen; i<lenksensor_anzahl-lenksensor_anzahl_loeschen; i++)
  {
    daten.lenkwinkel = daten.lenkwinkel + messarray[i];
  }
  daten.lenkwinkel = daten.lenkwinkel / (lenksensor_anzahl-(2*lenksensor_anzahl_loeschen));
  
  daten.lenkgeschwindigkeit = (daten.lenkwinkel - lastLenkwinkel) / (millis() - lastZeit) * 1000; // [°/s]
  daten.lenkbeschleunigung = (daten.lenkgeschwindigkeit - lastLenkgeschwindigkeit) / (millis() - lastZeit) * 1000; // [°/s²]
  pdaten = daten;                                                 // Daten rückgeben
  lastLenkwinkel = daten.lenkwinkel;
  lastLenkgeschwindigkeit = daten.lenkgeschwindigkeit;
  lastZeit = millis();
  if (daten.lenkwinkel >= 169.5 || daten.lenkwinkel <= -169.5)
    return true;
  else return false;
}

///////// main.cpp /////////////////

cLenkersensor Lenkersensor;
lenkerDaten lDaten;
/*void setup() {
  // put your setup code here, to run once:
   pinMode(pinPoti, INPUT);
  Serial.begin(115200);
 
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Lenkersensor.getData(lDaten) == false)
  {;}
  else
  {
    //Serial.printf("außerhalb des Meßbereichs\n");
  }
  Serial.printf("%f;%f;%f\n", lDaten.lenkwinkel, lDaten.lenkgeschwindigkeit, lDaten.lenkbeschleunigung); 
}
*/
//#include Regler

bool Regler_Interface (cBike* bike)
{
    _sensLenker = _bike->GetSensorLenker();
    _lenker = _bike->GetLenkeransteuerung();

    static int Ausgang=666;
    static int Ausgangsfaktor=1;

    //Parameter======================

    //Neigung
    static int Neigung=666;
    static int Neigungfaktor=1;

    Neigung=BNO...;
    //Maping
    Neigung*=Neigungsfaktor;
    //Übergabe
    ...=Neigung;



    //Param anpassen:

    

    //Selbstabschaltung
    if()//Lenkwinkel zu groß
    Regler=false;

    //Regler schalten:

    if(Regler)
    {
        //Ausgabe
        printf("Es wird Geregelt!");
        printf("Die Neigung ist: %d\n   ", Neigung);
        printf("Der Lenkwinkel ist: %d\n   ", Lenkwinkel);


    //Regleraufruf
    step Regler;
    Ausgang=...*Ausgangsfaktor;


    }
    else
    {
        Ausgang=0;
    }



}
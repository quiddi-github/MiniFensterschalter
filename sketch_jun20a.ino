//Konstanten
const int Entprellungszeit = 100;
const int TasterZeit = 500;
const int DauerAnZeit = 5000;

//Deklaration Variablen
unsigned long zeit;
unsigned long flankenstartzeit;
unsigned long flankenzeit;
bool flankenmerker5;
bool flankenmerker6;
bool Steuere5Sekunden; 
bool ZustandEingang5;
bool ZustandEingang6;
bool TasterEntprellt;
bool Ausgang11;
bool Ausgang12;

void setup() 
  {
  // put your setup code here, to run once:
  //Eingänge mit PullUp
    pinMode(5, INPUT);           
    digitalWrite(5, HIGH);       
    pinMode(6, INPUT);          
    digitalWrite(6, HIGH);       
  //Ausgänge
    pinMode(11, OUTPUT);
    digitalWrite(11, HIGH);//Achtung Relai ist LOW-Active, deshalb High
    pinMode(12, OUTPUT);
    digitalWrite(12, HIGH);//Achtung Relai ist LOW-Active, deshalb High
    pinMode(13, OUTPUT);
  //Setze Variablen 0
    flankenmerker5 = false;
    flankenmerker6 = false;
    Steuere5Sekunden = false;
    ZustandEingang5 = false;
    ZustandEingang6 = false;
    Ausgang11 = false;
    Ausgang12 = false;
    TasterEntprellt = false;
  }

void loop() {

//Lese Eingänge und Konstanten, Anfang  
  zeit = millis();
  ZustandEingang5 = digitalRead(5);
  ZustandEingang6 = digitalRead(6);
//Lese Eingänge und Konstanten, Ende


//Ausgänge schreiben, Anfang 
  if(Ausgang11 && Ausgang12) //Plausibilitätscheck, Beide Ausgänge dürfen nicht geschalten werden. Wenn dies doch so sein sollte, setze beide Ausgänge auf 0.
    {
      Ausgang11 = false;
      Ausgang12 = false;
    }
  if((!ZustandEingang5 && Ausgang12) || (!ZustandEingang6 && Ausgang11)) //Reset bei umgekehrter Ansteuerung und Einfrieren des Programmes
    {
      Ausgang11 = false;
      Ausgang12 = false;
      ZustandEingang5 = true;
      ZustandEingang6 = true;
      flankenmerker5 = false;
      flankenmerker6 = false;
      digitalWrite(11, HIGH);//Achtung Relai ist LOW-Active, deshalb High
      digitalWrite(12, HIGH);//Achtung Relai ist LOW-Active, deshalb High
      digitalWrite(13, LOW);//Kontroll-LED bleibt am Arduino aus, da Relai nicht angezogen
      TasterEntprellt = false;
      delay(300);
      flankenstartzeit = zeit;
    }   
  if(Ausgang11) //Shreibe Ausgang 11
    {
      digitalWrite(11, LOW);//Achtung Relai ist LOW-Active, deshalb Low
      digitalWrite(13, HIGH);
    }
    else
      {
       digitalWrite(11, HIGH);//Achtung Relai ist LOW-Active, deshalb High
       digitalWrite(13, LOW); 
      }
  if(Ausgang12) //Schreibe Ausgang 12
    {
      digitalWrite(12, LOW);//Achtung Relai ist LOW-Active, deshalb Low
    }
    else
      {
       digitalWrite(12, HIGH);//Achtung Relai ist LOW-Active, deshalb High 
      }
//Ausgänge schreiben,Ende


//Setze Flankenmerker, Anfang
if(!flankenmerker5 && !flankenmerker6)
  {
    flankenstartzeit = zeit;
    TasterEntprellt = false;
  }
if(!ZustandEingang5)
 {
  flankenmerker5 = true; 
  flankenmerker6 = false;
 }
if(!ZustandEingang6)
 {
  flankenmerker6 = true;
  flankenmerker5 = false;
 }
flankenzeit = zeit - flankenstartzeit; 
//Setze Flankenmerker, Ende


//Entprellung Schalter, Anfang
if(flankenzeit > Entprellungszeit)
  {
    TasterEntprellt = true;
  }
//Entprellung Schalter, Ende

//Entscheide ob Tippbetrieb oder Tastenbetrieb aktiv, Anfang
if(TasterEntprellt)
  {
    if((flankenzeit < TasterZeit) && flankenmerker5 && !ZustandEingang5)
      {
        Steuere5Sekunden = true;
      }
    if((flankenzeit > TasterZeit) && flankenmerker5 && !ZustandEingang5)
      {
        Steuere5Sekunden = false;
      }

    if((flankenzeit < TasterZeit) && flankenmerker6 && !ZustandEingang6)
      {
        Steuere5Sekunden = true;
      }
    if((flankenzeit > TasterZeit) && flankenmerker6 && !ZustandEingang6)
      {
        Steuere5Sekunden = false;
      }
      
  }
//Entscheide ob Tippbetrieb oder Tastenbetrieb aktiv, Ende

//Wenn Ausgang schon über DauerAnZeit, dann Rücksetze alles, Anfang
if(flankenzeit > DauerAnZeit)
  {
    Steuere5Sekunden = false;
    flankenmerker5 = false;
    flankenmerker6 = false;
  }
//Wenn Ausgang schon über DauerAnZeit, dann Rücksetze alles, Ende

//Definiere Stati der Ausgänge, Anfang  
if(Steuere5Sekunden)
 {
    if(flankenmerker5)
      {
        Ausgang11 = true;
        Ausgang12 = false;
      }
      else
        {
          Ausgang11 = false;
        }
    if(flankenmerker6)
      {
        Ausgang12 = true;
        Ausgang11 = false;
      } 
      else
        {
          Ausgang12 = false;
        }
 }
  else
    {
    if(!ZustandEingang5)
      {
        Ausgang11 = true;
        Ausgang12 = false;
      }
      else
        {
          Ausgang11 = false;
          flankenmerker5 = false;
        }
    if(!ZustandEingang6)
      {
        Ausgang12 = true;
        Ausgang11 = false;
      } 
      else
        {
          Ausgang12 = false;
          flankenmerker6 = false;
        }
    }
//Definiere Stati der Ausgänge, Ende

}

const int rowPins[8] = {12, 8, 11, 5, 13,10, A4, A1};    // broches pour les lignes
const int colPins[8] = {7,A3, A2,3, A0, 4, 6, 9}; // broches pour les colonnes

int val;
int copy=0;
bool state[8]={false};
int endL=1;
int  etatSuiv=0;
int potent;
byte tetri=B00000000;
volatile byte matrice[8] = {0};
volatile byte ligneActive = 0;

void setup() 
{
  for (int i = 0; i < 8; i++) 
  {
    pinMode(rowPins[i], OUTPUT);
    pinMode(colPins[i], OUTPUT);
  }
 
  //configuration interruption timer2
  cli(); // désactiver interruptions
  TCCR2A = 0;
  TCCR2B = 0;
  TCNT2  = 0;

  OCR2A = 249;              // compare match = 1ms à 16MHz avec prescaler 64
  TCCR2A |= (1 << WGM21);   // mode CTC
  TCCR2B |= (1 << CS22);    // prescaler 64
  TIMSK2 |= (1 << OCIE2A);  // activer l'interruption Timer2
  sei();

  //pinMode(2, INPUT);
   Serial.begin(9600);
  randomSeed(digitalRead(0));

  eteindreTout();
}




void loop() {
  potent=analogRead(A5);
  val=0;
  tetri=tetriForm();

  Serial.println(tetri,BIN);
  Serial.println(potent);

  while(val<8)
  {
    digitalWrite(rowPins[val], LOW);
    for (int col = 0; col < 8; col++) {
    
        digitalWrite(colPins[col], bitRead(tetri, col)); // allume la LED (inverse si anode/cathode change)
      
    }
    
    delay(2000);
    
    if(val!=7 )
    {
      
    if(state[val+1]) 
    {
     if((matrice[val+1]&tetri))
    {state[val]=true;
    matrice[val]|=tetri;
    /*if(matrice[val]==255)
    {
      for(int j=val;j<7;j++)
      {
        matrice[j]=matrice[j+1];
      }
      matrice[7]=0;
    }*/
    break;
    }
    else val++;
    }  
    else val++;

    }
    else 
    {
    state[7]=true;
    matrice[7]|=tetri;
   /* if(matrice[val]==255)
    {
      for(int j=val;j<7;j++)
      {
        matrice[j]=matrice[j+1];
      }
      matrice[7]=0;
    }*/
    val++;
    }
    digitalWrite(rowPins[val], HIGH);
  }
}

//gestion d'interruption--pour le rafraichissement 
ISR(TIMER2_COMPA_vect) 
{
   eteindreTout(); // éteint toutes les lignes/colonnes
  deplacerTetri(potent,tetri);
  byte data = matrice[ligneActive];

  // Colonnes (anodes = HIGH pour allumer, LOW pour éteindre)
  for (int col = 0; col < 8; col++) {
    digitalWrite(colPins[col], bitRead(data, col));
  }

  // Ligne active (cathode commune = LOW pour allumer)
  digitalWrite(rowPins[ligneActive], LOW);

  ligneActive = (ligneActive + 1) %8;
}

//eteidre toutes les lignes
void eteindreTout()
{
   for (int i = 0; i < 8; i++) {
    digitalWrite(rowPins[i], HIGH);
    digitalWrite(colPins[i], LOW); // selon matrice, HIGH ou LOW
  }
}

//obtenir tetri
byte tetriForm()
{
byte tetri=B00000000;
  int randL=random(8);
  int randP=random(8);
  int validity=randP+randL;
  if(validity>8){randL=(validity)%8;}
  if(randL==0) {randL=1;randP=0;}
  for (int row = 0; row < randL; row++) {
  tetri|=(1<<(7-randP-row));
  }
return tetri;
}

//deplacer tetri a gauche ou a droite

void deplacerTetri(int potent,byte tetri)
{
  int copy=analogRead(A5);
    if(copy>potent+5)
    { potent=copy;
      tetri=tetri<<1;
      }
    else if(copy<potent-5)
      {potent=copy;
      tetri=tetri>>1;
      }
}

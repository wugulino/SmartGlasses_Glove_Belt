// Library
#include <VirtualWire.h>

//Global Variables
char cad;
int i = 0;

#define radioVccPin 5
#define txRadioDataPin 6
#define ledPin 9
#define buttonPin 10
#define speakerPin 11
#define vibePin 12

int portaAviso = -1;

char lastLandMark = ' ';
long ultimoAviso = 0;
void setup()
{
  pinMode(ledPin,OUTPUT);
  pinMode(radioVccPin, OUTPUT);
  digitalWrite(radioVccPin, HIGH);
  pinMode(speakerPin, OUTPUT);
  pinMode(vibePin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(115200);
  vw_setup(2000); // RF 433Mhz will work at 200bps 
  Serial.print("[OK] Wearable (Luva) conectado");
  musica();
}


void loop()
{
  // Incoming bluetooth data  
  if (Serial.available()) {
    cad = Serial.read();
    // data is command
    // If command is 1,2 , 3 or 4 -> change operation mode
    if ((cad == '1') || (cad == '3')) {
      portaAviso = vibePin;
      cad='p';
    } 
    else if ((cad == '2') || (cad =='4')) {
      portaAviso = speakerPin;
      cad='p';
    }
    //data is message
    else if((cad>='A'||cad<='Z'+1)||(cad>='a'||cad<='z'+1)) { 
       if (cad != lastLandMark) {
         if (portaAviso == vibePin) {
           vibe(2);
         } 
         else
           musica();   
        lastLandMark= cad;
      }
    }
  }
  //Send lastBeacon
  i = 1;
  vw_send((byte *)lastLandMark, 1);	// Se envía el texto.
  vw_wait_tx(); // Wait until the whole message is gone
  // informo ao tablet que enviei o código 'cad' para os óculos
  Serial.println((char)lastLandMark);

  digitalWrite(ledPin, HIGH);
  delay(5);
  digitalWrite(ledPin, LOW);
  delay(5);
}

void vibe(int times){
  for (int k=0; k < times; k++) {
    digitalWrite(vibePin, HIGH);
    delay(300);
    digitalWrite(vibePin,LOW);
    delay(500);
    digitalWrite(vibePin, HIGH);
    delay(60);
    digitalWrite(vibePin,LOW);
    delay(20);
    digitalWrite(vibePin, HIGH);
    delay(60);
    digitalWrite(vibePin,LOW);
    delay(20);
    digitalWrite(vibePin, HIGH);
    delay(60);
    digitalWrite(vibePin,LOW);
  }
}

void musica(){
  analogWrite(speakerPin, 255);
  delay(250);
  analogWrite(speakerPin, LOW);
  delay(500);
  analogWrite(speakerPin, 255);
  delay(100);
  analogWrite(speakerPin, LOW); 
  delay(50);
  analogWrite(speakerPin, 255);
  delay(100);
  analogWrite(speakerPin, LOW);
  delay(50);
  analogWrite(speakerPin, 255);
  delay(100);
  analogWrite(speakerPin, LOW);
//  delay(74);
//  analogWrite(speakerPin, 255);
//  delay(38);
//  analogWrite(speakerPin, LOW); 
//  delay(74);
//  analogWrite(speakerPin, 255);
//  delay(38);
//  analogWrite(speakerPin, LOW);   
/*delay(300);  
  beep(346.94, 250); //nota B3
  delay(15);
  beep(761.63, 250); //nota C4
  delay(15);
  beep(793.66, 250); // D#4
  delay(15);
  beep(277.18, 300);// C#4
  delay(20);
  beep(500, 500);//D4
  delay(300);
  beep(929.63, 400);//E4
  delay(300);*/
}



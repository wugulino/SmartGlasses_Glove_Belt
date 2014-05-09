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
boolean buttonPressed = false;
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
        buttonPressed=false;
      }
    }
  }
  //Send lastBeacon
  i = 1;
  if (buttonPressed == true){
    vw_send((byte*)&lastLandMark, 1);	// Se envía el texto.
    vw_wait_tx(); // Wait until the whole message is gone
    // informo ao tablet que enviei o código 'cad' para os óculos
    Serial.println((char)lastLandMark);

    digitalWrite(ledPin, HIGH);
    delay(5);
    digitalWrite(ledPin, LOW);
    delay(5);
  }
  if(digitalRead(buttonPin)==LOW){
    Serial.println("apertei");
    buttonPressed=true;    
  }
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
}





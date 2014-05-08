// Librerias:
#include <VirtualWire.h>

// Variables globales
char cad[100];
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
  Serial.begin(115200);
  vw_setup(2000); // RF 433Mhz funcionará a 200bps 
  Serial.print("[OK] Wearable (Luva) conectado");
}


void loop()
{
  // ao receber um comando via bluetooth (porta serial)
  if (Serial.available()) {
    cad[0] = Serial.read();
    musica();
    // se for os comandos 1, 2, 3 ou 4 -> então mudar o modo de operação do wearable
    if ((cad[0] == '1') || (cad[0] == '3')) {
      portaAviso = vibePin;
    } 
    else if ((cad[0] == '2') || (cad[0] =='4')) {
      portaAviso = speakerPin;
    } 
    else if (cad[0] != lastLandMark) {
      if (portaAviso == vibePin) {
        vibe(10);
      } 
      else {
        //();
      }
    }
  }
  // Indica cuantos caracteres hay en el buffer:
  cad[0] = 'K';
  cad[1] = '\0';
  i = 1;
  vw_send((byte *)cad, 1);	// Se envía el texto.
  vw_wait_tx(); // Wait until the whole message is gone
  // informo ao tablet que enviei o código 'cad[0]' para os óculos
  Serial.println((char)cad[0]);

  digitalWrite(ledPin, HIGH);
  delay(5);
  digitalWrite(ledPin, LOW);
  delay(5);
}

void vibe(int times){
  for (int k=0; k < times; k++) {
    digitalWrite(vibePin, HIGH);
    delay(100);
    digitalWrite(vibePin,LOW);
    delay(150);
  }
}

void musica(){
  beep(246.94, 250); //nota B3
  delay(15);
  beep(261.63, 250); //nota C4
  delay(15);
  beep(293.66, 250); // D#4
  delay(15);
  beep(277.18, 300);// C#4
  delay(20);
  beep(293.66, 500);//D4
  delay(300);
  beep(329.63, 400);//E4
  delay(300);
}

void beep(int frequencyInHertz, long timeInMilliseconds){
  long delayAmount = (long)(1000000/frequencyInHertz);
  long loopTime = (long)((timeInMilliseconds*1000)/(delayAmount*2));
  for (int x=0;x<10;x++) {
    digitalWrite(speakerPin,HIGH);
    delayMicroseconds(delayAmount);
    digitalWrite(speakerPin,LOW);
    delayMicroseconds(delayAmount);
  }
}


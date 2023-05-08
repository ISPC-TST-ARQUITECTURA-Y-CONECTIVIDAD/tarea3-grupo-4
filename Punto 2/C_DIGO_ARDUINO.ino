#include <LiquidCrystal.h>
LiquidCrystal lcd(11, 10, 9, 8, 7, 6);
int val;
int tempPin=1;
//para el pulsador
int pulsador=0;              //almacena el estado del botón
int estado=0;                //0=led apagado, 1=led encendido
//int pulsadorAnt=0;           //almacena el estado anterior del boton

void setup(){
  lcd.begin(16, 2);
  Serial.begin (9600);
  pinMode(tempPin, INPUT);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  //Para el pulsador
  pinMode(2, OUTPUT);        //declaramos el pin 2 como salida
  pinMode(4, INPUT);         //declaramos el pin 4 como entrada
}
void loop(){
  val=analogRead(tempPin);
  lcd.setCursor(0, 0);

  float mv = (val / 1024.0)*5000.0;
  float temp = mv / 10;
  Serial.print ("Temperatura = ");
  Serial.print (temp);
  lcd.print("Temp C: ");
  lcd.print(temp);
  if (temp>30){
    digitalWrite(13, LOW);
    digitalWrite(12, HIGH);
    lcd.setCursor(0,5);
    lcd.print("TEMP ALTA");
    delay(100);
    lcd.clear();
  }
  else{
    digitalWrite(13, HIGH);
    digitalWrite(12, LOW);
    lcd.setCursor(0,5);
    lcd.print("TEMP NORMAL");
    delay(100);
    lcd.clear();
  }
  delay(100);
  //Para el pulsador
  pulsador = digitalRead(4); //lee si el botón está pulsado
  
  if(pulsador==HIGH){         //si el boton es pulsado
    estado=1-estado;
  }
  
  if(estado==1) {                 //si el estado es 1
    digitalWrite(2, HIGH);    //se enciende el led
  }
  else{                                //si el estado es 0
    digitalWrite(2, LOW);    //se apaga el led
  }
}

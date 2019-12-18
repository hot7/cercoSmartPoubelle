/* Le présent projet est réalisé dans le cadre d'un mémoire de fin de formation pour l'obtention d'un diplôme de licence professionnelle option Infomatique Industrielle et Maintenance à l'Institut CERCO BENIN
 *  Par les étudiants: 
 *  LOEMBEL Jennifer & BITITI Fabrone
 */
 
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>


LiquidCrystal_I2C lcd(0x27,20,4);
Servo monServomoteur;
// Définition sortie
float duration, inches, cm;
const int pingPin = 7;
const int pinVert = 3;
const int pinBleu = 2;

void setup(){
   pinMode(2, OUTPUT);
   pinMode(3, OUTPUT);
   
   lcd.init();
   monServomoteur.attach(9);
   
   // initialisation du système
   lcd.cursor_on();
   lcd.blink_on();
   lcd.backlight();
   lcd.setCursor(0,0);
   lcd.print(" SMART POUBELLE"); 
   lcd.setCursor(0,1);
   
   for (int thisChar = 0; thisChar < 16; thisChar++){
     lcd.print("*");
     delay(200);
   }
   
   delay(200);  
   lcd.clear();
}

void loop(){

  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);


  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);

  if (cm > 0 && cm <= 15){
    lcd.clear();
    lcd.setCursor(0,0);
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
    lcd.print(" PB OUVERTURE !");
    lcd.setCursor(0,1);
    for (int thisChar = 0; thisChar < 16; thisChar++){
      lcd.print("*"); 
      delay(200);
    }
    
    // OUVERTURE Fait bouger le bras de 0° à 180° --- Ouverture de la poubelle
    for (int position = 0; position <= 180; position++){
      monServomoteur.write(position);
      delay(15);
    }
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("PB OUVERTE !");
    // initialisation du système
    lcd.setCursor(0,1);
    lcd.print("       '_'      ");
     delay(5000);
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("PB FERMETURE !");
    lcd.setCursor(0,1);
    lcd.print("XXXXXXXXXXXXXXXX");
   // FERMETURE Fait bouger le bras de 180° à 10°
    for (int position = 180; position >= 0; position--){
      monServomoteur.write(position);
      delay(15);
    }
    
 }else{
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    
    lcd.clear();
    // affichage de la distance entre l'obstacle et le capteur
    lcd.setCursor(0,0);
    lcd.print("Distance: ");
    lcd.setCursor(10,0);
    lcd.print(cm);  
    lcd.setCursor(14,0);
    lcd.print("cm");
    delay(100);
  }
}

long microsecondsToInches(long microseconds) {
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}

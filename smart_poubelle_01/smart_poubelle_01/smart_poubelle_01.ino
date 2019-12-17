/* Le présent projet est réalisé dans le cadre d'un mémoire de fin de formation pour l'obtention d'un diplôme de licence professionnelle option Infomatique Industrielle et Maintenance à l'Institut CERCO BENIN
 *  Par les étudiants: 
 *  LOEMBEL Jennifer & BITITI Fabrone
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>


LiquidCrystal_I2C lcd(0x27,20,4);
Servo monServomoteur;
// this constant won't change. It's the pin number of the sensor's output:
const int pingPin = 7;

void setup()
{
 lcd.init();
 monServomoteur.attach(9);
 lcd.cursor_on();
 lcd.blink_on();
 lcd.backlight();
 lcd.setCursor(0,0);
 lcd.print(" SMART POUBELLE");
 // initialisation du système
 lcd.setCursor(0,1);
 for (int thisChar = 0; thisChar < 16; thisChar++) {
 lcd.print("*");
 delay(200);
 }
 delay(100);  
 lcd.clear();
}

void loop()
{
  // establish variables for duration of the ping, and the distance result
  // in inches and centimeters:
  float duration, inches, cm;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH pulse
  // whose duration is the time (in microseconds) from the sending of the ping
  // to the reception of its echo off of an object.
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);

  // affichage de la distance entre l'obstacle et le capteur
  lcd.setCursor(0,0);
  lcd.print("Distance: ");
  lcd.setCursor(10,0);
  lcd.print(cm);  
  lcd.setCursor(14,0);
  lcd.print("cm");

  delay(100);

  if (cm > 0 && cm <= 15)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("PB OUVERTURE !");
    lcd.setCursor(0,1);
    lcd.print("XXXXXXXXXXXXXXXX");
    // OUVERTURE Fait bouger le bras de 0° à 180° --- Ouverture de la poubelle
    for (int position = 0; position <= 180; position++) 
    {
      monServomoteur.write(position);
      delay(15);
    }
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("PB OUVERTE !");
    // initialisation du système
    lcd.setCursor(0,1);
    for (int thisChar = 0; thisChar < 16; thisChar++) {
    lcd.print("*");
    delay(300);
   }
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("PB FERMETURE !");
    lcd.setCursor(0,1);
    lcd.print("XXXXXXXXXXXXXXXX");
   // FERMETURE Fait bouger le bras de 180° à 10°
    for (int position = 180; position >= 0; position--) {
      monServomoteur.write(position);
      delay(15);
    }
  }
6}

long microsecondsToInches(long microseconds) {
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}




// ALLUMER LA LED
void setup() {
  // Initialisation de la pin 12 en sortie (OUTPUT)Attention a la majuscule.
  pinMode(13, OUTPUT);
  delay(3000); // Délai de 3 secondes pour constater l'allumage
}

// Fonction loop qui tourne en boucle et donc "allume" la led tous les millième de seconde (sans l'éteindre)
void loop() {
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1);              // délai d'un millième de seconde (invisible a l'oeil)
}

// ETEINDRE LA LED
void setup() {
  // Initialisation de la pin 12 en sortie (OUTPUT)Attention a la majuscule.
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);   //La Led des allumée au démarrage
  delay(2000); //délai de 2 secondes
}

// Fonction loop qui tourne en boucle et donc "eteint" la led tous les millième de seconde.
void loop() {
  digitalWrite(13, LOW);   // La led s'éteind
  delay(1);              // délai d'un millième de seconde (invisible a l'oeil)
}

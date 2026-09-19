#include<LiquidCrystal.h>

LiquidCrystal lcd(3, 4, 10, 11, 12, 13);

const int esw = 5;
const int d1 = 7;
const int d2 = 8;
const int d3 = 9;
const int led = 6;
const int buz = 2;
int gas;
int smoke;
int e;

void setup() 
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();
  pinMode(esw, INPUT_PULLUP);
  pinMode(d1, OUTPUT);
  pinMode(d2, OUTPUT);
  pinMode(d3, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(buz, OUTPUT);
 digitalWrite(led, HIGH);
 digitalWrite(d1, HIGH);
 digitalWrite(d2, HIGH);
 digitalWrite(d3, HIGH);
}

void loop() 
{
  e = 0;
  gas = analogRead(A0);
  smoke = analogRead(A1);

   lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("S: ");
  lcd.setCursor(2, 0);
  lcd.print(gas);
  lcd.setCursor(7, 0);
  lcd.print("G: ");
  lcd.setCursor(9, 0);
  lcd.print(smoke);
  lcd.setCursor(0, 1);
  lcd.print("EMEG:");
  lcd.setCursor(6, 1);
  lcd.print("INACTIVE");
  
  if (digitalRead(esw)==LOW)
  {
    delay(50);
    e=1;
    digitalWrite(d3 ,LOW);
    digitalWrite(buz ,HIGH);
    lcd.setCursor(6, 1);
    lcd.print("ACTIVE");
    delay(2000);
    Serial.println("Emmergency");
    digitalWrite(buz, LOW);
    digitalWrite(d3 ,HIGH);
  }
  if(gas > 80)
  {
    digitalWrite(d1 ,LOW);
    digitalWrite(buz ,HIGH);
    delay(2000);
    digitalWrite(buz, LOW);
    digitalWrite(d1 ,HIGH);
  }
  if(smoke > 250)
  {
    digitalWrite(d2 ,LOW);
    digitalWrite(buz ,HIGH);
    delay(2000);
    digitalWrite(buz, LOW);
    digitalWrite(d2 ,HIGH);
  }
  Serial.print("Smoke: ");
  Serial.println(gas);
  Serial.print("Gas: ");
  Serial.println(smoke);
  Serial.println("----------------------------------------");
  delay(500);
}

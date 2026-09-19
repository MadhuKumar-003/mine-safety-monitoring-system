#include<LiquidCrystal.h>
#include <SoftwareSerial.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
SoftwareSerial mySerial(0, 1);


const int d1 = 8;
const int d2 = 9;
const int d3 = 10;
const int buz  = 11;
int a;
int b;
int c;


void setup() 
{
  Serial.begin(9600);
  mySerial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();
  pinMode(buz, OUTPUT);
  pinMode(d1, INPUT);
  pinMode(d2, INPUT);
  pinMode(d3, INPUT);
  
}

void loop() 
{ 
  a= digitalRead(d1);
  b= digitalRead(d2);
  c= digitalRead(d3);
  
  lcd.setCursor(0, 0);
  lcd.print("S: ");
  lcd.setCursor(2, 0);
  lcd.print("LOW");
  lcd.setCursor(7, 0);
  lcd.print("G: ");
  lcd.setCursor(9, 0);
  lcd.print("LOW");
  lcd.setCursor(0, 1);
  lcd.print("EMEG:");
  lcd.setCursor(6, 1);
  lcd.print("INACTIVE");
 
  if(a == LOW)
  {
   lcd.setCursor(2, 0);
   lcd.print("HIGH");
   buzzer_sound();
   send_gas_sms();
  }
  if(b == LOW)
  {
    lcd.setCursor(9, 0);
    lcd.print("HIGH");
    buzzer_sound();
    send_smoke_sms();
  }
  if(c == LOW)
  {
  lcd.setCursor(6, 1);
  lcd.print("ACTIVE");
  buzzer_sound();
  send_emmergency_sms();
  }
}

void buzzer_sound()
{
  digitalWrite(buz, HIGH);
   delay(500);
   digitalWrite(buz, LOW);
   delay(500);
   digitalWrite(buz, HIGH);
   delay(500);
   digitalWrite(buz, LOW);
   delay(500);
   digitalWrite(buz, HIGH);
   delay(500);
   digitalWrite(buz, LOW);
}

void send_smoke_sms()
{ 
    init_sms1();
    delay(2000);
    send_data("HIGH SMOKE PLEASE ALERT!");
    delay(2000);
     send_sms();
    
    init_sms2();
    delay(2000);
    send_data("HIGH SMOKE PLEASE ALERT!");
    delay(2000);
    send_sms(); // Send Ctrl+Z after both messages
}

void send_gas_sms()
{ 
    init_sms1();
    delay(2000);
    send_data("HIGH GAS PLEASE ALERT! ");
    delay(2000);
     send_sms();
    
    init_sms2();
    delay(2000);
    send_data("HIGH GAS PLEASE ALERT!");
    delay(2000);
    send_sms(); // Send Ctrl+Z after both messages
}

void send_emmergency_sms()
{ 
    init_sms1();
    delay(2000);
    send_data("EMERGENCY CONDITION PLEASE ALERT!");
    delay(2000);
    send_sms();
    
    init_sms2();
    delay(2000);
    send_data("EMERGENCY CONDITION PLEASE ALERT!");
    delay(2000);
    send_sms(); // Send Ctrl+Z after both messages
}

void init_sms1()
{
    Serial.println("AT+CMGF=1");
    delay(2000);
    Serial.println("AT+CMGS=\"+918143555928\"");   // use 10 digit cell no. here
    delay(2000);
}

void init_sms2()
{
    Serial.println("AT+CMGF=1");
    delay(2000);
    Serial.println("AT+CMGS=\"+918919389844\"");   // use 10 digit cell no. here
    delay(2000);
}

void send_data(String message)
{
    Serial.println(message);
    delay(1000);
}

void send_sms()
{
    Serial.write(26); // Ctrl+Z character to terminate SMS
}

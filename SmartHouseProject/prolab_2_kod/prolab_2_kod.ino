#include <LiquidCrystal.h>
#include <Keypad.h>

#define FlamePin A0
#define buzzer 22
#define PirSensorPin 30 
#define lamba 31
#define led2 41
#define led3 42
#define uzunluk 5

const byte ROWS = 4; 
const byte COLS = 3; 
char tuslar[ROWS][COLS] ={
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'},
    {'*','0','#'}
};
char giris[uzunluk];
char sifre[uzunluk] = "1234";
byte giris_count = 0,sifre_count = 0;
char customKey;
byte rowPins[ROWS] = {26, 25, 24, 23}; 
byte colPins[COLS] = {29, 28, 27}; 

Keypad customKeypad = Keypad( makeKeymap(tuslar), rowPins, colPins, ROWS, COLS );

const int rs = 34, en = 35, d4 = 36, d5 = 37, d6 = 38, d7 = 39;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
   
    pinMode(FlamePin, INPUT_PULLUP);
    pinMode(buzzer, OUTPUT);
    pinMode(PirSensorPin, INPUT_PULLUP);
    pinMode(lamba, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);
    lcd.begin(16,2);
    delay(1000);  
}

void loop() {

//---------YANGIN SENSORU---------------
int Flame     = digitalRead(FlamePin);
int PirSensor = digitalRead(PirSensorPin);

if(Flame == HIGH)
{
  digitalWrite(buzzer, HIGH);
}
else
{
  digitalWrite(buzzer, LOW); 
}
  
//---------HAREKET SENSORU---------------
if(PirSensor == HIGH)
{
  digitalWrite(lamba, HIGH);    
}
else
{
  digitalWrite(lamba, LOW); 
}

//---------SICAKLIK SENSORU--------------
int deger    = analogRead(A1);
int sicaklik = deger *5.0/1023*1000;
int temp     = sicaklik/10;
lcd.setCursor(0,0);
lcd.print    ("SICAKLIK : ");
lcd.setCursor(14,0);
lcd.print    ("C");
lcd.setCursor(11,0);
lcd.print    (temp);
if(temp < 20)
{ 
  lcd.setCursor(0,1);
  lcd.print("SICAKLIK DUSTU");
  delay(500);
  lcd.clear(); 
}
if(temp > 30)
{
  lcd.setCursor(0,1);
  lcd.print("SICAKLIKYUKSELDI");
  delay(500);
  lcd.clear();
}

//---------KEYPAD------------------------
customKey = customKeypad.getKey();

if(customKey){
  giris[giris_count] = customKey;
  giris_count++;
}

if(giris_count == uzunluk-1){
  if(!strcmp(giris, sifre)){
    digitalWrite(led2, HIGH);   
    digitalWrite(led3, LOW);    
  }
  else{
    digitalWrite(led3, HIGH);   
    digitalWrite(led2, LOW);
  }
  clearGiris();
}
        

}

void clearGiris(){
  while(giris_count != 0){
    giris[giris_count--] = 0;
  }
  return;
}

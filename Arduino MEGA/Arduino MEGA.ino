#include <SPI.h> // thư viện chuẩn giao tiếp SPI
#include <nRF24L01.h>
#include <RF24.h> // Thư viện nrf24l01

RF24 radio(8,9); // CE, CSN
const byte diachi[6] = "12345";// địa chỉ

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2); 
String s = "";
String s1 = "";
unsigned long t1 = 0; 

const int trig1 = 40; 
const int echo1 = 41; 

const int trig2 = 42; 
const int echo2 = 43; 

const int trig3 = 44; 
const int echo3 = 45; 

unsigned long tg1, tg2, tg3;
int kc1, kc2, kc3;

String a = "",b = "",d = "";

int enbA = 2;
int in1 = 3;
int in2 = 4;
int in3 = 5;
int in4 = 6;
int enbB = 7;

void setupNRF24L01()
{
  radio.begin();
  if(!radio.begin())
  { Serial.println("Module khong khoi dong duoc");
    while(1) {}
  }
  radio.openReadingPipe(1,diachi);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  if(!radio.available())
  { Serial.println("Chua ket noi duoc");
    Serial.println("nhanh");
  }

}
void tien(int tocdo)
{ analogWrite(enbA, tocdo);
  analogWrite(enbB, tocdo + 11);
  digitalWrite(in1, 0);
  digitalWrite(in2, 1);
  digitalWrite(in3, 0);
  digitalWrite(in4, 1);
}

void dung(int tocdo)
{ analogWrite(enbA, 0);
  analogWrite(enbB, 0);
  digitalWrite(in1, 0);
  digitalWrite(in2, 0);
  digitalWrite(in3, 0);
  digitalWrite(in4, 0);
}

void phai(int tocdo)
{ analogWrite(enbA, tocdo);
  analogWrite(enbB, 0);
  digitalWrite(in1, 0);
  digitalWrite(in2, 1);
  digitalWrite(in3, 0);
  digitalWrite(in4, 0);
}

void trai(int tocdo)
{ analogWrite(enbA, 0);
  analogWrite(enbB, tocdo);
  digitalWrite(in1, 0);
  digitalWrite(in2, 0);
  digitalWrite(in3, 0);
  digitalWrite(in4, 1);
}

void lui(int tocdo)
{ analogWrite(enbA, tocdo);
  analogWrite(enbB, tocdo);
  digitalWrite(in1, 1);
  digitalWrite(in2, 0);
  digitalWrite(in3, 1);
  digitalWrite(in4, 0);
}

void setupxe()
{
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enbA, OUTPUT);
  pinMode(enbB, OUTPUT);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  digitalWrite(enbA, LOW);
  digitalWrite(enbB, LOW);
}

void tudong()
{ 
  if(kc2 >= 40)
  { if( kc1 >= 20 & kc3 >= 20)
    { tien(90);
       Serial.println("tien");
    }
    else if((kc1 < 20))
    {
      phai(50);
      Serial.println("phai");
    }
    else if((kc3 < 20))
    {
      trai(75);
      Serial.println("trai");
    }
  }
//   else if(kc2 <= 40 && kc2 >= 30)
//  {
//    if((kc1 < 20))
//    {
//      phai(75);
//      Serial.println("phai");
//    }
//    else if((kc3 < 20))
//    {
//      trai(75);
//      Serial.println("trai");
//    } 
//  } 
  else 
    {
      lui(75);
      Serial.println("dung");
    }

}

void setupSRF05()
{
  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);
  pinMode(trig3, OUTPUT);
  pinMode(echo3, INPUT);
}

void setup() 
{
  Serial3.begin(9600);
  Serial.begin(9600);
  setupSRF05();
  setupxe();
  lcd.init();                    
  lcd.backlight();
  setupNRF24L01();
}

void doSRF05()
{
  digitalWrite(trig1,0);
  delayMicroseconds(2);
  digitalWrite(trig1,1);
  delayMicroseconds(10);
  digitalWrite(trig1,0);

  tg1= pulseIn(echo1, HIGH);
  kc1=int(tg1 * 0.034 / 2 );
  
  digitalWrite(trig2,0);
  delayMicroseconds(2);
  digitalWrite(trig2,1);
  delayMicroseconds(10);
  digitalWrite(trig2,0);

  tg2= pulseIn(echo2, HIGH);
  kc2=int(tg2 * 0.034 / 2 );
  
  digitalWrite(trig3,0);
  delayMicroseconds(2);
  digitalWrite(trig3,1);
  delayMicroseconds(10);
  digitalWrite(trig3,0);
  
  tg3= pulseIn(echo3, HIGH);
  kc3=int(tg3 * 0.034 / 2 );
   if(millis() - t1 > 100)
  { 
    lcd.setCursor(0,1);
    lcd.print(kc1);
    delay(500);
    lcd.setCursor(3,1);
    lcd.print("cm");

    lcd.setCursor(5,0);
    lcd.print(kc2);
    delay(500);
    lcd.setCursor(8,0);
    lcd.print("cm");
    
    lcd.setCursor(11,1);
    lcd.print(kc3);
    delay(500);
    lcd.setCursor(14,1);
    lcd.print("cm");
    t1 = millis();
  }
  

  lcd.setCursor(5,0);
  lcd.print("   ");
  lcd.setCursor(0,1);
  lcd.print("   ");
  lcd.setCursor(11,1);
  lcd.print("   ");

}
void nhanESPvaNRF()
{ 
  const char text7[]="0";
  const char text6[]="1";
  const char text5[]="2";
  const char text4[]="5"; 
  const char text3[]="4";
  const char text2[]="3";
  
  char text[32] = "";
  radio.read(&text, sizeof(text));

  if(Serial3.available() ||  radio.available())
  {
    char c = Serial3.read();
    //Serial.println(c);
    s += c;
    if (c == '\n')
    {
      s = "";
      
    }
      if (c == '1' || strcmp(text, text6) == 0)
      {
          a = '1';
          b = '0';
      }
      if (c == '0' || strcmp(text, text7) == 0)
      { 
          a = '0';
          b = '0';
      }
      if (c == '2' || strcmp(text, text5) == 0)
      {
          b = '2';
      }
      if (c == '3' || strcmp(text, text2) == 0)
      {
          b = '3';
      }
      if (c == '4' || strcmp(text, text3) == 0)
      {
          b = '4';
      }
      if (c == '5' || strcmp(text, text4) == 0)
      {
          b = '5';
      }
      
      d = a + b;
      b = "0";
      Serial.println(d);
  }
}
void dieukhienxe()
{  
   if( a == "0")
    { 
      tudong();
    }
    if ( d == "10")
    {
      dung(100);
      Serial.println("dung");
    }
    if ( d == "12")
    {
      tien(100);
      Serial.println("tien");
      delay(500);
      //dung(100);
    }
    if ( d == "13")
    {
      phai(100);
      Serial.println("phai");
      delay(250);
      //dung(100);
    }
    if ( d == "14")
    {
      trai(100);
      Serial.println("trai");
      delay(250);
      //dung(100);
    }
    if ( d == "15")
    {
      lui(100);
      Serial.println("lui");
      delay(500);
      //dung(100);
    }
}
void loop() 
{ 
  doSRF05();
  nhanESPvaNRF();
  dieukhienxe();
  if(millis() - t1 > 100)
  { s1 = "A" + (String)kc1 + "B" + (String)kc2 + "C" + (String)kc3 + "D";
    Serial3.println(s1);
    delay(100);
    t1 = millis();
  }
  
}

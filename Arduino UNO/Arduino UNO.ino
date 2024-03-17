#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(8, 9); // CE, CSN
const byte diachi[6] = "12345"; //Mảng kí tự dạng chuỗi có 6 kí 

int nutnhan7 = 7;
int nutnhan6 = 6;
int nutnhan5 = 5;
int nutnhan4 = 4;
int nutnhan3 = 3;  
int nutnhan2 = 2;


void setup() 
{
  Serial.begin(9600);
  
  if (!radio.begin()) 
  {
    Serial.println("Module không khởi động được...!!");
    while (1) {}
  } 
  
  radio.openWritingPipe(diachi);
  radio.setPALevel(RF24_PA_MIN); 
  radio.stopListening(); //Cài đặt module là TX
  
  if (!radio.available())
  {
    Serial.println("Chưa kết nối được với RX...!!");
    Serial.println("CHỜ KẾT NỐI.......");
  }  

  pinMode(nutnhan7, INPUT_PULLUP);
  pinMode(nutnhan6, INPUT_PULLUP);
  pinMode(nutnhan5, INPUT_PULLUP);
  pinMode(nutnhan4, INPUT_PULLUP);
  pinMode(nutnhan3, INPUT_PULLUP);
  pinMode(nutnhan2, INPUT_PULLUP);
}

void loop() 
{
  int gtnutnhan7 = digitalRead(nutnhan7);
  int gtnutnhan6 = digitalRead(nutnhan6);
  int gtnutnhan5 = digitalRead(nutnhan5);
  int gtnutnhan4 = digitalRead(nutnhan4);
  int gtnutnhan3 = digitalRead(nutnhan3);
  int gtnutnhan2 = digitalRead(nutnhan2);

  const char text7[]="0";
  const char text6[]="1";
  const char text5[]="2";
  const char text4[]="5"; 
  const char text3[]="4";
  const char text2[]="3";
  const char text1[]="6";
  
  if(gtnutnhan7 == 0)
    { 
       radio.write(&text7, sizeof(text7));
       //delay(500);
    }
  if(gtnutnhan6 == 0)
    { 
       radio.write(&text6, sizeof(text6));
       //delay(500);
    }
    if(gtnutnhan5 == 0)
    { 
       radio.write(&text5, sizeof(text5));
       //Serial.println(text5);
      // delay(500);
    }
  if(gtnutnhan4 == 0)
    { 
       radio.write(&text4, sizeof(text4));
       //delay(500);
    }
  if(gtnutnhan3 == 0)
    { 
       radio.write(&text3, sizeof(text3));
       //delay(500);
    }
  if(gtnutnhan2 == 0)
    { 
       radio.write(&text2, sizeof(text2));
       //delay(500);
    }
  radio.write(&text1, sizeof(text1));
}

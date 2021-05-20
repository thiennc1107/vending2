#include <Keypad.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <stdlib.h>
LiquidCrystal_I2C lcd(0x3F,20,4);

 
const byte rows = 4; //số hàng
const byte columns = 4; //số cột
 
int holdDelay = 700; //Thời gian trễ để xem là nhấn 1 nút nhằm tránh nhiễu
int n = 3; // 
int state = 0; //nếu state =0 ko nhấn,state =1 nhấn thời gian nhỏ , state = 2 nhấn giữ lâu
char key = 0;
 
//Định nghĩa các giá trị trả về
char keys[rows][columns] =
{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'},
};
 
byte rowPins[rows] = {9, 8, 7, 6}; //Cách nối chân với Arduino
byte columnPins[columns] = {5, 4, 3, 2};
int number =0;
//cài đặt thư viện keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, columnPins, rows, columns);
void setup() {
  
  lcd.init();                    
  lcd.backlight();
  lcd.setCursor(2,0);
  lcd.print("Nhap so");
   lcd.setCursor(1,2);
  lcd.print("00");
  pinMode(10,INPUT);
  pinMode(11,INPUT);
  for(int i= 22;i<49;i++)
  {
    pinMode(i,OUTPUT);
    digitalWrite(i,HIGH);
  }
  
}
void loop() {  
  char temp = keypad.getKey();
 
  if ((int)keypad.getState() ==  PRESSED) {
    if (temp != 0) {
      key = temp;
      String keystring = String(key);
      if(key !='*' && key != '#')
      {
        if (number ==0)
        {
          number = number + keystring.toInt();
        }
        else if(number<10 && number>0)
        {
          number = number*10 + keystring.toInt();
        }
      }
      else if (key =='*')
      {
        number =0;
        
      }
      else if (key == '#')
      {
        drop();
      }
    }
      
    hienthi();
      
  }
  delay(100);
  }
  void hienthi()
  { 
    String stringNumber = String(number);
    if(number <10)
    {
      lcd.setCursor(2,2);
      lcd.print(stringNumber);
      lcd.setCursor(1,2);
      lcd.print("0");
    }
    else 
    {
      lcd.setCursor(1,2);
      lcd.print(stringNumber);
    }
  }
 void drop()
{
  lcd.setCursor(0,3);
  lcd.print("vui long doi");
  digitalWrite(number+21,LOW);
  delay(3000);
  digitalWrite(number+21,HIGH);
  lcd.setCursor(0,3);
  lcd.print("            ");
  number = 0;
  

}
  

//#include <TimerOne.h>
#include <Keypad.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <stdlib.h>
#include <Adafruit_Fingerprint.h>
#define mySerial Serial1
LiquidCrystal_I2C lcd(0x27,16,2);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
const byte rows = 4; //số hàng
const byte columns = 4; //số cột
 
int holdDelay = 700; //Thời gian trễ để xem là nhấn 1 nút nhằm tránh nhiễu
int n = 3; // 
int state = 0; //nếu state =0 ko nhấn,state =1 nhấn thời gian nhỏ , state = 2 nhấn giữ lâu
char key = 0;
int flag = 0;


 
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
int verifyFingerprint() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.confidence ;
  if( p <50) return -1;

  return 1;
}
void dropSecond(int ID)
{

  lcd.setCursor(0,0);
  lcd.print("vui long doi    ");
  String signal = String(ID);
  Serial.println(ID);
  String data = "";
  while (1) {
     if (Serial.available() > 0) {
    // read the incoming byte:
    data = Serial.readString();
    if(data == "hethang")
    {
      lcd.setCursor(0,0);
      lcd.print("San pham da het hang    ");
      delay(3000);
      break;
    }
    if(data=="xong")
    {
      lcd.setCursor(0,0);
      lcd.print("xong          ");
      delay(3000);
      break;
    }
    }
  }
  
} 


void enrollFingerprint()
{
  int id = number;
  if(id>127){
    lcd.setCursor(0,0);
    lcd.print("qua tai bo nho");
  }
  int p = -1;
  lcd.setCursor(0,0);
  lcd.print("dang ghi     "); 
  lcd.print(id);
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
  }
  p = finger.image2Tz(1);
  if (p != FINGERPRINT_OK){
    lcd.setCursor(0,0);
    lcd.print("            ");
    lcd.setCursor(0,0);
    lcd.print("Loi");
    return ;
  }
  lcd.setCursor(0,0);
  lcd.print("            ");
  lcd.setCursor(0,0);
  lcd.print("thao ngon tay ra");
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }
  lcd.setCursor(0,0);
  lcd.print("              ");
  lcd.setCursor(0,0);
  lcd.print("dat lai ngon tay");
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
  }
  p = finger.image2Tz(2);
  if (p != FINGERPRINT_OK){
    lcd.setCursor(0,0);
    lcd.print("            ");
    lcd.setCursor(0,0);
    lcd.print("Loi");
    return ;
  }
  p = finger.createModel();
  if (p != FINGERPRINT_OK)  return -1;
  p = finger.storeModel(id);
  if (p != FINGERPRINT_OK)  return -1;   
  lcd.setCursor(0,0);
  lcd.print("                   ");
  lcd.setCursor(0,0);
  lcd.print("da luu xong"); 
  delay(3000);
  number =0;
}


 void drop()
{
  bool flag=0;
  lcd.setCursor(0,0);
  delay(10);
  lcd.print("vui long doi    ");
  digitalWrite(number+21,LOW);
  int i = 0;
  while(digitalRead(11)==1&&digitalRead(10)==1)
  {
    delay(10);
    i++;
    if(i == 500)
    {
      lcd.setCursor(0,0);
      lcd.print("San pham da het hang    ");
      flag = 1;
      delay(3000);
      break;
    }
  }
  digitalWrite(number+21,HIGH);
  if(flag == 0)
  {
     lcd.setCursor(0,0);
    lcd.print("done              ");
    delay(3000);
  }
}



void hienthi()
  { 
    String stringNumber = String(number);
    if(number <10)
    {
      lcd.setCursor(2,1);
      lcd.print(stringNumber);
      lcd.setCursor(1,1);
      lcd.print("0");
    }
    else 
    {
      lcd.setCursor(1,1);
      lcd.print(stringNumber);
    }
}



void setup() {
  Serial.begin(9600);
  lcd.init();                    
  lcd.backlight();
  finger.begin(57600);
  delay(5);
  if (finger.verifyPassword()) {
    lcd.setCursor(0,0);
    lcd.print("Nhap van tay   ");
  } else {
    lcd.setCursor(0,0);
    lcd.print("Khong tim thay cam bien van tay");
    while (1) { delay(1); }
  }
  //Timer1.initialize(5000000);
  //Timer1.attachInterrupt(outOfStock_handle);
  pinMode(10,INPUT);
  pinMode(11,INPUT);
  for(int i= 22;i<50;i++)
  {
    pinMode(i,OUTPUT);
    digitalWrite(i,HIGH);
  }
  
}
void loop() {  
   int flag =0;
   lcd.setCursor(0,0);
   lcd.print("Nhap van tay    ");
   lcd.setCursor(1,1);
    lcd.print("00");
   int fingerVerify =0;
   while(fingerVerify !=1)
  {
    fingerVerify=verifyFingerprint();
    delay(10);
  }
    
    int ID = finger.fingerID; 
    while(1)
    {
      lcd.setCursor(0,0);
      lcd.print("Nhap so        ");
      int flag = 0;
      char temp = keypad.getKey();
 
      if ((int)keypad.getState() ==  PRESSED) {
        if (temp != 0) 
        {
          key = temp;
          String keystring = String(key);
          if(key !='*' && key != '#'&& key != 'A' && key != 'B')
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
            if(number>28||number<1)
            {
              lcd.setCursor(0,0);
              lcd.print("So khong hop le           ");
              delay(3000);
            }
            else
            {
              drop();
              dropSecond(ID);
            }
          }
          else if (key == 'A')
          {
            number =0;
            flag =1;
          }
          else if (key == 'B' && ID ==1)
          {
            if(number<1||number>127)
            {
              lcd.setCursor(0,0);
              lcd.print("So khong hop le       ");
            }
            else
            {
              enrollFingerprint();
            }
          }
        }     
        hienthi();    
      }
      if(flag==1) break;
    }
    delay(10);
   }
  

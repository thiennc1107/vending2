void drop(int number)
{
  digitalWrite(number+21,LOW);
  int i = 0;
  while(digitalRead(11)==1&&digitalRead(10)==1)
  {
    delay(10);
    i++;
    if(i == 500)
    {
      Serial.println("hethang");
      delay(3000);
      break;
    }
  }
  Serial.println("xong");
  digitalWrite(number+21,HIGH);
}


void setup()
{
  for(int i= 22;i<50;i++)
  {
    pinMode(i,OUTPUT);
    digitalWrite(i,HIGH);
  }
  Serial.begin(9600);
}
void loop() {
  // reply only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    //String data = Serial.readString();
    int number = Serial.read();
    drop(number);
    Serial.println(number);
  }

    
 }

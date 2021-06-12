int stock[4][4];
int col[4];
void drop(int number)
{
  bool flag = 0;
  digitalWrite(number+21,LOW);
  int i = 0;
  while(digitalRead(11)==1&&digitalRead(10)==1)
  {
    delay(10);
    i++;
    if(i == 500)
    {
      Serial1.write("hethang");
      delay(3000);
      flag = 1;
      break;
    }
  }
  digitalWrite(number+21,HIGH);
  if(flag==0)
  {
    Serial1.write("xong");
  }
}

int findStock(int ID)
{
  int row = ID/25;
  if(stock[row][col[row]] ==0) 
  col[row]++;
  drop(row*0+col[row]);
  stock[row][col[row]]--;
}



void setup()
{
  for(int i= 22;i<50;i++)
  {
    pinMode(i,OUTPUT);
    digitalWrite(i,HIGH);
  }
  Serial1.begin(9600);
  Serial.begin(9600);
  for(int i=0;i<4;i++)
  {
    col[i] = 0;
    for(int j=0;j<4;j++)
    {
      stock[i][j] =7;
    }
  }
}
void loop() {
  // reply only when you receive data:
  if (Serial1.available() > 0) {
    // read the incoming byte:
    String data = Serial1.readString();
    int number = data.toInt();
    drop(number);
  }

    
 }

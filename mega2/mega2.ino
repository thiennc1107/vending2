int stock[4][4];
int col[4];
bool drop(int number)
{
  digitalWrite(number+21,LOW);
  int i = 0;
  while(digitalRead(11)==1&&digitalRead(10)==1)
  {
    delay(10);
    i++;
    if(i == 500)
    {
     digitalWrite(number+21,HIGH);
     return 0;
     
    }
  }
  digitalWrite(number+21,HIGH);
  Serial1.write("xong");
  return 1;
}

void findStock(int ID)
{
  Serial.println(ID);
  int row = ID/250;
  Serial.println(row);
  if(stock[row][col[row]] ==0&&col[row]<3) 
  {
    col[row]++;
  }
  
  Serial.println(col[row]);
  stock[row][col[row]]--;
  Serial.println(stock[row][col[row]]);
  Serial.println(row*4+col[row]+1);
  bool flag = drop(row*4+col[row]+1);
  while(flag==0)
  {
   
    if(col[row]<3)
    {
      col[row]++;
      flag = drop(row*4+col[row]+1);
    }
    else
    {
      Serial1.write("hethang");
      break;
    }
  }
  
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
    findStock(number);
  }

    
 }

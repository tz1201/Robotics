//for wheel
#define E1 2
#define E2 3
#define E3 4
#define D1A 22
#define D1B 24
#define D2A 26
#define D2B 28
#define D3A 30
#define D3B 32

char data = 0; //Variable for storing received data
char data1 = 0; //Variable for storing received data
void setup()
{


  Serial.begin(9600); //Sets the baud for serial data transmission

  Serial1.begin(9600); //Sets the baud for serial data transmission
  pinMode(13, OUTPUT); //Sets digital pin 13 as output pin
  pinMode(E1, OUTPUT);
  pinMode(E2, OUTPUT);
  pinMode(E3, OUTPUT);
  pinMode(D1A, OUTPUT);
  pinMode(D1B, OUTPUT);
  pinMode(D2A, OUTPUT);
  pinMode(D2B, OUTPUT);
  pinMode(D3A, OUTPUT);
  pinMode(D3B, OUTPUT);
}
void loop()
{
  if (Serial.available() > 0) // Send data only when you receive data:
  {
    data = Serial.read();        //Read the  incoming  data and store it into variable data
    Serial.print(data);          //Print Value inside data in Serial monitor
    if (data == 'H') {
      digitalWrite(E3, HIGH);
      digitalWrite(D3A, HIGH);
      digitalWrite(D3B, LOW);
      digitalWrite(E2, HIGH);
      digitalWrite(D2A, LOW);
      digitalWrite(D2B, HIGH);
      digitalWrite(E1, LOW);// Checks whether value of data is equal to 1
      digitalWrite(13, HIGH);
    }   //If value is 1 then LED turns ON
    else if (data == 'L')    {    //  Checks  whether value of data is equal to 0
      digitalWrite(E1, LOW);
      digitalWrite(E2, LOW);
      digitalWrite(E3, LOW);
      digitalWrite(13, LOW);    //If value is 0 then LED turns OFF
    }
  }


  if (Serial1.available() > 0) // Send data only when you receive data:
  {
    data1 = Serial1.read();        //Read the  incoming  data and store it into variable data
    Serial1.print(data1);          //Print Value inside data in Serial monitor
    if (data1 == 'H') {
      digitalWrite(E3, HIGH);
      digitalWrite(D3A, HIGH);
      digitalWrite(D3B, LOW);
      digitalWrite(E2, HIGH);
      digitalWrite(D2A, LOW);
      digitalWrite(D2B, HIGH);
      digitalWrite(E1, LOW);// Checks whether value of data is equal to 1
      digitalWrite(13, HIGH);
    }   //If value is 1 then LED turns ON
    else if (data1 == 'L')    {    //  Checks  whether value of data is equal to 0
      digitalWrite(E1, LOW);
      digitalWrite(E2, LOW);
      digitalWrite(E3, LOW);
      digitalWrite(13, LOW);    //If value is 0 then LED turns OFF
    }
  }
}

#define SLAVE_ADDR1 1 // streetlight
#define SLAVE_ADDR3 3 // rfid
#define SLAVE_ADDR4 4 // rfid
#define ANSWERSIZE 3 // number of bytes to receive

#include<Wire.h> // I2C library
byte receiveData[ANSWERSIZE] = {4,4,4}; // array to receive data for traffic density
byte receiveRfid3[ANSWERSIZE] = {0,0,0}; // array to receive data from rfid1
byte receiveRfid4[ANSWERSIZE] = {0,0,0}; // array to receive data from rfid2

const int signals[3] = {11,12,13}; // signals for traffic lights

int currVal[3] = {0,0,0}; // current values of traffic density
int indices[3]; // indices of traffic density

byte seven_seg_digits[10][7] = { { 0,0,0,0,0,0,1 },  // = 0
                                 { 1,0,0,1,1,1,1 },  // = 1
                                 { 0,0,1,0,0,1,0 },  // = 2
                                 { 0,0,0,0,1,1,0 },  // = 3
                                 { 1,0,0,1,1,0,0 },  // = 4
                                 { 0,1,0,0,1,0,0 },  // = 5
                                 { 0,1,0,0,0,0,0 },  // = 6
                                 { 0,0,0,1,1,1,1 },  // = 7
                                 { 0,0,0,0,0,0,0 },  // = 8
                                 { 0,0,0,1,1,0,0 }   // = 9
                                                           };

void sevenSegWrite(byte digit) { // function to write to seven segment display
  byte pin = 2;

  for (byte segCount = 0; segCount < 7; ++segCount) { // loop to write to seven segment display
    digitalWrite(pin, !seven_seg_digits[digit][segCount]); 
    ++pin; 
    }

}

void setup() {
  Serial.begin(9600); // Starts the serial communication
  pinMode(signals[0],OUTPUT); //these are to setup the three traffic signals 
  pinMode(signals[1],OUTPUT);  
  pinMode(signals[2],OUTPUT);  
  digitalWrite(signals[0],LOW); //initially all traffic signals are red
  digitalWrite(signals[1],LOW);
  digitalWrite(signals[2],LOW);

  Wire.begin(); // join i2c bus
}

void sortArrayWithIndices(int values[], int indices[]) { // function to sort array
  for (int i = 0; i < 3; i++) { // initialize indices to 0, 1, 2
    indices[i] = i;
  }

  for (int i = 0; i < 2; i++) { // bubble sort
    for (int j = 0; j < 2 - i; j++) {
      if (values[indices[j]] > values[indices[j + 1]]) {
        // Swap indices
        int temp = indices[j];
        indices[j] = indices[j + 1];
        indices[j + 1] = temp;
      }
    }
  }
}
int i; // counter
void loop() {
  i=0; // initialize counter
  int sum = receiveData[0]+receiveData[1]+receiveData[2]; // total traffic density
  currVal[0] = receiveData[0]*9/sum; // receive data from master and allocate proper time for each traffic signal
  currVal[1] = receiveData[1]*9/sum; 
  currVal[2] = receiveData[2]*9/sum;

  // delay(1000);
  sortArrayWithIndices(currVal,indices); // sort array and give the array in descending order

  int signal1 = signals[indices[2]]; // get signal 1 for traffic light
  int val1 = currVal[indices[2]]; // get value 1 for traffic light
  int signal2 = signals[indices[1]]; // get signal 2 for traffic light
  int val2 = currVal[indices[1]]; // get value 2 for traffic light
  int signal3 = signals[indices[0]]; // get signal 3 for traffic light
  int val3 = currVal[indices[0]]; // get value 3 for traffic light

  digitalWrite(signal1,HIGH);
  for(int i=0;i<val1;i++){ // loop to write to seven segment display1
    sevenSegWrite(val1-i);
    delay(1000);

    Wire.requestFrom(SLAVE_ADDR3,3); // request 3 bytes from slave device #3(rfid1)
    Serial.println("addr3"); 
    int j=0; // counter
    while(Wire.available()){ // loop to receive data
      receiveRfid3[j] = Wire.read();
      Serial.println(receiveRfid3[j]);
      j++;
    }
    delay(50);
    Serial.println("addr4");
    Wire.requestFrom(SLAVE_ADDR4,3); // request 3 bytes from slave device #4(rfid2)
    j=0;
    while(Wire.available()){ // loop to receive data
      receiveRfid4[j] = Wire.read();
      Serial.println(receiveRfid4[j]);
      j++;
    }
    delay(50);
    Serial.println("=============================================================");
    for(int k = 0; k < 3; k++) // loop to print data
    {
      Serial.println(receiveRfid3[k]);
    }
    Serial.println("=============================================================");
    if(receiveRfid3[0]){ // if incoming rfid is detected
      Serial.println("lklkl");
      digitalWrite(signal1,LOW);
      digitalWrite(11,HIGH); 
      sevenSegWrite(9); 
      int m = 0; 
      while(receiveRfid4[2]==0 && receiveRfid3[1]==0 && receiveRfid4[1]==0){ // loop to wait for outgoing rfid to be detected
        delay(500);
        Wire.requestFrom(SLAVE_ADDR4,3); // request 3 bytes from slave device #4(rfid2)
        m=0;
        while(Wire.available()){ 
          receiveRfid4[m] = Wire.read(); 
          m++;
          }
        delay(50);
        Wire.requestFrom(SLAVE_ADDR3,3); // request 3 bytes from slave device #3(rfid1)
        m=0;
        while(Wire.available()){
          receiveRfid3[m]=Wire.read();
          m++;
        }
      }
      digitalWrite(11,LOW);
      break;
    }
    else if(receiveRfid3[2]){ // if incoming rfid is detected
      Serial.println("lklkl");
      digitalWrite(signal1,LOW);
      digitalWrite(12,HIGH);
      sevenSegWrite(9);
      int m = 0;
      while(receiveRfid4[2]==0 && receiveRfid3[1]==0 && receiveRfid4[1]==0){ // loop to wait for outgoing rfid to be detected
        delay(500);
        Wire.requestFrom(SLAVE_ADDR4,3); // request 3 bytes from slave device #4(rfid2)
        m=0;
        while(Wire.available()){
          receiveRfid4[m] = Wire.read();
          m++;
          }
        delay(50);
        Wire.requestFrom(SLAVE_ADDR3,3); // request 3 bytes from slave device #3(rfid1)
        m=0;
        while(Wire.available()){
          receiveRfid3[m]=Wire.read();
          m++;
        }
      }
      digitalWrite(12,LOW);
      break;
    }
    else if(receiveRfid4[0]){ // if incoming rfid is detected
      Serial.println("lklkl");
      digitalWrite(signal1,LOW);
      digitalWrite(13,HIGH);
      sevenSegWrite(9);
      int m = 0;
      while(receiveRfid4[2]==0 && receiveRfid3[1]==0 && receiveRfid4[1]==0){ // loop to wait for outgoing rfid to be detected
        delay(500);
        Wire.requestFrom(SLAVE_ADDR4,3); // request 3 bytes from slave device #4(rfid2)
        m=0;
        while(Wire.available()){
          receiveRfid4[m] = Wire.read();
          m++;
          }
        delay(50);
        Wire.requestFrom(SLAVE_ADDR3,3); // request 3 bytes from slave device #3(rfid1)
        m=0;
        while(Wire.available()){
          receiveRfid3[m]=Wire.read();
          m++;
        }
      }
      digitalWrite(13,LOW);
      break;
    }

  }
  digitalWrite(signal1,LOW);
  
  digitalWrite(signal2,HIGH);
  for(int i=0;i<val2;i++){ // loop to write to seven segment display2
    sevenSegWrite(val2-i);
    delay(1000);

    int j=0;
    Wire.requestFrom(SLAVE_ADDR3,3); // request 3 bytes from slave device #3(rfid)
    Serial.println("addr3");
    while(Wire.available()){ // loop to receive data
      receiveRfid3[j] = Wire.read();
      Serial.println(receiveRfid3[j]); 
      j++;
    }
    delay(50);
    Wire.requestFrom(SLAVE_ADDR4,3); // request 3 bytes from slave device #4(rfid)
    Serial.println("addr4");
    j=0; 
    while(Wire.available()){ // loop to receive data
      receiveRfid4[j] = Wire.read();
      Serial.println(receiveRfid4[j]);
      j++;
    }
    delay(50);
    Serial.println("=============================================================");
    for(int k = 0; k < 3; k++)
    {
      Serial.println(receiveRfid3[k]);
    }
    Serial.println("=============================================================");
    if(receiveRfid3[0]==1){
      Serial.println("hmmhmm");
    }
if(receiveRfid3[0]){ // if incoming rfid is detected
      Serial.println("lklkl");
      digitalWrite(signal2,LOW);
      digitalWrite(11,HIGH);
      sevenSegWrite(9);
      int m = 0;
      while(receiveRfid4[2]==0 && receiveRfid3[1]==0 && receiveRfid4[1]==0){ // loop to wait for outgoing rfid to be detected
        delay(500);
        Wire.requestFrom(SLAVE_ADDR4,3); // request 3 bytes from slave device #4(rfid)
        m=0;
        while(Wire.available()){ 
          receiveRfid4[m] = Wire.read();
          m++;
          }
        delay(50);
        Wire.requestFrom(SLAVE_ADDR3,3); // request 3 bytes from slave device #3(rfid)
        m=0;
        while(Wire.available()){ 
          receiveRfid3[m]=Wire.read();
          m++;
        }
      }
      digitalWrite(11,LOW);
      break;
    }
    else if(receiveRfid3[2]){ // if incoming rfid is detected
      Serial.println("lklkl");
      digitalWrite(signal2,LOW);
      digitalWrite(12,HIGH);
      sevenSegWrite(9);
      int m = 0;
      while(receiveRfid4[2]==0 && receiveRfid3[1]==0 && receiveRfid4[1]==0){ // loop to wait for outgoing rfid to be detected
        delay(500);
        Wire.requestFrom(SLAVE_ADDR4,3); // request 3 bytes from slave device #4(rfid)
        m=0;
        while(Wire.available()){ 
          receiveRfid4[m] = Wire.read();
          m++;
          }
        delay(50);
        Wire.requestFrom(SLAVE_ADDR3,3); // request 3 bytes from slave device #3(rfid)
        m=0;
        while(Wire.available()){ 
          receiveRfid3[m]=Wire.read();
          m++;
        }
      }
      digitalWrite(12,LOW);
      break;
    }
    else if(receiveRfid4[0]){ // if incoming rfid is detected
      Serial.println("lklkl");
      digitalWrite(signal2,LOW);
      digitalWrite(13,HIGH);
      sevenSegWrite(9);
      int m = 0;
      while(receiveRfid4[2]==0 && receiveRfid3[1]==0 && receiveRfid4[1]==0){ // loop to wait for outgoing rfid to be detected
        delay(500);
        Wire.requestFrom(SLAVE_ADDR4,3); // request 3 bytes from slave device #4(rfid)
        m=0;
        while(Wire.available()){ 
          receiveRfid4[m] = Wire.read();
          m++;
          }
        delay(50);
        Wire.requestFrom(SLAVE_ADDR3,3); // request 3 bytes from slave device #3(rfid)
        m=0;
        while(Wire.available()){ 
          receiveRfid3[m]=Wire.read();
          m++;
        }
      }
      digitalWrite(13,LOW);
      break;
    }

  }
  digitalWrite(signal2,LOW);
  digitalWrite(signal3,HIGH);
  for(int i=0;i<val3;i++){ // loop to write to seven segment display3
    sevenSegWrite(val3-i);
    delay(1000);


    Wire.requestFrom(SLAVE_ADDR3,3); // request 3 bytes from slave device #3(rfid)
    Serial.println("addr3");
    int j=0;
    while(Wire.available()){ // loop to receive data
      receiveRfid3[j] = Wire.read();
      Serial.println(receiveRfid3[j]);
      j++;
    }
    delay(50);
    Serial.println("addr4");
    Wire.requestFrom(SLAVE_ADDR4,3); // request 3 bytes from slave device #4(rfid)
    j=0;
    while(Wire.available()){ // loop to receive data
      receiveRfid4[j] = Wire.read();
      Serial.println(receiveRfid4[j]);
      j++;
    } 
    delay(50);
    Serial.println("=============================================================");
    for(int k = 0; k < 3; k++)
    {
      Serial.println(receiveRfid3[k]);
    }
    Serial.println("=============================================================");
    if(receiveRfid3[0]==1){
      Serial.println("hmmhmm");
    }

  if(receiveRfid3[0]){ // if incoming rfid is detected
      Serial.println("lklkl");
      digitalWrite(signal3,LOW);
      digitalWrite(11,HIGH);
      sevenSegWrite(9);
      int m = 0;
      while(receiveRfid4[2]==0 && receiveRfid3[1]==0 && receiveRfid4[1]==0){ // loop to wait for outgoing rfid to be detected
        delay(500);
        Wire.requestFrom(SLAVE_ADDR4,3); // request 3 bytes from slave device #4(rfid)
        m=0;
        while(Wire.available()){
          receiveRfid4[m] = Wire.read();
          m++;
          }
        delay(50);
        Wire.requestFrom(SLAVE_ADDR3,3); // request 3 bytes from slave device #3(rfid)
        m=0;
        while(Wire.available()){
          receiveRfid3[m]=Wire.read();
          m++;
        }
      }
      digitalWrite(11,LOW);
      break;
    }
    else if(receiveRfid3[2]){ // if incoming rfid is detected
      Serial.println("lklkl");
      digitalWrite(signal3,LOW);
      digitalWrite(12,HIGH);
      sevenSegWrite(9);
      int m = 0;
      while(receiveRfid4[2]==0 && receiveRfid3[1]==0 && receiveRfid4[1]==0){ // loop to wait for outgoing rfid to be detected
        delay(500);
        Wire.requestFrom(SLAVE_ADDR4,3); // request 3 bytes from slave device #4(rfid)
        m=0;
        while(Wire.available()){
          receiveRfid4[m] = Wire.read();
          m++;
          }
        delay(50);
        Wire.requestFrom(SLAVE_ADDR3,3); // request 3 bytes from slave device #3(rfid)
        m=0;
        while(Wire.available()){ 
          receiveRfid3[m]=Wire.read();
          m++;
        }
      }
      digitalWrite(12,LOW);
      break;
    }
    else if(receiveRfid4[0]){ // if incoming rfid is detected
      Serial.println("lklkl");
      digitalWrite(signal3,LOW);
      digitalWrite(13,HIGH);
      sevenSegWrite(9);
      int m = 0;
      while(receiveRfid4[2]==0 && receiveRfid3[1]==0 && receiveRfid4[1]==0){ // loop to wait for outgoing rfid to be detected
        delay(500);
        Wire.requestFrom(SLAVE_ADDR4,3); // request 3 bytes from slave device #4(rfid)
        m=0;
        while(Wire.available()){ 
          receiveRfid4[m] = Wire.read();
          m++;
          }
        delay(50);
        Wire.requestFrom(SLAVE_ADDR3,3); // request 3 bytes from slave device #3(rfid)
        m=0;
        while(Wire.available()){ 
          receiveRfid3[m]=Wire.read();
          m++;
        }
      }
      digitalWrite(13,LOW);
      break;
    }
  }
  digitalWrite(signal3,LOW); 

  Serial.println("Addr1------------");
  Wire.requestFrom(SLAVE_ADDR1,3); // request 3 bytes from slave device #1(streetlight/traffic density)
  while(Wire.available()){ // loop to receive data
        receiveData[i]=Wire.read();
        Serial.println(receiveData[i]);
        i++;
  }
}
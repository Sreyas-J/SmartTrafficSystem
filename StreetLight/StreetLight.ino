#include<Servo.h> // servo library
#include<Wire.h> // I2C library
#define SLAVE_ADDR2 1 // I2C address
#define ANSWERSIZE 3 // no of bytes to be sent
int density1=4,density2=4,density3=4; // traffic density

const int trigPin = 5; // Trigger Pin of Ultrasonic Sensor
const int echoPin1 = A0; // Echo Pin 1 of Ultrasonic Sensor
const int echoPin2 = A1; // Echo Pin 2 of Ultrasonic Sensor
const int echoPin3 = A2; // Echo Pin 3 of Ultrasonic Sensor

long duration; 
int distance; // Variable for distance measurement  

Servo servo1; // servo object 1
Servo servo2; // servo object 2
Servo servo3; // servo object 3

void requestEvent(){ // function to send data to master
  int total=density1+density2+density3; // total traffic density
  Serial.print(density1);
  Serial.print(" work! ");
  Serial.print(density2);
  Serial.print(" work@ ");
  Serial.print(density3);
  Serial.print(" work# ");
  Serial.print("==================================================");
  byte response[ANSWERSIZE]={density1,density2,density3}; // array to send data
//  byte response[ANSWERSIZE] = {(density1*9)/total,(density2*9)/total,(density3*9)/total};
//  Serial.println("request");
//  for(int i=0;i<3;i++){
//    Serial.print(response[i]);
//    Serial.print(" ");
//  }
  Serial.println(); 

  Wire.write(response,ANSWERSIZE); // send data to master

//  for(int i=0;i<3;i++){
//    Serial.print(response[i]);
//    Serial.print(" ");
//  }
  Serial.println();
}

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin1, INPUT); // Sets the echoPin 1 as an Input for ultrasonic
  pinMode(echoPin2, INPUT); // Sets the echoPin 2 as an Input for ultrasonic
  pinMode(echoPin3, INPUT); // Sets the echoPin 3 as an Input for ultrasonic
  
  Serial.begin(9600); // Starts the serial monitor baud rate
  servo3.attach(3); //3
  servo1.attach(4); //1
  servo2.attach(6); //2

  Wire.begin(SLAVE_ADDR2); // join i2c bus with address SLAVE_ADDR2
  Wire.onRequest(requestEvent); // i2c request event
}

bool ultrasonic(int normal_dist,int echoPin){ // function to measure distance
  int count=0,max_c=0; // variables that determine if a vehicle is detected by the ultrasonic sensor
  delay(1000);
  int dist[20]; // array to store distance
  for(int i=0;i<20;i++){ // loop to measure distance 20 times
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
    distance = duration * 0.034 / 2;
    // Prints the distance on the Serial Monitor
    if(echoPin==echoPin1){
     Serial.print("Distance1: ");
     }
    else if(echoPin==echoPin2){
     Serial.print("Distance2: "); 
    }
    else{
      Serial.print("Distance3: "); 
    }
     Serial.println(distance); 
    dist[i]=distance; // storing distance in array
    delay(25);
  }  

  for(int i=0;i<20;i++){ // loop to check if vehicle is present
      if(dist[i]<normal_dist && dist[i]>5){ // if distance is less than normal distance and ignoring garbage readings 
        count++; // increment count
        if(count>max_c) max_c=count; // store max number of times a vehicle was detected continously
      }
      else{ // if no vehicle is detected
        count=0;
      }
    }

   if(max_c>5){ 
    Serial.println("True");
    return true;
   }
   else{
    Serial.println("False");
    return false;
   }
}

int traffic_density(bool arr[]){ // function to calculate traffic density
  if(arr[0]){ 
    return 3;
  }
  else if(arr[1]){
    return 2;
  }
  else if(arr[2]){ 
    return 1;
  }
  else{ 
    return 0;
  }
}

void loop() {
  bool traffic1[3]; // array to store vehicle detection at one side of a junction
  bool traffic2[3];
  bool traffic3[3];
  
  servo1.write(0); // rotate servo 1 to 0 degree
  servo2.write(0); // rotate servo 2 to 0 degree
  servo3.write(0); // rotate servo 3 to 0 degree
  delay(1500);
  
  traffic1[0]=ultrasonic(60,echoPin1); // measure distance
  traffic2[0]=ultrasonic(60,echoPin2);
  traffic3[0]=ultrasonic(60,echoPin3);

  servo1.write(60); // rotate servo 1 to 60 degree
  servo2.write(70); // rotate servo 2 to 70 degree
  servo3.write(60); // rotate servo 3 to 60 degree 
  delay(1500);
  
  traffic1[1]=ultrasonic(26,echoPin1); // measure distance
  traffic2[1]=ultrasonic(25,echoPin2);
  traffic3[1]=ultrasonic(25,echoPin3);

  servo1.write(130); // rotate servo 1 to 130 degree
  servo2.write(140); // rotate servo 2 to 140 degree
  servo3.write(110); // rotate servo 3 to 110 degree
  delay(1500);
  
  traffic1[2]=ultrasonic(60,echoPin1); // measure distance
  traffic2[2]=ultrasonic(60,echoPin2);
  traffic3[2]=ultrasonic(60,echoPin3);
  
  density1=traffic_density(traffic1); //traffic density at a junction side
  Serial.print("d1 ");
  Serial.println(density1);

  density2=traffic_density(traffic2);
  Serial.print("d2 ");
  Serial.println(density2); s

  density3=traffic_density(traffic3); 
  Serial.print("d3 "); 
  Serial.println(density3); 
}

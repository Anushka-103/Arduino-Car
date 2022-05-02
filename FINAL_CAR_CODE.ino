#define ENA   14          // Enable/speed motors Right        GPIO14(D5)
#define ENB   12          // Enable/speed motors Left         GPIO12(D6)
#define IN_1  15          // L298N in1 motors Rightx          GPIO15(D8)
#define IN_2  13          // L298N in2 motors Right           GPIO13(D7)
#define IN_3  2           // L298N in3 motors Left            GPIO2(D4)
#define IN_4  0           // L298N in4 motors Left            GPIO0(D3)

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

String command;             //String to store app command state.
int speedCar = 400;         // 400 - 1023.
//int speed_Coeff = 3;

const char* ssid = "VISITOR";
const char* password = "123456";
ESP8266WebServer server(80);

void setup() {
 
 //pinMode(ENA, OUTPUT);
 //pinMode(ENB, OUTPUT);  
 pinMode(IN_1, OUTPUT);
 pinMode(IN_2, OUTPUT);
 pinMode(IN_3, OUTPUT);
 pinMode(IN_4, OUTPUT); 
  
  Serial.begin(115200);
  
// Connecting WiFi

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
 
 // Starting WEB-server 
     server.on ( "/", HTTP_handleRoot );
     server.onNotFound ( HTTP_handleRoot );
     server.begin();    
}

void goAhead(){ 

      analogWrite(IN_1, 0);
      analogWrite(IN_2, speedCar);
      //analogWrite(ENA, speedCar);

      analogWrite(IN_3, 0);
      analogWrite(IN_4, speedCar);
      //analogWrite(ENB, speedCar);
  }

void goBack(){ 

      analogWrite(IN_1, speedCar);
      analogWrite(IN_2, 0);
      //analogWrite(ENA, speedCar);

      analogWrite(IN_3, speedCar);
      analogWrite(IN_4, 0);
      //analogWrite(ENB, speedCar);
  }

void goRight(){ 

      analogWrite(IN_1, speedCar);
      analogWrite(IN_2, 0);
      //analogWrite(ENA, speedCar);

      analogWrite(IN_3, 0);
      analogWrite(IN_4, speedCar);
      //analogWrite(ENB, speedCar);
  }

void goLeft(){

      analogWrite(IN_1, 0);
      analogWrite(IN_2, speedCar);
      //analogWrite(ENA, speedCar);

      analogWrite(IN_3, speedCar);
      analogWrite(IN_4, 0);
      //analogWrite(ENB, speedCar);
  }

void goAheadRight(){
      
      analogWrite(IN_1, 0); //RIGHT
      analogWrite(IN_2, speedCar/3);
      
      analogWrite(IN_3, 0); //LEFT
      analogWrite(IN_4, speedCar);
   
   }

void goAheadLeft(){
      
      analogWrite(IN_1, 0);
      analogWrite(IN_2, speedCar);
      //analogWrite(ENA, speedCar);

      analogWrite(IN_3, 0);
      analogWrite(IN_4, speedCar/3);
      //analogWrite(ENB, speedCar/speed_Coeff);
  }

void goBackRight(){ 

      analogWrite(IN_1, speedCar/3);
      analogWrite(IN_2, 0);
      //analogWrite(ENA, speedCar/speed_Coeff);

      analogWrite(IN_3, speedCar);
      analogWrite(IN_4, 0);
      //analogWrite(ENB, speedCar);
  }

void goBackLeft(){ 

      analogWrite(IN_1, speedCar);
      analogWrite(IN_2, 0);
      //analogWrite(ENA, speedCar);

      analogWrite(IN_3, speedCar/3);
      analogWrite(IN_4, 0);
      //analogWrite(ENB, speedCar/speed_Coeff);
  }

void stopRobot(){  

      analogWrite(IN_1, 0);
      analogWrite(IN_2, 0);
      //analogWrite(ENA, speedCar);

      analogWrite(IN_3, 0);
      analogWrite(IN_4, 0);
      //analogWrite(ENB, speedCar);
 }

void loop() {
    server.handleClient();
    
      command = server.arg("State");
      if (command == "F") goAhead();
      else if (command == "B") goBack();
      else if (command == "L") goLeft();
      else if (command == "R") goRight();
      else if (command == "I") goAheadRight();
      else if (command == "G") goAheadLeft();
      else if (command == "J") goBackRight();
      else if (command == "H") goBackLeft();
      else if (command == "0") speedCar = 100;
      else if (command == "1") speedCar = 200;
      else if (command == "2") speedCar = 300;
      else if (command == "3") speedCar = 400;
      else if (command == "4") speedCar = 500;
      else if (command == "5") speedCar = 600;
      else if (command == "6") speedCar = 700;
      else if (command == "7") speedCar = 800;
      else if (command == "8") speedCar = 900;
      else if (command == "9") speedCar = 1000;
      else if (command == "10") speedCar = 1023;
      else if (command == "S") stopRobot();

      Serial.println(speedCar);
}

void HTTP_handleRoot(void) {

if( server.hasArg("State") ){
       Serial.println(server.arg("State"));
  }
  server.send ( 200, "text/html", "" );
  delay(1);
}

#include <ESP8266WiFi.h>
#include <WebSocketsClient.h>


// motor 1 settings
#define IN1 D6 // GPIO12
#define IN2 D7 // GPIO13
#define ENA D8 // GPIO15 

// motor 2 settings
#define IN3 D2 //GPIO4
#define IN4 D3 //GPIO0
#define ENB D4 //GPIO2 

#define CW   1 // do not change
#define CCW  2 // do not change
//int motorDirection = CW;

#define motor1 1 // do not change
#define motor2 2 // do not change

void rotate(int motor, int speed, int dir);

void rotate(int motor, int speed, int dir){
  if(motor == motor1){
    if(dir == CW){
       //digitalWrite(ENA, LOW);
       digitalWrite(IN1, HIGH);
       digitalWrite(IN2, LOW);
       Serial.printf("CW test\nCW test\n");
       analogWrite(ENA, speed);
       
      }
      else if (dir == CCW){
       //Counter clock wise 
       //digitalWrite(ENA, LOW);
       digitalWrite(IN1, LOW);
       digitalWrite(IN2, HIGH);
       Serial.printf("CCW test\nCCW test\n");
       analogWrite(ENA, speed);
        }
    }
  else if (motor = motor2){
       if(dir == CW){
       //digitalWrite(ENA, LOW);
       digitalWrite(IN3, HIGH);
       digitalWrite(IN4, LOW);
       analogWrite(ENB, speed);
      }
      else if (dir == CCW){
       //digitalWrite(ENA, LOW);
       digitalWrite(IN3, LOW);
       digitalWrite(IN4, HIGH);
       analogWrite(ENB, speed);
        }
  }
}

WebSocketsClient wsc;               //new websocket of class WebSocketClient called wsc

const char *ssid = "Dark";     // put Your WiFi & password
const char *pass = "123456789";

#define SERVER  "192.168.137.1"      //Device IP
#define PORT    8000
#define URL     "/"

void websocketEvent(WStype_t type, uint8_t *data, size_t length){
  switch(type){
    case(WStype_CONNECTED):
      Serial.printf("connected to server\n");         // print on Arduino Serial monitor
      wsc.sendTXT("Hello Server, I'm nodeMCU");       // send"Hello Server.." to Server (as MSG)
      break;
    case WStype_DISCONNECTED:
      Serial.printf("Disconnected!\n");
      break;
    case(WStype_TEXT):                                //Recived a message from server (ws.send())
      Serial.printf("Messege from server: %s\n",data);
      
      char stop,forward,back,right,left;
      stop = data[0];
      forward = data[1];
      back = data[2];
      right = data[3];
      left = data[4];
      
      switch(stop){
        case '1':
          Serial.println("case 1, stop car");
          digitalWrite(IN1, LOW);
          digitalWrite(IN2, LOW);
          digitalWrite(IN3, LOW);
          digitalWrite(IN4, LOW);  
          analogWrite(ENA, 0);
          analogWrite(ENB, 0);
          //delay(2000);
         //  To test at which PWM value motor starts rotating
         //  digitalWrite(IN1, LOW);
         //  digitalWrite(IN2, HIGH);  
         //  for (int i = 0; i < 1024; i++) { 
         //  analogWrite(ENA, i);  
          // delay(20);
          // Serial.printf("PWM = %d\n",i); 
          // } 
          break;
        case '0':
            Serial.println("case 2, move car");
          switch(forward){
            case '0':
              Serial.println("Car stopped");
              rotate(motor1, 0, CW);
              //delay(2000);
              break;
            case '1':
              Serial.println("Speed 1");
              rotate(motor1, 51, CW);
              //delay(2000);
              break;
            case '2':
              Serial.println("speed 2");
              rotate(motor1, 102, CW);
              //delay(2000);
              break;
            case '3':
              Serial.println("speed 3");
              rotate(motor1, 153, CW);
              //delay(2000);
              break;
            case '4':
              Serial.println("speed 4");
              rotate(motor1, 204, CW);
              //delay(2000);
              break;
            case '5':
              Serial.println("speed 5");
              rotate(motor1, 255, CW);
              //delay(2000);
              break;
            default: Serial.println("error in forward");
            }
            switch(back){
            /*case '0':
            Serial.println("car stopped");
            rotate(motor1, 0, CCW);
            //delay(2000);
              break;*/
            case '1':
            Serial.println("speed -1");
            rotate(motor1, 51, CCW);
            //delay(2000);
              break;
            case '2':
            Serial.println("speed -2");
            rotate(motor1, 102, CCW);
            //delay(2000);
              break;
            case '3':
            Serial.println("speed -3");
            rotate(motor1, 153, CCW);
            //delay(2000);
              break;
            case '4':
            Serial.println("speed -4");
            rotate(motor1, 204, CCW);
            //delay(2000);
              break;
            case '5':
            Serial.println("speed -5");
            rotate(motor1, 255, CCW);
            //delay(2000);
              break;
            default: Serial.println("error in back");
            //delay(2000);
            }
            switch(right){
            case '0':
              Serial.println("forward");
              rotate(motor2, 0, CW);
              //delay(2000);
              break;
            case '1':
              Serial.println("right 1");
              rotate(motor2, 51, CW);
              //delay(2000);
              break;
            case '2':
              Serial.println("right 2");
              rotate(motor2, 102, CW);
              //delay(2000);
              break;
            case '3':
              Serial.println("right 3");
              rotate(motor2, 153, CW);
              //delay(2000);
              break;
            case '4':
              Serial.println("right 4");
              rotate(motor2, 204, CW);
              //delay(2000);
              break;
            case '5':
              Serial.println("right 5");
              rotate(motor2, 255, CW);
              //delay(2000);
              break;
            default: Serial.println("error in right");
            }
            switch(left){
            /*case '0':
              Serial.println("forward");
              rotate(motor2, 0, CCW);
              //delay(2000);
              break;*/
            case '1':
              Serial.println("Left 1");
              rotate(motor2, 51, CCW);
              //delay(2000);
              break;
            case '2':
              Serial.println("Left 2");
              rotate(motor2, 102, CCW);
              //delay(2000);
              break;
            case '3':
              Serial.println("Left 3");
              rotate(motor2, 153, CCW);
              //delay(2000);
              break;
            case '4':
              Serial.println("Left 4");
              rotate(motor2, 204, CCW);
              //delay(2000);
              break;
            case '5':
              Serial.println("Left 5");
              rotate(motor2, 255, CCW);
              //delay(2000);
              break;
            default: Serial.println("error in left");
            }

           
           break;
           
        default: Serial.println("error in stop");
        }
      
      break;
  }
}

void setup(){
  //motor init
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  Serial.begin(115200);                   // open Serial with buadrate 115200

  WiFi.begin(ssid, pass);                 // open wifi 

  while(WiFi.status() != WL_CONNECTED){   
    Serial.println(".");
    delay(500);
  }                                       //print dot while wifi not connected and check every .5 sec

  Serial.println(WiFi.SSID());            // when wifi connected print Wifi_name and IP
  Serial.println(WiFi.localIP());

  wsc.begin(SERVER, PORT, URL);           // start connection with Server
  wsc.onEvent(websocketEvent);            // In case of any event go to websocketEvent func
  // try ever 1000 again if connection has failed
  wsc.setReconnectInterval(1000);
}

void loop(){
  wsc.loop();
}

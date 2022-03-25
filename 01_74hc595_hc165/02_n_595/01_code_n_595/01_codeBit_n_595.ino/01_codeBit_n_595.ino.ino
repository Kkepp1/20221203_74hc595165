//#include "drawer.h"

#define CLK             9
#define LATCH           8
#define OUT             7
//#define CLK             8
//#define LATCH           7
//#define OUT             9
#define maxDrawer       2
#define Bit(i)          (1<<i)
#define lock_bit            1<<0
#define light_bit           1<<4
#define ir_bit              1<<7
//ctr_function
int drawerId;
String cmd;
String State;

typedef struct {
  u8 ctrl;

  u8 lightStatus;
  u8 irStatus;
  u8 lockStatus;
  } kkk;
  
kkk DrawerCtrl[maxDrawer]={0};
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(CLK,OUTPUT);
  pinMode(LATCH,OUTPUT);
  pinMode(OUT,OUTPUT);
  Serial.print("start to control...");
 

}
//--------------------------------------- nhận và xử lý dữ liệu---------------------------------------------------------
void split_String(String State, String &cmd,int &drawerId){
    String temp_drawerId="";
    String temp_cmd="";
    int dem=0;
    for(int i=0;i<State.length();i++){
    
      if(State[i]==','){
        dem++;
        }else{
          if(dem==0){
            temp_cmd+=State[i];
            }
            else if(dem==1){
              temp_drawerId+=State[i];
              }
            else if(dem==2){
              
              break;
              }
          }
      }
      cmd=temp_cmd;
      drawerId=temp_drawerId.toInt()-1;
      dem=0;
//      Serial.println(cmd);
//      Serial.println(drawerId);
      //delay(2000);
    }
//----------------------------------------------write 595------------------------------------------------
void Write_1_595(u8 byte){
  for(int i=7;i>=0;i--){
    if(byte&Bit(i)){
      digitalWrite(OUT,HIGH);
      }else {
       digitalWrite(OUT,LOW); 
        }
//    digitalWrite(OUT,byte&Bit(i));
    delay(1);
    digitalWrite(CLK,HIGH);
    delay(1);
    digitalWrite(CLK,LOW);
    delay(1);
    }
  digitalWrite(OUT,LOW);
 // delay(1);
  }
void Write_n_595(){
//  u8 ctrl;
  for(int i=maxDrawer-1;i>=0;i--){
    Write_1_595(DrawerCtrl[i].ctrl);

    }
    delay(10);
    digitalWrite(LATCH,LOW);
    delay(10);
    digitalWrite(LATCH,HIGH);
    delay(10);

  }

  
// -------------------------hàm điều khiển---------------------------------------------------------
void lock_ctrl(String cmd, int drawerId){
  if(cmd=="OpenDoor"){
   DrawerCtrl[drawerId].ctrl|=lock_bit;
   Serial.println("DoorOpened");
    }else if(cmd=="CloseDoor"){
      DrawerCtrl[drawerId].ctrl&=~(lock_bit);
      Serial.println("DoorClosed");
      }
     Write_n_595();
  }
void light_ctrl(String cmd, int drawerId){
  if(cmd=="LightOn"){
   DrawerCtrl[drawerId].ctrl|=light_bit;
    Serial.println("light on");
    }else if(cmd=="LightOff"){
   DrawerCtrl[drawerId].ctrl&=~(light_bit);
      Serial.println("light off");
      }
     Write_n_595();
  } 
void ir_ctrl(String cmd, int drawerId){
  if(cmd=="IrOn"){
    DrawerCtrl[drawerId].ctrl|=ir_bit;
    Serial.println("ir on");
    }else if(cmd=="IrOff"){
     DrawerCtrl[drawerId].ctrl&=~(ir_bit);
         Serial.println("ir off");
      }
    Write_n_595();
  } 
 //----------------------------------------------main-------------------------------------------  
void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
      State= Serial.readString();
      split_String(State,cmd,drawerId);
    }
    if(cmd=="OpenDoor"|| cmd=="CloseDoor"){lock_ctrl(cmd,drawerId);}
   if(cmd=="LightOn"|| cmd=="LightOff"){light_ctrl(cmd,drawerId);}
    if(cmd=="IrOn"|| cmd=="IrOff"){ir_ctrl(cmd,drawerId);}

//      Serial.println(DrawerCtrl[1].ctrl);
//      delay(2000);
  
}

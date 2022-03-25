#define CLK     9
#define LATCH   8
#define IN      7

#define maxDrawer  2

#define lock_sts_bit     (1<<0)
#define light_sts_bit     (1<<4)
#define ir_sts_bit        (1<<7)
String state="";
String cmd="";
int drawerId=0;
typedef struct{
  u8 ctrl;
  u8 look; 
  }kkk;
kkk DrawerCtrl[maxDrawer]={0,0,0,0};

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(CLK,OUTPUT);
pinMode(LATCH,OUTPUT);
pinMode(IN,INPUT);
Serial.print("Smart locker pha-ke v1");
Serial.println("");
}
//-----------------------------nhận và xử lý dữ liệu-----------------------------------------------------------------------
void split_string(String state, String &cmd,int &drawerId){
  int dem=0;
  String temp_cmd="";
  String temp_drawerId="";
  for(int i=0; i<state.length();i++){
    //while(state[i]!='\0'){
      if(state[i]==','){
        dem++;
        }else{
          if(dem==0){
          temp_cmd+=state[i];
         }else if(dem==1){
          temp_drawerId+=state[i]; 
         }else if(dem==2){
          break;
          }
          
          } 
       }
   // }
    cmd=temp_cmd;
    drawerId=temp_drawerId.toInt();
    dem=0;
  
  }
//-----------------------------read 165------------------------------------------------------------------------------------
void read_1_165(u8 &value){
  u8 temp=0;
  value=0;
  for(int i=7;i>=0;i--){
    digitalWrite(CLK,LOW);
    temp=digitalRead(IN);
    value|=temp<<i; 
    delay(10);
    digitalWrite(CLK,HIGH);
    delay(10);  
    }
    //Serial.println(value);
}
void read_n_165(){
   digitalWrite(LATCH,HIGH);
  delay(10);
  digitalWrite(LATCH,LOW);
  delay(10);
  digitalWrite(LATCH,HIGH);
  delay(10);
  for(int i=maxDrawer-1;i>=0;i--){
    read_1_165(DrawerCtrl[i].look);
    }
} 
//-------------------------------------------- hàm đọc trạng thái bit----------------------------------
bool lock_look(int drawerId){
  read_n_165();
  return DrawerCtrl[drawerId].look & lock_sts_bit? true:false;
  }
//--------------------------------------------main--------------------------------------------------- 
void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
      state=Serial.readString();
  read_n_165();
  Serial.println(DrawerCtrl[0].look);
  Serial.println(DrawerCtrl[1].look);
  split_string(state,cmd,drawerId);
  Serial.println(cmd);
  Serial.println(drawerId);
  if(lock_look(drawerId)) Serial.println("door open");
    else Serial.println("door closeee");
  delay(2000);
    }

}

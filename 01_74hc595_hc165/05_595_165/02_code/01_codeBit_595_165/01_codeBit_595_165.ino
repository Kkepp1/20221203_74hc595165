#define SAME_LATCH   (0)
#define DIFF_LATCH    (1)

#define CLK             3

#if SAME_LATCH
#define LATCH595        5
#define LATCH165        7
#endif
#if DIFF_LATCH
#define LATCH595        5
#define LATCH165        7
#endif

#define OUT             8
#define IN              10

#define maxDrawer       2

#define Bit(i)          (1<<i)
#define lock_bit        (1<<1)
#define light_bit       (1<<3)
#define ir_bit          (1<<5)

#define lock_sts_bit        (1<<1)
#define light_sts_bit       (1<<3)
#define ir_sts_bit          (1<<5)
String state;
String cmd;
int drawerId;

int a=0;
typedef struct{
  u8 ctrl;
  u8 look;
  
  } msg;
msg DrawerCtrl[maxDrawer]={0};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(CLK,OUTPUT);
  pinMode(LATCH595,OUTPUT);
  pinMode(LATCH165,OUTPUT);
  pinMode(OUT,OUTPUT);
  pinMode(IN,INPUT);
  digitalWrite(LATCH595,HIGH);
  digitalWrite(LATCH165,HIGH);
  Serial.print("Smartlocker phake v2...............................................connected");
  Serial.println("");
  

}
//----------------------------------xử lý du liêu------------------------------------------
void split_string(String state,String &temp,int &drawerId)
{
  int dem=0;
  String temp_cmd="";
  String temp_drawerId="";

  for(int i=0;i<state.length();i++)
  {
    if(state[i]==',')
    {
      dem++;
    }else{
        if(dem==0)
          {
            temp_cmd+=state[i];
          }else if(dem==1)
          {
            temp_drawerId+=state[i];
          }else if(dem==2)
          {
            break;
          }
        }
   }
    cmd=temp_cmd;
    drawerId=temp_drawerId.toInt()-1;// 1,2 on terminal
    dem=0;
}
//----------------------------------write 595----------------------------------------------
void write_1_595(u8 byte)
{
  for(int i=7;i>=0;i--){
    digitalWrite(OUT,byte&Bit(i));
    digitalWrite(CLK,LOW);
    delay(1);
    digitalWrite(CLK,HIGH);
    delay(1);
    }
 digitalWrite(OUT,LOW); 
 delay(10);
}
void write_n_595()
{
  for(int j=1;j<=3;j++)
  {
    for(int i=maxDrawer-1;i>=0;i--)
    {
      write_1_595(0x00);
      write_1_595(DrawerCtrl[i].ctrl);
    }
   // delay(100);
  }

    digitalWrite(LATCH595,LOW);
    delay(10);
    digitalWrite(LATCH595,HIGH);
    delay(10);
 }
//----------------------------------read 165------------------------------------------------
void read_1_165(u8 &value)
{
  value=0;
  u8 temp=0;
  for(int i=7;i>=0;i--)
  {
    digitalWrite(CLK,LOW);
    temp=digitalRead(IN);
    value|=temp<<i;
    delay(1);
    digitalWrite(CLK,HIGH);
    delay(1);
  }
  delay(10);
}
void read_n_165()
{
  u8 c;
  digitalWrite(LATCH165,HIGH);
  delay(10);
  digitalWrite(LATCH165,LOW);
  delay(10);
  digitalWrite(LATCH165,HIGH);
   // for(int j=1;j<=2;j++){
      for(int i=maxDrawer-1;i>=0;i--)
      {
        read_1_165(DrawerCtrl[i].look);
        read_1_165(c);
        Serial.println(DrawerCtrl[i].look);
      }
       //delay(100);
   // }
// write_n_595();
    
}
//----------------------------------hàm điều khiển-----------------------------------------
void lock_ctrl(String cmd,int drawerId)
{
    if(cmd=="OpenDoor")
    {
      DrawerCtrl[drawerId].ctrl|=lock_bit;
    }else if(cmd=="CloseDoor")
    {
      DrawerCtrl[drawerId].ctrl&=~(lock_bit);
    }
    write_n_595();
   if(detect_lock(drawerId))
   {
      Serial.println("Door opened");
   }else Serial.println("Door closed" );
}
void light_ctrl(String cmd,int drawerId)
{
    if(cmd=="LightOn")
    {
        DrawerCtrl[drawerId].ctrl|=light_bit;
    }else if(cmd=="LightOff")
    {
        DrawerCtrl[drawerId].ctrl&=~(light_bit);
    }
        write_n_595();
}
//----------------------------------hàm xét trạng thái----------------------------------------
bool detect_lock(int drawerId)
{
  read_n_165();
  return DrawerCtrl[drawerId].look & lock_sts_bit? true:false; 
}
bool detect_light(int drawerId)
{
  read_n_165();
  return DrawerCtrl[drawerId].look & light_sts_bit? true:false; 
}
//-----------------------------------main-----------------------------------------------------
void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
    state=Serial.readString();
    split_string(state,cmd,drawerId);
    if(cmd=="OpenDoor"|| cmd=="CloseDoor"){lock_ctrl(cmd,drawerId);}
    if(cmd=="LightOn"|| cmd=="LightOff"){light_ctrl(cmd,drawerId);}
    
    
    //Serial.println(drawerId);
    }
}

#define LATCH   7
#define OUT     9
#define CLK     8

u8 out=0;
int dem=0;
#define Bit(i)  (1<<i)

#define bit0    1<<0
#define bit3    1<<3
#define bit6    1<<6
#define bit7    1<<7
String state;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LATCH,OUTPUT);
  pinMode(CLK,OUTPUT);
  pinMode(OUT,OUTPUT);
  Serial.print("start");

}
void Bit0(u8 &out,String state){
 // String state = Serial.readString();
  if(state =="ON0"){
    out|=bit0;
    Serial.println("on0");
    }else if(state =="OFF0"){
      out&=~(bit0);
      Serial.println("off0");
      }
  }
void Bit3(u8 &out,String state){
 // String state = Serial.readString();
  if(state =="ON3"){
    out|=bit3;
    Serial.println("on3");
    }else if(state =="OFF3"){
      out&=~(bit3);
      Serial.println("off3");
      }
  }
void Bit6(u8 &out,String state){
//  String state = Serial.readString();
  if(state =="ON6"){
    out|=bit6;
    Serial.println("on6");
    }else if(state =="OFF6"){
      out&=~(bit6);
      Serial.println("off6");
      }
  }
 void Bit7(u8 &out,String state){
 // String state = Serial.readString();
  if(state =="ON7"){
    out|=bit7;
    Serial.println("on7");
    }else if(state =="OFF7"){
      out&=~(bit7);
      Serial.println("off7");
      }
  } 
void control_function(u8 &out,String state){

  for(int i=7;i>=0;i--){
    digitalWrite(OUT,out&Bit(i));
    delay(1);
    digitalWrite(CLK,HIGH);
    delay(1);
    digitalWrite(CLK,LOW);
    delay(1);
    }
  digitalWrite(LATCH,LOW);
  delay(10);
  digitalWrite(LATCH,HIGH);
  delay(10);
  
  }
void loop() {
  // put your main code here, to run repeatedly:
  state = Serial.readString();
  Bit0(out,state);
  Bit3(out,state);
  Bit6(out,state);
  Bit7(out,state);
  control_function(out,state);
  //delay(100);
  
}

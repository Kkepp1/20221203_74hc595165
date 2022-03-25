#define CLK         9
#define LATCH       7
#define DATA        8  

byte daTa[8]={1,0,0,0,1,1,1,1};
void setup() {
  // put your setup code here, to run once:
  pinMode(CLK,OUTPUT);
  pinMode(LATCH,OUTPUT);
  pinMode(DATA,OUTPUT);
  

}
void write_Data(){
  for(int i=7;i>=0;i--){
    digitalWrite(DATA,daTa[i]);
    digitalWrite(CLK,HIGH);
    delay(1);
    digitalWrite(CLK,LOW);
    delay(1);
    }
   digitalWrite(LATCH,LOW);
   delay(1);
   digitalWrite(LATCH,HIGH);
   delay(1); 
  }
void loop() {
  // put your main code here, to run repeatedly:
  int i=0;
  if(i==0){
    write_Data();
    i++;
   }

}

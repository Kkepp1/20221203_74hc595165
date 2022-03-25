#define LATCH     7
#define CLOCK     8
#define DATA      9
byte out1[8]={1,1,0,1,1,1,1,0};
byte out2[8]={0,1,0,0,1,0,0,0};
int a=0;
void setup() {
  // put your setup code here, to run once:
  pinMode(LATCH,OUTPUT);
  pinMode(DATA,OUTPUT);
  pinMode(CLOCK,OUTPUT);

}
void send_595(){
    for(int i=7;i>=0;i--){
    digitalWrite(DATA,out2[i]);
    delay(1);
    digitalWrite(CLOCK,HIGH);
    delay(1);
    digitalWrite(CLOCK,LOW);
    delay(1);
    }
    for(int i=7;i>=0;i--){
    digitalWrite(DATA,out1[i]);
    delay(1);
    digitalWrite(CLOCK,HIGH);
    delay(1);
    digitalWrite(CLOCK,LOW);
    delay(1);
    }
    digitalWrite(LATCH,LOW);
    delay(1);
    digitalWrite(LATCH,HIGH);
    delay(1);
  }
void loop() {
  // put your main code here, to run repeatedly:
 
  if(a==0){
    send_595();
    a++;
    }


}

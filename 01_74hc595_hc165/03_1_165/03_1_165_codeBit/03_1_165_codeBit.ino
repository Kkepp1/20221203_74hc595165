#define CLK     8
#define LATCH   7
#define IN      9
int a=0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(CLK,OUTPUT);
  pinMode(LATCH,OUTPUT);
  pinMode(IN,INPUT);

}
void read_165(){
  u8 value=0;
  u8  temp=0;
  digitalWrite(LATCH,HIGH);
  delay(10);
  digitalWrite(LATCH,LOW);
  delay(10);
  digitalWrite(LATCH,HIGH);
  delay(10);
  for(int i=7;i>=0;i--){
    digitalWrite(CLK,LOW);
    temp=digitalRead(IN);
    value |=temp<<i;
    delay(10);
    digitalWrite(CLK,HIGH);
    delay(10);
    
    }
  Serial.print(value);
  int bit1= 1&(value<<0);
  if(bit1) Serial.println("bit 1 on");
   else Serial.println("bit 1 off");
  }
void loop() {
  // put your main code here, to run repeatedly:
if(a==0){
  read_165();
  a++;
  }
}

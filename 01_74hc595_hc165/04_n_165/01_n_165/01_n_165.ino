#define CLK   9
#define LATCH 8
#define IN    7
byte in1[8],in2[8];
int a=0;
void setup() {
  // put your setup code here, to run once:
  pinMode(CLK,OUTPUT);
  pinMode(LATCH,OUTPUT);
  pinMode(IN,INPUT);
  Serial.begin(9600);
}
void read_1_165(){
  digitalWrite(LATCH,LOW);
  delay(10);
  digitalWrite(LATCH,HIGH);
  delay(10);
  for(int i=0;i<8;i++){
    digitalWrite(CLK,LOW);
   
    in1[i]=digitalRead(IN);
    delay(10);
    digitalWrite(CLK,HIGH);
    delay(10);
    }
   for(int i=0;i<8;i++){
    digitalWrite(CLK,LOW);
   
    in2[i]=digitalRead(IN);
    delay(10);
    digitalWrite(CLK,HIGH);
    delay(10);
    }
for(int i=7;i>=0;i--){
  Serial.print(in2[i]);
  Serial.print(" ");
  }
  Serial.print("|||||"); 
for(int i=7;i>=0;i--){
  Serial.print(in1[i]);
  Serial.print(" ");
  }

  
  }
void loop() {
  // put your main code here, to run repeatedly:
  if(a==0){
    read_1_165();
    a++;
    }

}

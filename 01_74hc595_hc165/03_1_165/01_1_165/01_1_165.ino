#define CLK     8
#define LATCH   7
#define EN      5
#define IN      9

#define cycle (1)
#define no_cycle  (0)
 int a=0;
 u8 b;
byte in[8];
void setup() {
  // put your setup code here, to run once:
  pinMode(CLK,OUTPUT);
  pinMode(LATCH,OUTPUT);
  pinMode(EN,OUTPUT);
  pinMode(IN,INPUT);

  Serial.begin(9600);
  digitalWrite(EN,LOW);
  Serial.print("Start");

}
void read_165(){
  digitalWrite(LATCH,HIGH);
  delay(10);
  digitalWrite(LATCH,LOW);
  delay(10);
  digitalWrite(LATCH,HIGH);
  delay(10);
  
  delay(50);
  for(int i=0;i<8;i++){
     digitalWrite(CLK,LOW);
    in[i]=digitalRead(IN);
    delay(10);
    digitalWrite(CLK,HIGH);
    delay(10);
    }

  for(int i=7;i>=0;i--){
    
    Serial.print(" ");
    Serial.print(in[i]);
    delay(100);
    }
    Serial.println("");
    delay(2000);
  
  }
void loop() {
  // put your main code here, to run repeatedly:
 #if no_cycle
  if(a==0){
    read_165();
    a++;
    }
  #endif
  #if cycle
    read_165();
  #endif
}

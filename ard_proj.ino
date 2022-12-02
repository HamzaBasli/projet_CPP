#define LM35 A1

char data;
float lmtmp=0;
float c;
int a = 1;
void setup() {
  pinMode(LM35, INPUT);
  Serial.begin(9600);

 // put your setup code here, to run once:

}

void loop() {
 
  

 lmtmp=analogRead(LM35);
if(a==1){

  c = lmtmp * 500 / 1024 ;
if(c<= 80) 
{Serial.println("1");
}
else{ 
Serial.write("2");}}
a++;





delay(5000);
}

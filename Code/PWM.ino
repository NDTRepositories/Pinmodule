int i,data,pwm,bat,b,tmp;
float vo,cutoff,on;
void setup() {
pinMode(2,OUTPUT);
pinMode(3,OUTPUT);
pinMode(4,OUTPUT);
TCCR1B = TCCR1B & B11111000 | B00000001; // Set PWM frequency for D9 & D10:
Serial.begin(9600);
}
void loop(){
for(int j=0;j<3;j++){
vo=analogRead(A0);
vo=vo*.1;
bat=bat+vo;
for(int i=0;i<7;i++){
if(i>7)i=0;
led(i,1);
if(i>0)led(i-1,0);
delay(100);
}
}
bat=bat/3;
if(bat<16){
cutoff=14.4;
on=13.8;
b=12;
}else {
cutoff=28.8;
on=27.6;
b=24;
}
Serial.println(bat);
delay(2000);
while(1){
led(0,0);
led(1,0);
led(2,0);
led(3,0);
led(4,0);
led(5,0);
i++;
if(i>7)i=0;
led(i,1);
if(i>0)led(i-1,0);
vo=analogRead(A0);
vo=vo*.1;
if(vo>cutoff)pwm--;
if(vo<on)pwm++;
if(pwm<0)pwm=0;
if(pwm>100)pwm=100;
if(b==12)tmp=1;
if(b==24)tmp=2;
if(vo>b)led(0,1);
if(vo>b+(.4*tmp))led(1,1);
if(vo>b+(.8*tmp))led(2,1);
if(vo>b+(1.2*tmp))led(3,1);
if(vo>b+(1.6*tmp))led(4,1);
if(vo>b+(2.2*tmp))led(5,1);
Serial.print(b);
Serial.print("V Battery ");
Serial.print("output volt ");
Serial.print(vo);
Serial.println("V");
analogWrite(9,pwm);
delay(500);
}
}
void led(uint8_t pin,bool val){
bitWrite(data,pin,val);
digitalWrite(2,LOW); //latch pin low
shiftOut(3,4,MSBFIRST,data); //shiftOut(datapin,clockpin,LSBFIRST/MSBFIRST,data);
digitalWrite(2,HIGH);
}
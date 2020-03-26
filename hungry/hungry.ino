#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include<Servo.h>
      int led = 7;
      Servo servo5;
        float getDistance(int trig,int echo){
            pinMode(trig,OUTPUT);
            digitalWrite(trig,LOW);
            delayMicroseconds(2);
            digitalWrite(trig,HIGH);
            delayMicroseconds(10);
            digitalWrite(trig,LOW);
            pinMode(echo, INPUT);
            return pulseIn(echo,HIGH,30000)/58.0;
        }

void setup() {
  Serial.begin(9600);
  servo5.attach(5);
  servo5.write(180);
  pinMode(led,OUTPUT);
  float a[3];
}
 
void loop() {
   while (1) {
//    Serial.println((getDistance(4,3)));
//    delay(100);
    int i=0;
    float a[3];
//    ================================================================
//@brief lay gia tri 3 lan lien tiep cach nhau 20ms
//====================================================================
    while(i<3){
      a[i]= getDistance(4,3);
      delay(5);
      i++;
    }
    
    for(i=0;i<3;i++){
      Serial.println((a[i]));
      
    }
    int k;
    for(i=0;i<2;i++){
      for(int j=i+1;j<3;j++){
        if((a[j]/a[i])>1.5||(a[j]/a[i]<0.7)){
          k=0;
          break;
        }
        else
        {
            k=1;
            break;
        }
      }
    }
     
    for(int t =0;t<2;t++){
      if(a[t]==0.00)
      k=2;
      break;
    }
   Serial.println(k);
    if(k== 0||k == 2){
      break;
    }
    if(k==1){
          if(((a[0]+a[1]+a[2])/3) < 4 && ((a[0]+a[1])/2) < 4 && ((a[1]+a[2])/2)<4)
            {
              digitalWrite(led,HIGH);
              delay(2000);
              servo5.write(45);
              delay(200);
              servo5.write(180);
              digitalWrite(led,LOW);
              delay(100); 
            }
              else{
               digitalWrite(led,LOW);
               break;
              }
          
    }
   }    
}

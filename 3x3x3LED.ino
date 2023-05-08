int pin1 = 12;  
int pin2 = 11;  
int pin3 = 10;  
int pin4 = 9;  
int pin5 = 8;   
int pin6 = 7;   
int pin7 = 6;   
int pin8 = 5;   
int pin9 = 4;  

int pos1 = 3;   
int pos2 = 2;   
int pos3 = 0;   
int r = 0;

void setup() {                
  
  pinMode(pin1, OUTPUT);     
  pinMode(pin2, OUTPUT);     
  pinMode(pin3, OUTPUT);     
  pinMode(pin4, OUTPUT);     
  pinMode(pin5, OUTPUT);     
  pinMode(pin6, OUTPUT);     
  pinMode(pin7, OUTPUT);     
  pinMode(pin8, OUTPUT);     
  pinMode(pin9, OUTPUT);  
  
  pinMode(pos1, OUTPUT);     
  pinMode(pos2, OUTPUT);     
  pinMode(pos3, OUTPUT);     
}


void loop() {
  
 r = random(1,6); 
if (r == 1){

  for (int i=0 ; i<=3 ;i++){
    digitalWrite(pos1, 0);
    digitalWrite(pos2, 0);
    digitalWrite(pos3, 0);
  
    digitalWrite(pin1, 1);
    digitalWrite(pin2, 1);
    digitalWrite(pin3, 1);
    digitalWrite(pin4, 0);
    digitalWrite(pin5, 0);
    digitalWrite(pin6, 0);
    digitalWrite(pin7, 0);
    digitalWrite(pin8, 0);
    digitalWrite(pin9, 0);
    delay(200);

     digitalWrite(pos1, 0);
    digitalWrite(pos2, 0);
    digitalWrite(pos3, 0);
  
    digitalWrite(pin1, 0);
    digitalWrite(pin2, 0);
    digitalWrite(pin3, 0);
    digitalWrite(pin4, 1);
    digitalWrite(pin5, 1);
    digitalWrite(pin6, 1);
    digitalWrite(pin7, 0);
    digitalWrite(pin8, 0);
    digitalWrite(pin9, 0);
    delay(200);

     digitalWrite(pos1, 0);
    digitalWrite(pos2, 0);
    digitalWrite(pos3, 0);
  
    digitalWrite(pin1, 0);
    digitalWrite(pin2, 0);
    digitalWrite(pin3, 0);
    digitalWrite(pin4, 0);
    digitalWrite(pin5, 0);
    digitalWrite(pin6, 0);
    digitalWrite(pin7, 1);
    digitalWrite(pin8, 1);
    digitalWrite(pin9, 1);
    delay(200);

     digitalWrite(pos1, 1);
    digitalWrite(pos2, 1);
    digitalWrite(pos3, 0);
  
    digitalWrite(pin1, 1);
    digitalWrite(pin2, 1);
    digitalWrite(pin3, 1);
    digitalWrite(pin4, 1);
    digitalWrite(pin5, 1);
    digitalWrite(pin6, 1);
    digitalWrite(pin7, 1);
    digitalWrite(pin8, 1);
    digitalWrite(pin9, 1);
    delay(200);

    digitalWrite(pos1, 1);
    digitalWrite(pos2, 0);
    digitalWrite(pos3, 1);
  
    digitalWrite(pin1, 1);
    digitalWrite(pin2, 1);
    digitalWrite(pin3, 1);
    digitalWrite(pin4, 1);
    digitalWrite(pin5, 1);
    digitalWrite(pin6, 1);
    digitalWrite(pin7, 1);
    digitalWrite(pin8, 1);
    digitalWrite(pin9, 1);
    delay(200);

    digitalWrite(pos1, 0);
    digitalWrite(pos2, 1);
    digitalWrite(pos3, 1);
  
    digitalWrite(pin1, 1);
    digitalWrite(pin2, 1);
    digitalWrite(pin3, 1);
    digitalWrite(pin4, 1);
    digitalWrite(pin5, 1);
    digitalWrite(pin6, 1);
    digitalWrite(pin7, 1);
    digitalWrite(pin8, 1);
    digitalWrite(pin9, 1);
    delay(200);
}
}




     
      
  if (r == 2){    
      
      digitalWrite(pos1, 1);
    digitalWrite(pos2, 0);
    digitalWrite(pos3, 0);
  
    digitalWrite(pin1, 0);
    digitalWrite(pin2, 0);
    digitalWrite(pin3, 0);
    digitalWrite(pin4, 0);
    digitalWrite(pin5, 1);
    digitalWrite(pin6, 1);
    digitalWrite(pin7, 0);
    digitalWrite(pin8, 1);
    digitalWrite(pin9, 1);
    delay(500);

      digitalWrite(pos1, 1);
    digitalWrite(pos2, 0);
    digitalWrite(pos3, 0);
  
    digitalWrite(pin1, 0);
    digitalWrite(pin2, 1);
    digitalWrite(pin3, 1);
    digitalWrite(pin4, 0);
    digitalWrite(pin5, 1);
    digitalWrite(pin6, 1);
    digitalWrite(pin7, 0);
    digitalWrite(pin8, 0);
    digitalWrite(pin9, 0);
    delay(500);

     digitalWrite(pos1, 1);
    digitalWrite(pos2, 0);
    digitalWrite(pos3, 0);
  
    digitalWrite(pin1, 1);
    digitalWrite(pin2, 1);
    digitalWrite(pin3, 0);
    digitalWrite(pin4, 1);
    digitalWrite(pin5, 1);
    digitalWrite(pin6, 0);
    digitalWrite(pin7, 0);
    digitalWrite(pin8, 0);
    digitalWrite(pin9, 0);
    delay(500);

     digitalWrite(pos1, 1);
    digitalWrite(pos2, 0);
    digitalWrite(pos3, 0);
  
    digitalWrite(pin1, 0);
    digitalWrite(pin2, 0);
    digitalWrite(pin3, 0);
    digitalWrite(pin4, 1);
    digitalWrite(pin5, 1);
    digitalWrite(pin6, 0);
    digitalWrite(pin7, 1);
    digitalWrite(pin8, 1);
    digitalWrite(pin9, 0);
    delay(500);






    digitalWrite(pos1, 0);
    digitalWrite(pos2, 0);
    digitalWrite(pos3, 1);
  
    digitalWrite(pin1, 0);
    digitalWrite(pin2, 0);
    digitalWrite(pin3, 0);
    digitalWrite(pin4, 0);
    digitalWrite(pin5, 1);
    digitalWrite(pin6, 1);
    digitalWrite(pin7, 0);
    digitalWrite(pin8, 1);
    digitalWrite(pin9, 1);
    delay(500);

      digitalWrite(pos1, 0);
    digitalWrite(pos2, 0);
    digitalWrite(pos3, 1);
  
    digitalWrite(pin1, 0);
    digitalWrite(pin2, 1);
    digitalWrite(pin3, 1);
    digitalWrite(pin4, 0);
    digitalWrite(pin5, 1);
    digitalWrite(pin6, 1);
    digitalWrite(pin7, 0);
    digitalWrite(pin8, 0);
    digitalWrite(pin9, 0);
    delay(500);

     digitalWrite(pos1, 0);
    digitalWrite(pos2, 0);
    digitalWrite(pos3, 1);
  
    digitalWrite(pin1, 1);
    digitalWrite(pin2, 1);
    digitalWrite(pin3, 0);
    digitalWrite(pin4, 1);
    digitalWrite(pin5, 1);
    digitalWrite(pin6, 0);
    digitalWrite(pin7, 0);
    digitalWrite(pin8, 0);
    digitalWrite(pin9, 0);
    delay(500);

     digitalWrite(pos1, 0);
    digitalWrite(pos2, 0);
    digitalWrite(pos3, 1);
  
    digitalWrite(pin1, 0);
    digitalWrite(pin2, 0);
    digitalWrite(pin3, 0);
    digitalWrite(pin4, 1);
    digitalWrite(pin5, 1);
    digitalWrite(pin6, 0);
    digitalWrite(pin7, 1);
    digitalWrite(pin8, 1);
    digitalWrite(pin9, 0);
    delay(500);


  }

  if (r == 3){

for(int i=0 ; i<=20 ;i++){
    digitalWrite(pos1, 0);
    digitalWrite(pos2, 0);
    digitalWrite(pos3, 0);
  
    digitalWrite(pin1, 0);
    digitalWrite(pin2, 0);
    digitalWrite(pin3, 0);
    digitalWrite(pin4, 0);
    digitalWrite(pin5, 0);
    digitalWrite(pin6, 0);
    digitalWrite(pin7, 0);
    digitalWrite(pin8, 0);
    digitalWrite(pin9, 0);
    

    
  int led = random(4,13);
  

    digitalWrite(pos1, 0);
    digitalWrite(pos2, 1);
    digitalWrite(pos3, 1);
  
    digitalWrite(led, 1);
    delay(100);

    

    digitalWrite(pos1, 1);
    digitalWrite(pos2, 0);
    digitalWrite(pos3, 1);
  
    digitalWrite(led, 1);
    delay(100);

    

    digitalWrite(pos1, 1);
    digitalWrite(pos2, 1);
    digitalWrite(pos3, 0);
  
    digitalWrite(led, 1);
   delay(100);



    
}
    
  }


  if (r == 4){
    for (int i=0 ; i<=20 ; i++){

for (int y=4; y<=13 ; y++){
int bin = random(0,2);
digitalWrite(y,bin);

}

for (int x=0; x<=3 ; x++){
int bin1 = random(0,2);
digitalWrite(x,bin1);

}
  delay(200);  
    }

  }




  if (r == 5){

digitalWrite(pos1, 0);
    digitalWrite(pos2, 0);
    digitalWrite(pos3, 0);
  
    digitalWrite(pin1, 1);
    digitalWrite(pin2, 0);
    digitalWrite(pin3, 0);
    digitalWrite(pin4, 0);
    digitalWrite(pin5, 0);
    digitalWrite(pin6, 0);
    digitalWrite(pin7, 0);
    digitalWrite(pin8, 0);
    digitalWrite(pin9, 0);

delay(200);
digitalWrite(pin2, 1);
 delay(200);
digitalWrite(pin3, 1);
    delay(200);
digitalWrite(pin4, 1);
   delay(200);
digitalWrite(pin5, 1);
delay(200);
digitalWrite(pin6, 1);
delay(200);
digitalWrite(pin7, 1);
delay(200);
digitalWrite(pin8, 1);
delay(200);
digitalWrite(pin9, 1);
delay(2000);

 digitalWrite(pin1, 0);
 delay(200);
    digitalWrite(pin2, 0);
 delay(200);
digitalWrite(pin3, 0);
    delay(200);
digitalWrite(pin4, 0);
   delay(200);
digitalWrite(pin5, 0);
delay(200);
digitalWrite(pin6, 0);
delay(200);
digitalWrite(pin7, 0);
delay(200);
digitalWrite(pin8, 0);
delay(200);
digitalWrite(pin9, 0);
delay(1000);
    
        }





    digitalWrite(pos1, 1);
    digitalWrite(pos2, 1);
    digitalWrite(pos3, 1);
  
    digitalWrite(pin1, 0);
    digitalWrite(pin2, 0);
    digitalWrite(pin3, 0);
    digitalWrite(pin4, 0);
    digitalWrite(pin5, 0);
    digitalWrite(pin6, 0);
    digitalWrite(pin7, 0);
    digitalWrite(pin8, 0);
    digitalWrite(pin9, 0);
  }




















    




   
  
     


int
  i = 0; 
int button = 34;  
unsigned long t_1 = millis();   
unsigned long t_2 = millis(); 
int mode = 32; 


#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define i2c_Address 0x3c

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64 


Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);



void
  setup() {
  Serial.begin(9600);

  // initialize OLED display with address 0x3C for 128x64
 // if (!display.begin(SSD1106G_SWITCHCAPVCC, 0x3C)) {
 //   Serial.println(F("SSD1106 allocation failed"));
 //   while (true);
//  }

  delay(250); 
  display.begin(i2c_Address, true); 
  
  delay(2000); 
  display.clearDisplay(); 
  
  pinMode(button,
  INPUT); 
}

void loop() {
  

  if (digitalRead(button) == HIGH){
    mode += 1;   
    delay(500); 

  }
  

  if (mode == 0){
    mode_0(); 
  }
  else if (mode == 1){
    mode_1();
  }

  else if (mode == 2){
    mode_2();
  }
  else{
    mode = 0;  
    mode_0();

  }
}

void mode_0(){
  
  if (millis() - t_1 > 300){
    i += 1;
    t_1 = millis();
    display.clearDisplay();
     
    if (i >= 4){
      i = 0;
    }
    if (millis() - t_2 < 2000){
      display.drawCircle(0,0,24,SH110X_WHITE);

      display.drawCircle(0,0,28,SH110X_WHITE);
    }
    else{
      if (millis()
  - t_2 > 7000){
        t_2 = millis();
      }
      
      display.drawCircle(0,0,16
  + (i * 2),SH110X_WHITE);
      display.drawCircle(0,0,20 + (i * 2),SH110X_WHITE);
      

      if (i < 2){
      display.drawCircle(0,0,24 + (i * 2), SH110X_WHITE);
      }

      
      if (i < 1){
      display.drawCircle(0,0,28 + (i * 2),SH110X_WHITE);
   
      }  
    }
      
    display.fillCircle(0,0,20,SH110X_WHITE); 
    display.drawRoundRect(105, 10, 20, 45, 3, SH110X_WHITE);

 
    display.setTextColor(SH110X_WHITE);
    display.setTextSize(1);

    


    display.setCursor(106,0);
    display.println("MAX");

    display.setCursor(106,57);

    display.println("MIN");

    display.setTextColor(SH110X_WHITE);

    display.setTextSize(3);
    
    
    display.setCursor(SCREEN_WIDTH / 2 - 10, 0);
    display.println("UV");


    float media = 0; 



    for (int j = 0;  j < 5; j++){
      int sensor_value = analogRead(A0); 
      media += sensor_value;
    }

    Serial.println(media);


    
    media  = media/5; 
    media = round(media);



    Serial.print("Media:");
    Serial.println(media);



    if (media <= 9){
      display.setCursor(63,30);
    }
    else if(media  <= 99){
      display.setCursor(54,30);
    }
    else{
      display.setCursor(42,30);

    }
    
    display.print(int(media));
      
    display.setTextSize(1);


    
    for (int j = 9; j <= 36 ; j += 9 ){
      display.fillRect(105, 55 - j, 20, 1, SH110X_WHITE); 
    }

 
    if(media > 0){
     

      if(media >= 290){ 
        display.fillRoundRect(105, 10, 20, 45, 3, SH110X_WHITE);

      }   
   
      else if(media >=  256){
        display.fillRoundRect(105, 19, 20, 36, 3, SH110X_WHITE);
      }

      
      else if(media >= 178){

        display.fillRoundRect(105, 28, 20, 27, 3, SH110X_WHITE);
      }
    
      else if(media >= 121){
        display.fillRoundRect(105,
  37, 20, 18, 3, SH110X_WHITE);
        }
     
      else{
        display.fillRoundRect(105, 46, 20, 9, 3, SH110X_WHITE);

      }
    }
      
    display.display();

  }
}



void mode_1(){

  float media = 0; 


  display.clearDisplay();
  
  display.setCursor(0,0);
  display.setTextSize(1);
  display.println("UV INDEX"); 

  display.drawTriangle(93,59,66,5,120,5,SH110X_WHITE); 


  for
  (int j = 0; j < 9; j ++){
    display.drawTriangle(93, 59, 66 + (j*3), 5 + (j*6),120 - (j*3), 5 + (j*6), SH110X_WHITE);
  }
  

  for (int j = 0;  j < 5; j++){
    int sensor_value = analogRead(A0);
    media += sensor_value;
  }
  
  Serial.println(media);
  

  media = media / 5;
  media = round(media);



  Serial.print("Media:");
  Serial.println(media);

  
  if (media > 5){
    if (media < 69){

      display.fillTriangle(93,59,90,53,96,53, SH110X_WHITE); 
      cursor0();

      display.println("<1"); 

      cursor1(); 
      display.println("Bajo");
  // risk of harm
    }
    else if(media <= 121){
      display.fillTriangle(93,59,90,53,96,53,SH110X_WHITE); 
      cursor0(); 
      display.println("1"); 
      cursor1();
      display.println("Bajo");  
    }
    else
  if(media <= 178){
      display.fillTriangle(93,59,87,47,99,47, SH110X_WHITE); 
      cursor0(); 
      display.println("2");

      cursor1(); 
      display.println("Bajo");

    }
    else if(media <= 211){
      display.fillTriangle(93,59,84,41,102,41, SH110X_WHITE); 
      cursor0();

      display.println("3"); 
      cursor2();
      display.println("Moderado");
    }
    else
  if(media <= 237){
      display.fillTriangle(93,59,81,35,105,35, SH110X_WHITE); // fill the graph
      cursor0(); 
      display.println("4");
  // UV index
      cursor2(); 
      display.println("Moderado");
  // risk of harm
    }
    else if(media <= 256){
      display.fillTriangle(93,59,78,29,108,29, SH110X_WHITE); // fill the graph
      cursor0(); 
      display.println("5"); // UV index
      cursor2(); 
      display.println("Moderado"); // risk of harm
    }
    else
  if(media <= 273){
      display.fillTriangle(93,59,75,23,111,23, SH110X_WHITE); // fill  the graph
      cursor0(); 
      display.println("6");
  // UV index
      cursor1(); 
      display.println("Alto");
  // risk of harm
    }
    else if(media <= 290){
      display.fillTriangle(93,59,72,17,114,17, SH110X_WHITE); // fill the graph
      cursor0(); 

      display.println("7"); 
      cursor1(); 
      display.println("Alto");
    }
    else
  if(media <= 311){
      display.fillTriangle(93,59,69,11,117,11, SH110X_WHITE); // fill  the graph
      cursor0(); 
      display.println("8");
  // UV index
      cursor2(); 
      display.println("Muy alto"); 
    }
    else if(media > 311){
      display.fillTriangle(93,59,66,5,120,5, SH110X_WHITE); // fill the graph
      cursor0();
      display.println("9+");
      cursor2(); 
      display.println("Muy alto"); 

    }
  }
  else{
    cursor0(); 

    display.println("0"); 
    cursor1(); 
    display.println("Bajo"); 
  }
  display.display();
  // display the drawn info
}


void
  mode_2(){
  display.clearDisplay(); 


  display.setTextSize(2);
  display.setCursor(11,5);

  display.println("UVChecker");
  
 
  display.setTextSize(1);
  display.setCursor(30,32);

  display.drawRoundRect(9, 28, 110, 16, 3, SH110X_WHITE); 
  display.print("FIUSAC - EA1"); 
  display.display();
 
}


void cursor0(){
  display.setCursor(10,15);
  display.setTextSize(4);
}


void cursor1(){

  display.setCursor(5,50);
  display.setTextSize(1); 
}


void cursor2(){
  display.setCursor(0,50);

  display.setTextSize(1);
}

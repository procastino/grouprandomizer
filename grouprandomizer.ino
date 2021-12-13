//M5 stick c plus library
#include <M5StickCPlus.h>

//supposedly, this is needed for bootloader_random_enable() to compile
extern "C" {
#include "bootloader_random.h"
}

//variables for acceleration on different axis, we just would need one
float accX = 0;
float accY = 0;
float accZ = 0;
//acceleration threshold for the randomizer to start
float threshold = 4;
//Huge array with all the students names in the groups.Name length should not exceed 10 characters
char *names[] = {"Lucia A.", "Antia", "Rodrigo", "Alvaro Al.", "Adriana", "Alvaro Am.", "Claudia", "Laura", "Hugo C.", 
"Lucia C.", "Cristina", "Aischa", "Raul", "Noemi", "Alejandro", "Hugo S.", "Ivan", "Sheila", "Soraya",/*2A*/
"Aldan", "Alba", "Aroa", "Brayan", "Nerea", "Sofia", "Yoli", "Javi", "Alexander", "Lucia", "David", "Benxamin", "Pablo", "Brais", "A. Pena", 
"Nerea", "A. Porrua", "Sarai", "Marta",/*2b*/
"Cynthia", "Sara", "Lara", "Yaiza", "Gael","Nerea", "Ainhoa", "Alejandro", "Julia", "Alvaro", "Samuel", "Ainara", "Maria", /*3A*/
"Xulio", "Anxo A.", "Alex", "Anxo B.", "Saray", "Eloy", "Ivan", "Angel", "Ines", "Lucia", "Lorena", "Kevin", "Theodor", /*3b*/
"Laura ", "Carlos", "Izan", "Claudia","Virginia", "Facundo", "Juan", "Pablo", "Carme", "Daniel", "Samuel", "Marcos", "Sergio", "Rodrigo", /*4*/
"Alexia", "Laura B.", "Carlos","Christian","Maria", "Uxia", "Laura V.", "Izan", "Claudia","Virginia", "Facundo", "Juan", "Pablo", "Carme", 
"Daniel", "Samuel", "Marcos V.", "Sergio", "Rodrigo", "Marcos C.", "Pedro" /*TICS*/};
//with this two variables we define the limits of each group in the names array
int startName = 0;
int endName = 2;
// this are the groups we have
char *groups[] = {"2A", "2B", "3A", "3B", "4", "TIC"};
int group = 0;


void setup() {
  M5.begin(); //Init M5StickC Plus.  初始化 M5StickC Plus
  M5.Imu.Init();  //Init IMU.  初始化IMU
  M5.Lcd.setRotation(3);  //Rotate the screen. 将屏幕旋转
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(50, 15); //set the cursor location.  设置光标位置
  M5.Lcd.println("SORTEADOR");
  //this should make use of the esp32 hardware true random generator
  bootloader_random_enable();
  M5.Lcd.setCursor(10, 85);
  M5.Lcd.setTextSize(4);
  M5.Lcd.fillScreen(BLACK);
  //we print out the group which we are going to randomize
  M5.Lcd.setTextColor(YELLOW);
  M5.Lcd.println(groups[group]);
  
  
}


void loop() {
  //check if buttons were pressed
  M5.update();
  if (M5.BtnA.wasReleased()){
    //we change the group index to switch the group we are randomizing
    group++;
    if(group == 6){
      group = 0;
    }
    //we define start and end students for each group inside the array
    switch (group){
      case 0:
      //2a
      startName = 0;
      endName = 18;
      break;
      case 1:
      //2b
      startName = 19;
      endName = 37;
      break;
      case 2:
      //3a
      startName = 38;
      endName = 50;
      break;
      case 3:
      //3b
      startName = 51;
      endName = 63;
      break;
      case 4:
      //4 tecno
      startName = 64;
      endName = 77;
      break;
      default:
      startName = 78;
      endName = 98;
      break;
    }
    M5.Lcd.setCursor(10, 85);
    M5.Lcd.setTextSize(4);
    M5.Lcd.fillScreen(BLACK);
    //we print out the group which we are going to randomize
    M5.Lcd.setTextColor(YELLOW);
    M5.Lcd.println(groups[group]);
    
  }
  //check if the Stick has been accelerated
  M5.Imu.getAccelData(&accX,&accY,&accZ);
  //if it is shaken enough, it will print a random name of the student to answer
  if( accZ > threshold){
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(50, 15);
    M5.Lcd.print("Contesta");
    //little loop for dramatic purposes
    for (int i = 0; i<6;i++){
    delay(300);
    M5.Lcd.print(".");
    }
    M5.Lcd.setTextSize(3);
    M5.Lcd.setTextColor(BLUE);
    M5.Lcd.setCursor(30, 80);
    M5.Lcd.print(names[random(startName, endName+1)]);//chooses a random name within the limits set for the group
  }
    
  delay(20);
}

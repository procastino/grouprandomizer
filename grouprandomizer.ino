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
char *names[] = {
  "AA", "BB", "CC", "DD", "EE", "FF",/*2A*/
  "GG", "HH", "II", "JJ", /*2b*/
  "KK", "LL", "MM", "NN", /*3A*/
  "OO", "PP", /*3b*/
  "QQ ", "RR", "SS", "TT","UU",  /*4*/
  "VV", "XX", "YY","ZZ" /*TICS*/
  };
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
      endName = 5;
      break;
      case 1:
      //2b
      startName = 6;
      endName = 9;
      break;
      case 2:
      //3a
      startName = 10;
      endName = 13;
      break;
      case 3:
      //3b
      startName = 14;
      endName = 15;
      break;
      case 4:
      //4 tecno
      startName = 16;
      endName = 20;
      break;
      default:
      startName = 21;
      endName = 24;
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

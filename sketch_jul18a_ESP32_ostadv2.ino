/*  
 Test the tft.print() viz the libraries embedded write() function

 This sketch used font 2, 4, 7
 
 Make sure all the required fonts are loaded by editing the
 User_Setup.h file in the TFT_eSPI library folder.

  #########################################################################
  ###### DON'T FORGET TO UPDATE THE User_Setup.h FILE IN THE LIBRARY ######
  #########################################################################
 */
#define BLACK 0x0000
#define NAVY 0x000F
#define DARKGREEN 0x03E0
#define DARKCYAN 0x03EF
#define MAROON 0x7800
#define PURPLE 0x780F
#define OLIVE 0x7BE0
#define LIGHTGREY 0xC618
#define DARKGREY 0x7BEF
#define BLUE 0x001F
#define GREEN 0x07E0
#define CYAN 0x07FF
#define RED 0xF800
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF
#define ORANGE 0xFD20
#define GREENYELLOW 0xAFE5
#define PINK 0xB9C7
#define light_gray 0xD3D3D3
#include <SPI.h>
uint16_t color;
#define TEXT "aA MWyz~12"
#include "Free_Fonts.h"
#include <TFT_eSPI.h>  // Hardware-specific library
int i = 332;
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "time.h"
int rr = 0;
TFT_eSPI tft = TFT_eSPI();  // Invoke custom library
//TFT_eSPI tft = TFT_eSPI();

HTTPClient http;
#define TFT_GREY 0x5AEB  // New colour
const char* ssid = "Matin_Bax";
const char* password = "matin123";
const char* ntpServer = "pool.ntp.org";
const char* serverName = "http://5.10.248.142/api/Books/1";
const long gmtOffset_sec = 12600 - 3600;
const int daylightOffset_sec = 3600;
double tt = 0.00;
double fwlo_p = 0;
char r[80];
char m[80];
char s[80];

char HH[80];
char MM[80];

unsigned long Time_circle = 0;
unsigned long Time_text = 0;
int ghasemi = 0;
int x = 0;


double flow; //Liters of passing water volume
unsigned long pulse_freq;
void setup() {
  ghasemi = 2;
   pinMode(34, INPUT);
  Serial.begin(115200);
  attachInterrupt(34, pulse, RISING); // Setup Interrupt
  tft.setSwapBytes(true); 
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(BLACK);
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  tft.setCursor(50, 30);
  tft.setTextSize(3);
  tft.print("Connecting to WiFi");

  delay(250);

  

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    tft.setCursor(50, 30);
  tft.setTextSize(3);
  tft.print("Connecting to WiFi");
  }
   tft.setCursor(50, 30);
  tft.setTextSize(3);
  tft.print("                  ");
}

void loop() {
    flow = .00225 * pulse_freq;
  tft.pushImage(30,60,204,309,modares);  //ابعاد نمایش

   Serial.print("felow =");
  Serial.print(flow);

  Serial.print("         ");

  Serial.print("flow_p =");
  Serial.println(fwlo_p);
// tft.fillRect(130,190,80,40,BLUE); //fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t t)
   if(flow - fwlo_p >= 2 || ghasemi != 0){
   

    int s = get();
    int f = int(flow);
    //int result
    delay(250);
   put(s+f);
   //int nn = get();
    tft.setCursor(20, 220);
    tft.setFreeFont(&FreeSansBold9pt7b);
    tft.setTextSize(1);
    tft.print("usage water ");
    tft.setFreeFont(&FreeSansBold18pt7b);
    tft.fillRect(130,190,80,40,BLACK); //fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t t)
    //tft.setCursor(40, 220);
 
    tft.setTextColor(PINK);
    tft.print(s+f);
    tft.setFreeFont(&FreeMonoOblique12pt7b);
    tft.setTextSize(1);
    tft.print("L");

    // text of battery

    tft.setCursor(20, 260);
    //tft.setFreeFont(TT1);
    // tft.textfont(TT1);
    //tft.setFreeFont(&TomThumb);
    //tft.setTextSize(4);
    tft.setFreeFont(&FreeSansBold9pt7b);
    tft.setTextSize(1);
    tft.print("Battery");
    tft.setFreeFont(&FreeSansBold18pt7b);
    tft.print("20");
    tft.setFreeFont(&FreeMonoOblique12pt7b);
    tft.setTextSize(1);
    tft.print("%");
   c();
    circle(s+f);
    circle2();

   ghasemi = 0;
    fwlo_p = flow;
    Serial.print("work");
   
  }
   
    // if (rr == 7){
    //   flow = 0.0;
    //   rr = 0;
    //   Serial.print("pesar shoja");
    // }
    // Serial.print(flow, DEC);
    // Serial.println("L");


  //  while (!getLocalTime(&timeinfo)){
  //  Serial.println("Failed to obtain time");
  //   return;
  // }
  // Fill screen with random colour so we can see the effect of printing with and without
  // a background colour defined
  //tft.fillScreen(BLACK);
  // create qrcode
  /*tft.setCursor(20, 220);
  //tft.print("hhhhhhhhhhhhhhhh");
  tft.drawLine(40 + 10, 20, 50 + 10, 50, BLUE);
  tft.drawLine(50 + 10, 50, 40 + 10, 80, BLUE);  // HROF X = 40 ; Y = 60

  tft.drawLine(40 + 10, 80, 15 + 10, 80, BLUE);  //KAFF

  tft.drawLine(15 + 10, 80, 5 + 10, 50, BLUE);
  tft.drawLine(15 + 10, 20, 5 + 10, 50, BLUE);

  tft.drawLine(40 + 10, 20, 15 + 10, 20, BLUE);

  tft.setCursor(90, 30);*/

  //tft.setTextColor(YELLOW);
 // if (millis() - Time_circle > 2000) {
//     for (int x = 0; x < 90; x = x+1) {

// //statement(s);

//     c();
//     circle(16);
//     circle2();
//     // Time_circle = millis();
//     // ghasemi = 0;
//     // Serial.println(x);
//     // delay(500);
// }
    
 // }
  // tft.fillRect(87, 20, 135, 47, BLUE);  //fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t t)
  // tft.setTextSize(1);
  // tft.setTextColor(WHITE);
  // tft.print("hex shower");


  // milis =====================================text of water

  /*if (flow - tt >= 1.0 ) {
    int s = get();
    int f = int(flow);
    delay(250);
   put(s+f);
   int nn = get();
    tft.setCursor(20, 220);
    tft.setFreeFont(&FreeSansBold9pt7b);
    tft.setTextSize(1);
    tft.print("usage water ");
    tft.setFreeFont(&FreeSansBold18pt7b);
    tft.print(nn);
    tft.setFreeFont(&FreeMonoOblique12pt7b);
    tft.setTextSize(1);
    tft.print("L");

    // text of battery

    tft.setCursor(20, 260);
    //tft.setFreeFont(TT1);
    // tft.textfont(TT1);
    //tft.setFreeFont(&TomThumb);
    //tft.setTextSize(4);
    tft.setFreeFont(&FreeSansBold9pt7b);
    tft.setTextSize(1);
    tft.print("Battery");
    tft.setFreeFont(&FreeSansBold18pt7b);
    tft.print("20");
    tft.setFreeFont(&FreeMonoOblique12pt7b);
    tft.setTextSize(1);
    tft.print("%");
    // Serial.println(flow);
   rr = 7;
    // clock
    // tft.setCursor(20, 300);
    // tft.setFreeFont(&FreeSansBold9pt7b);
    // tft.setTextSize(1);
    // tft.print(fadeai(1));
    // tft.print("  ");
    // tft.print(fadeai(2));
    // tft.setTextFont(4);
 tt = flow;
 Serial.print(tt);
    // delay(500);
   // Time_text = millis();
    
    //break;
  }*/
}




//////////////////////////////////////////////////////////////////
void circle(int d) {

  for (int p = 0; p <= d *133.4; p++) {
    int j = 115 * (sin(PI * p / 2000));
    int i = 115 * (cos(PI * p / 2000));
    int j2 = 85 * (sin(PI * p / 2000));
    int i2 = 85 * (cos(PI * p / 2000));

    tft.drawLine(i2 + 345, j2 + 170, i + 345, j + 170, BLACK);
    // tft.drawCircle(i2 + 345,j2 + 170,30,WHITE); //drawCircle(int16_t x, int16_t y, int16_t r, uint16_t t)
  }




  for (int p = 0; p <= d *133.4; p++) {
    int j = 115 * (sin(PI * p / 2000));
    int i = 115 * (cos(PI * p / 2000));
    int j2 = 85 * (sin(PI * p / 2000));
    int i2 = 85 * (cos(PI * p / 2000));

    tft.drawLine(i2 + 345, j2 + 170, i + 345, j + 170, NAVY);
    // tft.drawCircle(i2 + 345,j2 + 170,30,WHITE); //drawCircle(int16_t x, int16_t y, int16_t r, uint16_t t)
  }
tft.fillRect(310,170,80,40,BLACK); //fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t t)
  tft.setCursor(320, 200);
  tft.setTextColor(PINK);
  tft.setFreeFont(&FreeSansBold18pt7b);
  tft.setTextSize(1);
d = map(d,0,30,0,100);
  String r = String(d);
  r = r + "%";
  tft.print(r);
}
void circle2() {
  for (int y = 0; y <= 4000; y++) {

    int jx = 120 * (sin(PI * y / 2000));
    int ix = 120 * (cos(PI * y / 2000));
    int j2x = 115 * (sin(PI * y / 2000));
    int i2x = 115 * (cos(PI * y / 2000));

    tft.drawLine(i2x + 345, j2x + 170, ix + 345, jx + 170, WHITE);
  }
}
String fadeai(int var) {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {

    return "Failed to obtain time";
  }
  strftime(r, 80, "%m", &timeinfo);
  strftime(m, 80, "%d", &timeinfo);
  strftime(s, 80, "%G", &timeinfo);

  strftime(HH, 80, "%H", &timeinfo);
  strftime(MM, 80, "%M", &timeinfo);
  String j = r;
  j = j + "/";
  j = j + m;
  j = j + "/";
  j = j + s;
  ////
  String k = HH;
  k = k + ":";
  k = k + MM;
  // return k;
  //return j;

  switch (var) {

    case 1:
      return j;
      break;

    case 2:
      return k;
      break;
  }
}

void pulse () // Interrupt function

{
  pulse_freq++;
}

void put(int mm){
// Create JSON document for PUT request
  StaticJsonDocument<200> putDoc;
  putDoc["debi"] = mm;
  //putDoc["value"] = "your_value";
  String putPayload;
  serializeJson(putDoc, putPayload);

  // PUT request
  http.begin(serverName);
  http.addHeader("Content-Type", "application/json");
  int httpResponseCode = http.PUT(putPayload);

  if(httpResponseCode>0){
    String response = http.getString();
    Serial.println(httpResponseCode);
    Serial.println(response);
  }

  http.end();
  delay(500);
}

int get(){
// GET request
  http.begin(serverName);
  int httpResponseCode = http.GET();

  if(httpResponseCode>0){
    String response = http.getString();
    Serial.println(httpResponseCode);
    
    // Parse JSON response
    StaticJsonDocument<200> getDoc;
    deserializeJson(getDoc, response);
    int keyValue = getDoc["debi"];
    
    
    return keyValue;
    // Serial.println(valueValue);
  }else{
    Serial.print("Error on sending GET Request: ");
    Serial.println(httpResponseCode);
  }

  http.end();

  
}
void c(){

  tt = tt  * 0;
}




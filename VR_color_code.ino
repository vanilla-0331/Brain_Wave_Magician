#include <Adafruit_NeoPixel.h>

#define SW_PIN   8
#define DIN_PIN  4
#define NUM_LEDS 12

Adafruit_NeoPixel pixels(NUM_LEDS, DIN_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, DIN_PIN, NEO_GRB + NEO_KHZ800);

/* 消灯の要素 0 */
uint32_t black2 = pixels.Color(0, 0, 0);
uint32_t black_color[] = {black2, black2, black2, black2, black2, black2, black2, black2, black2, black2, black2, black2};
int black_index[] = {11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

/* 赤色の要素 1 */
uint32_t red2 = pixels.Color(255, 0, 0);
uint32_t red_color[] = {red2, red2, red2, red2, red2, red2, red2, red2, red2, red2, red2, red2};
int red_index[] = {11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

/* オレンジ色の要素 2 */
uint32_t orange2 = pixels.Color(255, 80, 0);
uint32_t orange_color[] = {orange2, orange2, orange2, orange2, orange2, orange2, orange2, orange2, orange2, orange2, orange2, orange2};
int orange_index[] = {11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

/* 青色の要素 3 */
uint32_t blue2 = pixels.Color(0, 0, 255);
uint32_t blue_color[] = {blue2, blue2, blue2, blue2, blue2, blue2, blue2, blue2, blue2, blue2, blue2, blue2};
int blue_index[] = {11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

/* 緑色の要素 4 */
uint32_t green2 = pixels.Color(0, 255, 0);
uint32_t green_color[] = {green2, green2, green2, green2, green2, green2, green2, green2, green2, green2, green2, green2};
int green_index[] = {11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

int i = 0;             //LEDの色分け用
int s = 5;             //LEDのスピード制御用
bool setLED = true;    //LEDの発光制御用
bool mode1 = false;    //swの制御用
char attribute;        //属性変更制御用

void setup() 
{
  pixels.setBrightness(100);
  Serial.begin(115200);
  pinMode(SW_PIN, INPUT_PULLUP);
}

/* 動作開始 */
void loop() 
{
  if(setLED)
  {
    /* 色変更 */
    sw();
  }
  /* スイッチの動作 */
  switch_behavior();
  delay(50);  
}

/* スイッチの動作 */
void switch_behavior()
{
  /* swの制御 */
  if(digitalRead(SW_PIN) == LOW)
  {
    int counter = 0; //長押し判定用のカウンタ
    while(digitalRead(SW_PIN) == LOW)
    {
      counter++;
      delay(5);   
    }
    /* 長押ししたら、メニューモード */
    if(counter > 50){
      Serial.print("menu_mode");
      Serial.println();
    }
    /* 短押ししたら、属性選択モード */
    else
    {   
      sw();
      setLED = true; //再度，点灯しなおす
    }
  }
}

void sw()
{ 
  if(Serial.available() > 0) // 受信データがあるか？
  { 
    attribute = Serial.read();
    switch(attribute)
    {
      case 'f' : red();
                 break;
      case 'i' : blue();
                 break;
      case 's' : orange();
                 break;
      case 'm' : green();
                 break; 
    }
  }
}

void red()
{
  if(setLED)
  {
    pixels.clear();    
    for(int j = 0 ; j < NUM_LEDS; j++) 
    {    
      pixels.setPixelColor(red_index[NUM_LEDS - j - 1], red_color[NUM_LEDS - j - 1]);
      pixels.begin(); 
      pixels.show();
      delay(s);
    }
  }
  /*点灯の制御処理を変更*/
  //setLED = false;
}

void blue()
{
  if(setLED)
  {
    pixels.clear();    
    for(int j = 0 ; j < NUM_LEDS; j++) 
    {    
      pixels.setPixelColor(blue_index[NUM_LEDS - j - 1], blue_color[NUM_LEDS - j - 1]);
      pixels.begin();
      pixels.show();
      delay(s);
    }
  }
  /*点灯の制御処理を変更*/
  //setLED = false;
}

void orange()
{
  if(setLED)
  {
    pixels.clear();    
    for(int j = 0 ; j < NUM_LEDS; j++) 
    {    
      pixels.setPixelColor(orange_index[NUM_LEDS - j - 1], orange_color[NUM_LEDS - j - 1]);   
      pixels.begin();
      pixels.show();
      delay(s);
    }
  }
  /*点灯の制御処理を変更*/
  //setLED = false;
}


/* 今は使用しない */
void green()
{
  if(setLED)
  {
    pixels.clear();    
    for(int j = 0 ; j < NUM_LEDS; j++) 
    {    
      pixels.setPixelColor(green_index[NUM_LEDS - j - 1], green_color[NUM_LEDS - j - 1]);
      pixels.begin();
      pixels.show();
      delay(s);
    }
  }
  /*点灯の制御処理を変更*/
  //setLED = false;
}

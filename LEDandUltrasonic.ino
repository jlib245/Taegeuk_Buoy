#include <Adafruit_NeoPixel.h>

#define ledPin 4 // LED 스트립 연결 핀
#define ledPixelsNum 8 // LED 개수
Adafruit_NeoPixel strip = Adafruit_NeoPixel(ledPixelsNum, ledPin, NEO_GRB + NEO_KHZ800);

#define trigPin 2 // 초음파 센서 Trig 연결 핀
#define echoPin 3 // 초음파 센서 Echo 연결 

#define redDistance 200
#define yellowDistance 100

#define brightness 100 // 빛의 밝기

int r, g, b, i, ledNum;

void setup() {
  Serial.begin(9600);
  strip.begin();
  strip.show();

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void ledDisplay(long distance) {
  if (distance >= 300) {
    ledNum = 8;
  }
  else {
    ledNum = map(distance, 0, 300, 1, 8);
  }
  if (distance >= redDistance) {
    r = brightness;
    g = 0;
    b = 0;
  }
  else if (distance >= yellowDistance) {
    r = brightness;
    g = brightness;
    b = 0;
  }
  else {
    r = 0;
    g = brightness;
    b = 0;
  }
  for(i=0; i<ledNum; i++) {
    strip.setPixelColor(i, strip.Color(r, g, b)); // 표시할 개수만큼 LED 불 켜기
  }
  for(i=ledNum; i < ledPixelsNum; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0)); // 표시할 개수를 제외한 LED 불 끄기
  }
}

void loop() {
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; // 기간 -> 거리 변환

  Serial.print("Distance: ");
  Serial.println(distance);

  ledDisplay(distance);
  strip.show(); // LED 업데이트
  delay(500);
}

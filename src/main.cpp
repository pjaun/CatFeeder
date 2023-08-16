// เริ่มต้นด้วยการโหลด Library ต่าง ๆ ที่ต้องใช้
#include <Arduino.h>
#include <TridentTD_LineNotify.h> //สำหรับการส่งข้อความใน LINE Notify
#include <SPI.h>
#include <Ethernet.h>
#include <BlynkSimpleEthernet.h>
#include <TimeLib.h>
#include <WidgetRTC.h>

#define BLYNK_PRINT Serial // Enables Serial Monitor

/* Fill in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPxxxxxx"
#define BLYNK_TEMPLATE_NAME "Device"
#define BLYNK_AUTH_TOKEN "YourAuthToken"

#define LINE_TOKEN "xxxxxxxxxxxxxxxxxxxxxxxxxx" // ใส่ รหัส TOKEN ที่ได้มาจากข้างบน

BlynkTimer timer;
WidgetRTC rtc;

void requestTime()
{
  Blynk.sendInternal("rtc", "sync");
}

BLYNK_WRITE(InternalPinRTC)
{
  long t = param.asLong();
  Serial.print("Unix time: ");
  Serial.print(t);
  Serial.println();
}

BLYNK_CONNECTED()
{
  // Synchronize time on connection
  rtc.begin();
  LINE.setToken(LINE_TOKEN);
}

void Start_Feed()
{
  // เริ่มต้นให้อาหาร
}

void Stop_Feed()
{
  // หยุดให้อาหาร
}

void setup()
{
  // put your setup code here, to run once:
  // See the connection status in Serial Monitor
  Serial.begin(9600);

  // Here your Arduino connects to the Blynk Cloud.
  Blynk.begin(BLYNK_AUTH_TOKEN);
  timer.setInterval(10000L, requestTime);
}

void loop()
{
  // put your main code here, to run repeatedly:
  Blynk.run();
  timer.run();
}
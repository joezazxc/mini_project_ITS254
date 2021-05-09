#define BLYNK_PRINT Serial      // สำหรับ print monitor
#include <ESP8266WiFi.h>        //  ไลบรารี่ของชิป ESP8266 WiFi
#include <BlynkSimpleEsp8266.h> // ไลบรารี่ส่วนเชื่อมต่อแอพ Blynk

char auth[] = "VQK8hSeVaybwt07vuFwdMd9L8SUCElje"; // รหัสเฉพาะสำหรับ Thing (Authen Key) ได้จากแอพ Blynk
char ssid[] = "KJS";                              // ชื่อ WiFi ของบ้าน
char pass[] = "025991954";                        //พาสเวิร์ด WiFi

String soilmsg = ""; //ตัวแปรเก็บข้อความ ความชื้นในดิน
String soilpercentmsg = ""; //ตัวแปรเก็บข้อความ ความชื้นในดินเป็นเปอร์เซ็น

const int AirValue = 666; //ค่าความชื้นในอากาศ
const int WaterValue = 120; //ค่าความชื้นในน้ำ

int LED = 2; //ขาหลอดไฟ
String pump = "D4"; //ขาปั้มน้ำ
int delay_time = 500; //ค่าหน่วยเวลา
String analogPin = "A0"; //ขารับค่าความชื้น
int enable = 0;//ตัวแปรกำหนด เปิด-ปิด ระบบ

int soil = 0; //ค่าความชื้น
int soilpercent = 0; //ค่าความชื้นเป็นเปอร์เซ็นต์

WidgetLCD lcd(V0);//กำหนดใช้จอ LCD ในแอป Blynk

void sendSoil(int soil, int soilpercent) //ฟังก์ชั่นโชว์ข้อความในแอป Blynk โดยพารามิเตอร์แรกเป็นค่าความชื้น พารามิเตอร์ที่สองเป็นค่าความชื้นแบบเปอร์เซ็นต์
{
    soilmsg = String("soil : ") + String(soil); //รวมค่าความชื้นเป็นข้อความ
    soilpercentmsg = String("precent : ") + String(soilpercent) + String(" %"); //รวมค่าความชื้นเป็นเปอร์เซ็นต์
    Blynk.virtualWrite(V1, soil); //แสดงค่าความชื้นในแอป Blynk
    Blynk.virtualWrite(V2, soilpercent); //แสดงค่าความชื้นแบบเปอร์เซ็นต์ในแอป Blynk
    lcd.print(0, 0, soilmsg); //แสดงค่าความชื้นบนจอ LCD
    lcd.print(0, 1, soilpercentmsg); //แสดงค่าความชื้นแบบเปอร์เซ็นต์บนจอ LCD
    Serial.println(soilmsg); //log ค่าความชื้น
    Serial.println(soilpercentmsg); //log ค่าความชื้นแบบเปอร์เซ็นต์
}

void setup() //ตั้งค่า
{
    pinMode(LED, OUTPUT); //กำหนดให้ขา LED เป็น OUTPUT
    pinMode(pump, OUTPUT);  //กำหนดให้ขา pump เป็น OUTPUT
    Serial.begin(9600); //กำหนดช่องทางการเชื่อมต่อกับคอมพิวเตอร์
    Blynk.begin(auth, ssid, pass, "blynk.iot-cm.com", 8080); //ตั้งค่าแอป Blynk โดยใช้ server ที่กำหนดเอง
    lcd.clear(); //reset จอ lcd
}

BLYNK_WRITE(V3) // ON-OFF ปุ่ม
{
    if (param.asInt() == 1) //ถ้ามีการกดปุ่ม V3 ในแอป Blynk
    {
        enable = 1; //เปิดระบบ
        Blynk.virtualWrite(V3, 1); //ตั้งค่าให้ปุ่ม V3 เป็นเปิด
    }
    else //ถ้าไม่
    {
        enable = 0; //ปิดระบบ
        Blynk.virtualWrite(V3, 0); //ตั้งค่าให้ปุ่ม V3 เป็นปิด
    }
}

void loop()
{
    Blynk.run(); //สั่ง Blynk ทำงาน
    if (enable == 1) // ถ้าเปิดระบบ
    {
        soil = analogRead(analogPin); //เก็บค่าความชื้นที่ได้จากขา analogPin 
        soilpercent = map(soil, AirValue, WaterValue, 0, 100); //เก็บค่าความชื้นเป็นเปอร์เซ็นต์ โดยเอาค่าความชื้นที่เก็บได้มา map กับความชื้นของอากาศและน้ำ
        sendSoil(soil, soilpercent); //ส่งค่าความชื้นและ ค่าความชื้นแบบเปอร์เซ็นต์ไปแสดงผลในแอป Blynk ผ่านฟังก์ชั่น sendSoil
        if (soilpercent <= 40) //ค่าความชิ้นในดินน้อยกว่า หรือเท่ากับ 40%
        {
            digitalWrite(LED, LOW); //เปิดไฟ LED
            digitalWrite(pump, HIGH); //ปั้มน้ำทำงาน
        }
        else //ถ้าไม่
        {
            digitalWrite(LED, HIGH); //ปิดไฟ LED
            digitalWrite(pump, LOW); //ปิดปั้มน้ำ
        }
    }
    else //ถ้าไม่เปิดระบบ
    {
        lcd.clear(); //reset จอ LCD
        digitalWrite(LED, HIGH); //ปิดไฟ LED
        digitalWrite(pump, LOW); //ปิดปั้มน้ำ
    }
    delay(delay_time); //หน่วงเวลา (500 ms)
}

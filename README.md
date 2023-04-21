## Soil Moisture Monitoring and Irrigation System using Blynk and ESP8266

This project is part of the NBU-ITS254 course. It encompasses the monitoring of soil moisture levels and controlling the irrigation system using Blynk application and ESP8266 microcontroller.

### Components Used
- ESP8266 Wi-Fi microcontroller
- Soil Moisture Sensor
- Relay module
- Water pump
- LED
- Breadboard and connecting wires
- Power supply

### Libraries Used
- ESP8266WiFi.h
- BlynkSimpleEsp8266.h

### Blynk App Configuration
1. Create a new project in the Blynk app.
2. Add a gauge widget (V1) to display the soil moisture level.
3. Add a level bar widget (V2) to display the soil moisture level as percentage.
4. Add a button widget (V3) to turn the irrigation system on and off.
5. Add an LCD widget (V0) to display the current soil moisture level and percentage.

### Circuit Diagram
![Circuit Diagram](https://www.ai-corporation.net/wp-content/uploads/2022/07/%E0%B8%81%E0%B8%B2%E0%B8%A3%E0%B8%95%E0%B9%88%E0%B8%AD%E0%B8%A7%E0%B8%87%E0%B8%88%E0%B8%A3-1536x716.png)
Special thanks to [ai-corporation.net](https://www.ai-corporation.net/2022/07/29/diy-project-hand-operated-automatic-plant-watering-through-the-blynk-application/) for Diagram.

### Code Explanation
- The `BlynkSimpleEsp8266.h` library is used to establish connection between the ESP8266 microcontroller and the Blynk app.
- The `sendSoil()` function is used to display the soil moisture level and percentage on the Blynk app and LCD screen.
- The `BLYNK_WRITE()` function is used to turn the irrigation system on and off based on the state of the button widget on the Blynk app.

### Usage
1. Connect the components as per the circuit diagram.
2. Upload the code to the ESP8266 microcontroller.
3. Open the Blynk app and connect it to the Wi-Fi network.
4. Run the project in the Blynk app and monitor the soil moisture level.
5. Use the button widget to turn the irrigation system on and off.

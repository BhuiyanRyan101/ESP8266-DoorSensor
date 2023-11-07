# DoorSensor Project for ESP8266

My house was wired with contact sensors in each door leading up into an ADT control panel. We don't pay for ADT anymore and the alarm panel was broken. The only logical thing to do was make my contact sensors smart and compatiable with Home Assistant running a MQTT Broker.

The board detects if each circut was closed or open by checking the voltage using digitalRead() against the ground pin and published updates to Home Assistant at n second intervals. 

## What You Need

  * [ESP-8266 Mini D1 Module](https://www.amazon.com/HiLetgo-NodeMcu-Development-ESP8266-Compatiable/dp/B073CQVFLK/ref=pd_ci_mcx_mh_ci_mcx_mr_mp_m_2?pd_rd_w=NTVPC&content-id=amzn1.sym.8d9df0b1-324b-4c0a-a13b-e10a9334cd53&pf_rd_p=8d9df0b1-324b-4c0a-a13b-e10a9334cd53&pf_rd_r=YMNG38GMCB9V3RBHQ6KT&pd_rd_wg=1HGmc&pd_rd_r=6dacbb32-8993-40e1-890e-78ef3c021bc5&pd_rd_i=B073CQVFLK)
  * Contact Sensors (Wired)
  * A [MQTT Broker](https://mosquitto.org/) (I used [Mosquitto running on Hassio](https://www.home-assistant.io/integrations/mqtt/))


## Coding The Board

Included in this respository was a file named [DoorSensor.ino](https://github.com/BhuiyanRyan101/ESP8266-DoorSensor/blob/main/DoorSensor.ino) that contained the code that I use for my board. 

      #include <ESP8266WiFi.h>
      #include <PubSubClient.h>

In lines 6-7, I include the ESP8266 wifi library for wifi and the PubSubClient Library for MQTT messaging.

      #define wifi_ssid "SSID"
      #define wifi_password "WifiPass"
      #define mqtt_server "x.x.x.x"
      #define mqtt_user "MqttUser"
      #define mqtt_password "MqttPass"
      
Then in lines 9-13, I define my wifi info along with my MQTT information.

      #define front_topic "doorsensor/front"
      #define garage_topic "doorsensor/garage"
      #define back_topic "doorsensor/back"
      
Lines 15-17 define each topic for the board to publish to. You can alter these to fit your needs.

      #define frontDoor 14 //D5
      #define garageDoor 12 //D6
      #define backDoor 13 //D7
      
This tells the board what [pins](https://escapequotes.net/wp-content/uploads/2016/02/esp8266-wemos-d1-mini-pinout.png) each door sensor is connected to. Again, alter these to your needs.

//documentation
//https://pubsubclient.knolleary.net/api
//https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/readme.html
//https://www.home-assistant.io/blog/2015/10/11/measure-temperature-with-esp8266-and-report-to-mqtt/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define wifi_ssid "SSID"
#define wifi_password "WifiPass"
#define mqtt_server "x.x.x.x"
#define mqtt_user "MqttUser"
#define mqtt_password "MqttPass"

#define front_topic "doorsensor/front"
#define garage_topic "doorsensor/garage"
#define back_topic "doorsensor/back"

#define frontDoor 14 //D5
#define garageDoor 12 //D6
#define backDoor 13 //D7

int fval = 0;
bool frontDoorOpen = false;
String front = "Closed";
char frontarray[6];

int gval = 0;
bool garageDoorOpen = false;
String garage = "Closed";
char garagearray[6];

int bval = 0;
bool backDoorOpen = false;
String back = "Closed";
char backarray[6];

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
    pinMode(frontDoor, INPUT_PULLUP);
    pinMode(garageDoor, INPUT_PULLUP);
    pinMode(backDoor, INPUT_PULLUP);
  
  setup_wifi();
  client.setServer(mqtt_server, 1883);

}

void setup_wifi(){
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(wifi_ssid);

  WiFi.begin(wifi_ssid, wifi_password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP()); 
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    // If you do not want to use a username and password, change next line to
    // if (client.connect("ESP8266Client")) {
    if (client.connect("ESP8266Client", mqtt_user, mqtt_password)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}



void loop() {
  if (!client.connected()) {
    reconnect();
  }

    fval = (digitalRead(frontDoor));
    gval = (digitalRead(garageDoor));
    bval = (digitalRead(backDoor));
      if (fval == 0) {
    frontDoorOpen = false;
    front = "Closed";
    
  } else {
    frontDoorOpen = true;
    front = "Open";
  }

        if (gval == 0) {
    garageDoorOpen = false;
    garage = "Closed";
    
  } else {
    garageDoorOpen = true;
    garage = "Open";
  }

        if (bval == 0) {
    backDoorOpen = false;
    back = "Closed";
    
  } else {
    backDoorOpen = true;
    back = "Open";
  }

front.toCharArray(frontarray, front.length() + 1);
garage.toCharArray(garagearray, garage.length() + 1);
back.toCharArray(backarray, back.length() + 1);


  client.loop();
  client.publish(front_topic, frontarray, true);
  client.publish(garage_topic, garagearray, true);
  client.publish(back_topic, backarray, true);
  delay(1000);
  }

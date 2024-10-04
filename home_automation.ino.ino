// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
//
// This Code is Written By Saikat Chowdhury as Robomanthan's Assignment
//
// LED Behaviour: Rapid Blink - Not Connected to WiFi
//                Static On - In Config Mode
//                Slow Blink - Connected to WiFi
//
// Instruction: Press The Button Connected to D1 and Power Up to Get Into 
//              Configuration Mode
//
// Note: By Default The MCU Will Boot Into Station Mode and Try to Connect to
//       Latest Configured SSID
//
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------



// Includde Liabraries ----------------------------------------------------------
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>
#include <WiFi.h>
#include <PubSubClient.h>

ESP8266WebServer server(80);

// MQTT broker details
const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;
const char* mqtt_user = ""; // Not required for public brokers
const char* mqtt_password = ""; // Not required for public brokers
const char* mqtt_topic = "esp32/relay";

WiFiClient espClient;
PubSubClient client(espClient);

// Variablws --------------------------------------------------------------------
String content;
int statusCode;
unsigned long i=0;
bool setupMode = false;
bool state=true;

//I/O Pins ----------------------------------------------------------------------
#define funSW D1

// Relay pins
const int relayPin1 = 26;
const int relayPin2 = 27;
const int relayPin3 = 14;
const int relayPin4 = 12;

//Function Decalration-----------------------------------------------------------
void setupAP(void);
void launchWeb(void);


void setup()
{
  // I/O Setup ------------------------------------------------------------------
  pinMode(funSW, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  // Initialize relay pins
  pinMode(relayPin1, OUTPUT);
  pinMode(relayPin2, OUTPUT);
  pinMode(relayPin3, OUTPUT);
  pinMode(relayPin4, OUTPUT);
  digitalWrite(relayPin1, LOW);
  digitalWrite(relayPin2, LOW);
  digitalWrite(relayPin3, LOW);
  digitalWrite(relayPin4, LOW);

  // Initializations ------------------------------------------------------------
  Serial.begin(115200);
  delay(2000);
  Serial.println("Starting...");
  
  WiFi.disconnect();
  EEPROM.begin(512);
  
  // Check for function button press ---------------------------------------------
  if (digitalRead(funSW)==LOW)
  {
    Serial.println("Setting Up Access Point...");
    launchWeb();
    setupAP();
    
    // Handle Clinent of AP Server & Static On LED, If MCU is in Config Mode -----------
    digitalWrite(LED_BUILTIN, LOW);
    while ((WiFi.status() != WL_CONNECTED))
    {
      Serial.print(".");
      delay(100);
      server.handleClient();
    }

  }

  // If button is not pressed -----------------------------------------------------
  else {
    delay(10);
    //Reading SSID & Password from EEPROM -----------------------------------------
    String esid;
    for (int i = 0; i < 32; ++i)
      esid += char(EEPROM.read(i));
  
    String epass="";
    for (int i = 32; i < 64; ++i)
      epass += char(EEPROM.read(i));

    //Trying to connect to AP ------------------------------------------------------
    WiFi.begin(esid.c_str(), epass.c_str());
    delay(1000);

    // If WiFi Not Connected Blink LED Rapidly -------------------------------------
    while (WiFi.status() != WL_CONNECTED) {
      delay(200);
      Serial.print(".");
      digitalWrite(LED_BUILTIN, !state);
      state=!state;
    }
  }
  
  Serial.print("Connected!");
  delay(3000);
  
  // Set MQTT server and callback
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void callback(char topic, byte payload, unsigned int length) {
  String message = "";
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  Serial.println(message);

  if (String(topic) == mqtt_topic) {
    if (message == "relay1_on") {
      digitalWrite(relayPin1, HIGH);
    } else if (message == "relay1_off") {
      digitalWrite(relayPin1, LOW);
    } else if (message == "relay2_on") {
      digitalWrite(relayPin2, HIGH);
    } else if (message == "relay2_off") {
      digitalWrite(relayPin2, LOW);
    } else if (message == "relay3_on") {
      digitalWrite(relayPin3, HIGH);
    } else if (message == "relay3_off") {
      digitalWrite(relayPin3, LOW);
    } else if (message == "relay4_on") {
      digitalWrite(relayPin4, HIGH);
    } else if (message == "relay4_off") {
      digitalWrite(relayPin4, LOW);
    }
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP32Client", mqtt_user, mqtt_password)) {
      Serial.println("connected");
      client.subscribe(mqtt_topic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}


void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  digitalWrite(LED_BUILTIN, state);
  Serial.println(i++);
  state=!state;
  delay(1000);  
}

// Launch The Webserver ---------------------------------------------------------------
void launchWeb()
{
  Serial.println("");
  if (WiFi.status() == WL_CONNECTED)
    Serial.println("WiFi connected");
  Serial.print("Local IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("SoftAP IP: ");
  Serial.println(WiFi.softAPIP());
  createWebServer();
  // Start the server
  server.begin();
  Serial.println("Server started");
}

// Create Access Point With Specified SSID, Pass ---------------------------------------
void setupAP(void)
{
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  delay(100);
  WiFi.softAP("C.Saikat Creations | IoT", "");
  launchWeb();
  Serial.println("over");
}


// Create Webserver --------------------------------------------------------------------
void createWebServer()
{
 {     
   server.on("/setting", []() {
      String qsid = server.arg("ssid");
      String qpass = server.arg("pass");
      if (qsid.length() > 0 && qpass.length() > 0) {
        Serial.println("clearing eeprom");
        for (int i = 0; i < 96; ++i) {
          EEPROM.write(i, 0);
        }
        Serial.println(qsid);
        Serial.println("");
        Serial.println(qpass);
        Serial.println("");
        Serial.println("writing eeprom ssid:");
        for (int i = 0; i < qsid.length(); ++i)
        {
          EEPROM.write(i, qsid[i]);
          Serial.print("Wrote: ");
          Serial.println(qsid[i]);
        }
        Serial.println("writing eeprom pass:");
        for (int i = 0; i < qpass.length(); ++i)
        {
          EEPROM.write(32 + i, qpass[i]);
          Serial.print("Wrote: ");
          Serial.println(qpass[i]);
        }
        EEPROM.commit();
        content = "Done";
        statusCode = 200;
      } else {
        content = "Not Found";
        statusCode = 404;
        Serial.println("Sending 404");
      }
      server.sendHeader("Access-Control-Allow-Origin", "*");
      server.send(statusCode, "text/plain", content);
      Serial.println("Going to Reboot...");
      delay(5000);
      ESP.reset();
    });
  } 
}
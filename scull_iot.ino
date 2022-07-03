#include <WebServer.h>
#include <ArduinoJson.h>

WebServer server(80);

const char* ssid = "ssid";
const char* password = "password";

// Assign output variables to GPIO pins
const int eye_left = 33;
const int eye_right = 32;

StaticJsonDocument<250> jsonDocument;
char buffer[250];

void setup() {
  setup_yeys();
  setup_serial();
  setup_wifi();
  setup_routing();
}

void loop() {
  server.handleClient();
}

void setup_yeys() {
  // Initialize the output variables as outputs
  pinMode(eye_left, OUTPUT);
  pinMode(eye_right, OUTPUT);
  // Set outputs to LOW
  digitalWrite(eye_left, LOW);
  digitalWrite(eye_right, LOW);
}

void setup_serial() {
  Serial.begin(115200);
}

void setup_wifi() {
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup_routing() {
  server.on("/eye", HTTP_GET, get_eye);
  server.on("/eye", HTTP_POST, set_eye);
  server.begin();
}

void get_eye() {
  Serial.println("Get eyes status");
  jsonDocument.clear();
  
  if (digitalRead(eye_left) == HIGH) {
    jsonDocument["left"] = "on";
  } else {
    jsonDocument["left"] = "off";
  }

  if (digitalRead(eye_right) == HIGH) {
    jsonDocument["right"] = "on";
  } else {
    jsonDocument["right"] = "off";
  }

  serializeJson(jsonDocument, buffer);
  server.send(200, "application/json", buffer);
}

void set_eye() {
  Serial.println("Set eyes status");
  String body = server.arg("plain");
  deserializeJson(jsonDocument, body);

  String eye_left_status = jsonDocument["left"];
  String eye_right_status = jsonDocument["right"];

  if (eye_left_status == "on") {
    digitalWrite(eye_left, HIGH);
  }

  if (eye_right_status == "on") {
    digitalWrite(eye_right, HIGH);
  }
  
  if (eye_left_status == "off") {
    digitalWrite(eye_left, LOW);
  }

  if (eye_right_status == "off") {
    digitalWrite(eye_right, LOW);
  }
  
  get_eye();
}

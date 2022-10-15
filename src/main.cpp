#include <Arduino.h>
#include <wifi.h>
#include <logger.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <controller.h>
#include <commander.h>

#define SERVER_PORT 80

Logger logger;
WIFI wifi(&logger);
ESP8266WebServer httpServer(SERVER_PORT);
ESP8266HTTPUpdateServer ota;
Commander commander;
Controller controller(&httpServer, &logger, &wifi, &commander);

void setup() {
  wifi.begin();
  
  // Router
  httpServer.on("/ping", HTTP_GET, [](){controller.ping();});
  httpServer.on("/prepare", HTTP_POST, [](){controller.prepare();});
  httpServer.on("/config/wifi", HTTP_PUT, [](){controller.setWiFi();});

  httpServer.begin();

  ota.setup(&httpServer, "/fwu");
}

void loop() {
  httpServer.handleClient();
}
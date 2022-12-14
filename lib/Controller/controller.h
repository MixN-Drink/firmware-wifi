#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <ESP8266WebServer.h>
#include <logger.h>
#include <ArduinoJson.h>
#include <command.h>
#include <EEPROM.h>
#include <wifi.h>
#include <commander.h>

#define HTTP_STATUS_OK 200

class Controller {
    public:
        Controller(ESP8266WebServer *_httpServer, Logger *_logger, WIFI *_wifi, Commander *_commander);
        void ping(void);
        void setWiFi(void);
        void prepare(void);
    private:
        ESP8266WebServer *httpServer;
        Logger *logger;
        WIFI *wifi;
        Commander *commander;
};

#endif
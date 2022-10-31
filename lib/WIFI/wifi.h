#ifndef WIFI_H
#define WIFI_H

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <logger.h>
#include <EEPROM.h>

#define DEVICE_NAME "MixNDrink"
#define WIFI_RETRY_DELAY 100
#define MAX_RETRIES 1
#define AP_SSID "MixNDrink"
#define AP_PASS "mixndrink"
#define AP_IP 192,168,0,100

#define SSID_LENGTH 32
#define PASSWORD_LENGTH 32
#define SSID_ADDRESS_OFFSET 0
#define PASSWORD_ADDRESS_OFFSET SSID_ADDRESS_OFFSET+SSID_LENGTH

class WIFI {
    public:
        WIFI(Logger *_logger);
        void begin(void);
        void setSSID(const char *_ssid);
        void setPassword(const char *_password);
        const char* getSSID();
        const char* getPassword();
        void storeCredentials();
        void loadCredentials();
    private:
        Logger *logger;
        char ssid[SSID_LENGTH];
        char password[PASSWORD_LENGTH];
        IPAddress localIP;
        IPAddress gateway;
        IPAddress subnet;
};

#endif
#include <controller.h>

Controller::Controller(ESP8266WebServer *_httpServer, Logger *_logger, WIFI *_wifi, Commander *_commander){
    httpServer = _httpServer;
    logger = _logger;
    wifi = _wifi;
    commander = _commander;
}

void Controller::ping(void){
    httpServer->send(200, F("text/plain"), F("pong"));
}
void Controller::setWiFi(void){
    String body = httpServer->arg("plain");

    StaticJsonDocument<200> json;
    DeserializationError error = deserializeJson(json, body);
    if(error){
        httpServer->send(500, F("text/plain"), F("deserializeJson failed"));
        return;
    }

    const char *ssid = json["ssid"];
    const char *password = json["password"];
    
    wifi->setSSID(ssid);
    wifi->setPassword(password);
    wifi->storeCredentials();

    httpServer->send(200, F("text/plain"), F("WiFi credentials saved"));
}
void Controller::prepare(void){
    logger->Writeln(F("Handling: Prepare"));
    String body = httpServer->arg("plain");

    StaticJsonDocument<256> json;
    DeserializationError error = deserializeJson(json, body);
    if(error){
        logger->Write(F("deserializeJson failed: "));
        logger->Writeln(error.c_str());
        httpServer->send(500, F("text/plain"), F("deserializeJson failed"));
        return;
    }

    JsonArray slots = json["slots"];

    for(uint8_t i=0; i<4; i++){
        uint8_t slot = slots[i]["slot"].as<uint8_t>();
        uint8_t percentage = slots[i]["percentage"].as<uint8_t>();
        if(percentage == 0) continue;

        logger->Write("Slot: ");
        logger->Write(slot);
        logger->Write(" ");
        logger->Write(percentage);
        logger->Writeln("%");

        commander->Send(COMMAND_PUMP, slot, percentage);
    }

    httpServer->send(200, F("text/plain"), F("Preparing"));
}
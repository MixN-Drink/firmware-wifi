#include <controller.h>

Controller::Controller(ESP8266WebServer *_httpServer, Logger *_logger, WIFI *_wifi){
    httpServer = _httpServer;
    logger = _logger;
    wifi = _wifi;
}

void Controller::ping(void){
    logger->Writeln(F("Handling: Ping"));
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

    StaticJsonDocument<200> json;
    DeserializationError error = deserializeJson(json, body);
    if(error){
        httpServer->send(500, F("text/plain"), F("deserializeJson failed"));
        return;
    }

    JsonArray slots = json["slots"];

    logger->Write("Slots: ");
    logger->Write(slots[0].as<int>());
    logger->Write(F(","));
    logger->Write(slots[1].as<int>());
    logger->Write(F(","));
    logger->Write(slots[2].as<int>());
    logger->Write(F(","));
    logger->Writeln(slots[3].as<int>());

    JsonArray orders = json["order"];
    logger->Write("Order: ");
    logger->Write(orders[0].as<int>());
    logger->Write(F(","));
    logger->Write(orders[1].as<int>());
    logger->Write(F(","));
    logger->Write(orders[2].as<int>());
    logger->Write(F(","));
    logger->Writeln(orders[3].as<int>());

    uint8_t status = 0x80; // Comando surtir bomba 0
    uint8_t data = slots[0].as<int>() & 0x7F;

    Serial1.write(status);
    Serial1.write(data);

    status = 0xB0; // Comando surtir bomba 3
    data = slots[3].as<int>() & 0x7F;

    Serial1.write(status);
    Serial1.write(data);

    httpServer->send(200, F("text/plain"), F("Preparing"));
}
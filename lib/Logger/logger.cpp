#include "logger.h"

Logger::Logger(){
    Serial.begin(LOGGER_BAUDRATE);
}

void Logger::Write(char *msg){
    Serial.print(msg);
}
void Logger::Write(const char *msg){
    Serial.print(msg);
}
void Logger::Write(const __FlashStringHelper *msg){
    Serial.print(msg);
}
void Logger::Write(int msg){
    Serial.print(msg);
}
void Logger::Write(String msg){
    Serial.print(msg);
}
void Logger::Writeln(char *msg){
    Serial.println(msg);
}
void Logger::Writeln(const char *msg){
    Serial.println(msg);
}
void Logger::Writeln(const __FlashStringHelper *msg){
    Serial.println(msg);
}
void Logger::Writeln(int msg){
    Serial.println(msg);
}
void Logger::Writeln(String msg){
    Serial.println(msg);
}

static Logger logger;
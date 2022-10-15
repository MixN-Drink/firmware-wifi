#ifndef COMMANDER_H
#define COMMANDER_H

#include <stdint.h>
#include <Arduino.h>
#include <SoftwareSerial.h>

#define COMMAND_MASK 0b00001111
#define SUBCOMMAND_MASK 0b01110000
#define SUBCOMMAND_SHIFT 4
#define DATA_MASK 0b01111111

#define SERIAL_TX_PIN   12
#define SERIAL_RX_PIN   14
#define SERIAL_BAUDRATE 9600

class Commander {
    public:
        Commander();
        void Send(uint8_t command, uint8_t subcommand, uint8_t data);
    private:
        SoftwareSerial *serial;
};

#endif
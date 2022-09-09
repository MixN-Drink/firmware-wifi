#ifndef COMMANDER_H
#define COMMANDER_H

#include <stdint.h>
#include <Arduino.h>

#define COMMAND_MASK 0b00001111
#define SUBCOMMAND_MASK 0b01110000
#define SUBCOMMAND_SHIFT 4
#define DATA_MASK 0b01111111

class Commander {
    public:
        Commander();
        void Send(uint8_t command, uint8_t subcommand, uint8_t data);
};

#endif
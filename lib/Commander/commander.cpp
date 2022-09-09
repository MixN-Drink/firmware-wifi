#include <commander.h>

Commander::Commander(){
}

void Commander::Send(uint8_t command, uint8_t subcommand, uint8_t data){
    // Crea el byte de status base
    uint8_t status = 0b10000000;

    // Obtengo el comando
    command = command & COMMAND_MASK; // Filtra los 4 bits menos significativos. Ej: 0b00001111

    // Obtengo el subcomando
    subcommand = subcommand & SUBCOMMAND_MASK; // Filtra solo 3 bits menos significativos. Ej: 0b00000111

    subcommand = subcommand << SUBCOMMAND_SHIFT; // Mueve los 3 bits hacia la izq 4 posiciones. Ej: 0b01110000

    // Agrego el comando y el subcomando al status
    status = status | command | subcommand; // Suma los bits de cada variable de manera independiente.
    // Ej:
    // status     = 0b10000000
    // command    = 0b00001111
    // subcommand = 0b01110000
    // resultado  = 0b11111111

    // Pongo el bit de tipo en 0 por las dudas
    data = data & DATA_MASK; // Filtra los 7 bits menos significativos. Ej: 0b01111111

    // Envio los dos bytes
    Serial.write(status);
    Serial.write(data);
}

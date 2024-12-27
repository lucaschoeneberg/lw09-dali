/*
 * Arduino Sample for LED-Warrior 09
 */
#include <Arduino.h>
#include <Wire.h>
#include <LW09-Dali.h>

// device constants
#define I2C_ADDRESS 0x20

LW09Dali ledWarrior(I2C_ADDRESS);
#define SDA_PIN 13
#define SCL_PIN 16

void setup()
{
    Serial.begin(9600);
    Wire.begin(SDA_PIN, SCL_PIN);
}


void loop()
{
    if (Serial.available() > 0)
    {
        String input = Serial.readStringUntil('\n');
        input.trim();

        if (input.startsWith("CMD"))
        {
            // Command input format: CMD <address> <value>
            int firstSpace = input.indexOf(' ');
            int secondSpace = input.indexOf(' ', firstSpace + 1);

            if (firstSpace > 0 && secondSpace > 0)
            {
                String addressStr = input.substring(firstSpace + 1, secondSpace);
                String valueStr = input.substring(secondSpace + 1);

                uint8_t address = (uint8_t)strtol(addressStr.c_str(), NULL, 16);
                uint8_t value = (uint8_t)strtol(valueStr.c_str(), NULL, 16);

                ledWarrior.sendCommand(address, value);
                Serial.println("Command sent.");
            }
            else
            {
                Serial.println("Invalid CMD format. Use: CMD <address> <value>");
            }
        }
        else if (input.startsWith("SET"))
        {
            // Set lamp level format: SET <address> <level>
            int firstSpace = input.indexOf(' ');
            int secondSpace = input.indexOf(' ', firstSpace + 1);

            if (firstSpace > 0 && secondSpace > 0)
            {
                String addressStr = input.substring(firstSpace + 1, secondSpace);
                String levelStr = input.substring(secondSpace + 1);

                uint8_t address = (uint8_t)strtol(addressStr.c_str(), NULL, 16);
                uint8_t level = (uint8_t)strtol(levelStr.c_str(), NULL, 10);

                ledWarrior.setLampLevel(address, level);
                Serial.println("Lamp level set.");
            }
            else
            {
                Serial.println("Invalid SET format. Use: SET <address> <level>");
            }
        }
        else if (input.startsWith("CONF"))
        {
            // Configure switch format: CONF <switchIndex> <mode> <address>
            int firstSpace = input.indexOf(' ');
            int secondSpace = input.indexOf(' ', firstSpace + 1);
            int thirdSpace = input.indexOf(' ', secondSpace + 1);

            if (firstSpace > 0 && secondSpace > 0 && thirdSpace > 0)
            {
                String switchIndexStr = input.substring(firstSpace + 1, secondSpace);
                String modeStr = input.substring(secondSpace + 1, thirdSpace);
                String addressStr = input.substring(thirdSpace + 1);

                uint8_t switchIndex = (uint8_t)strtol(switchIndexStr.c_str(), NULL, 10);
                uint8_t mode = (uint8_t)strtol(modeStr.c_str(), NULL, 10);
                uint8_t address = (uint8_t)strtol(addressStr.c_str(), NULL, 16);

                ledWarrior.configureSwitchInput(switchIndex, mode, address);
                Serial.println("Switch configured.");
            }
            else
            {
                Serial.println("Invalid CONF format. Use: CONF <switchIndex> <mode> <address>");
            }
        }
    }
}
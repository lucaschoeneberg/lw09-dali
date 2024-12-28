#include "LW09Dali.h"
#include <Wire.h>

LW09Dali::LW09Dali(const uint8_t i2cAddress) : _i2cAddress(i2cAddress) {}

void LW09Dali::sendCommand(const uint8_t address, const uint8_t value) const {
    Wire.beginTransmission(_i2cAddress);
    Wire.write(LW09DaliConstants::REG_COMMAND);
    Wire.write(address);
    Wire.write(value);
    Wire.endTransmission();
}

uint8_t LW09Dali::readStatus() const {
    Wire.beginTransmission(_i2cAddress);
    Wire.write(LW09DaliConstants::REG_STATUS);
    Wire.endTransmission();

    Wire.requestFrom(_i2cAddress, static_cast<uint8_t>(1));
    return Wire.read();
}

uint8_t LW09Dali::readData() const {
    Wire.beginTransmission(_i2cAddress);
    Wire.write(LW09DaliConstants::REG_COMMAND);
    Wire.endTransmission();

    Wire.requestFrom(_i2cAddress, static_cast<uint8_t>(1));
    return Wire.read();
}

uint8_t LW09Dali::readQuery(const uint8_t address, const uint8_t value) const {
    sendCommand(address, value);
    waitForReady();
    return readData();
}

void LW09Dali::setDALIAddress(const uint8_t groupBit, const uint8_t address, const uint8_t modeBit) const {
    if (address > 63 || groupBit > 1 || modeBit > 1) {
        return;
    }
    const uint8_t daliAddress = (address << 1) | groupBit | modeBit;
    sendCommand(daliAddress, 0);
}

void LW09Dali::waitForReady() const {
    while (true) {
        const uint8_t status = readStatus();
        if ((status & LW09DaliConstants::STATUS_BUSY) == 0) {
            break;
        }
    }
}

void LW09Dali::setLampLevel(const uint8_t address, const uint8_t level) const {
    if (level > 254) {
        return;
    }
    const uint8_t daliAddress = (address << 1) | 0x00;
    sendCommand(daliAddress, level);
    waitForReady();
}

void LW09Dali::configureSwitchInput(const uint8_t switchIndex, const uint8_t mode, const uint8_t address) const {
    if (switchIndex > 1 || mode > 6 || address > 127) {
        return;
    }

    Wire.beginTransmission(_i2cAddress);
    Wire.write(LW09DaliConstants::REG_CONFIG);

    if (switchIndex == 0) {
        Wire.write(mode);
        Wire.write(address);
    } else {
        Wire.write(0x00); // Mode SW0
        Wire.write(0x00); // Addr SW0
        Wire.write(mode);
        Wire.write(address);
    }

    Wire.endTransmission();
}

void LW09Dali::sendDALICommand(const DALICommand command, const uint8_t address) const {
    if (address > 63 && address != LW09DaliConstants::DALI_BROADCAST) {
        return;
    }
    const uint8_t daliAddress = (address << 1) | 0x01; // Command mode
    sendCommand(daliAddress, static_cast<uint8_t>(command));
    waitForReady();
}

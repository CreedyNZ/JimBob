// Copyright (C) Pololu Corporation.  See LICENSE.txt for details.

#include "Maestro.h"

Maestro::Maestro(uint8_t resetPin,
                 uint8_t deviceNumber,
                 bool CRCEnabled)
{
  _deviceNumber = deviceNumber;
  _resetPin = resetPin;
  _CRCEnabled = CRCEnabled;
}

void Maestro::reset()
{
  if (_resetPin != noResetPin)
  {
    digitalWrite(_resetPin, LOW);
    pinMode(_resetPin, OUTPUT); // Drive low.
    delay(1);
    pinMode(_resetPin, INPUT); // Return to high-impedance input (reset is
                               // internally pulled up on Maestro).
    delay(200); // Wait for Maestro to boot up after reset.
  }
}

void Maestro::goHome()
{
  writeCommand(goHomeCommand);
  writeCRC();
}

void Maestro::setTarget(uint8_t channelNumber, uint16_t target)
{
  writeCommand(setTargetCommand);
  write7BitData(channelNumber);
  write14BitData(target);
  writeCRC();
}

void Maestro::setSpeed(uint8_t channelNumber, uint16_t speed)
{
  writeCommand(setSpeedCommand);
  write7BitData(channelNumber);
  write14BitData(speed);
  writeCRC();
}

void Maestro::setAcceleration(uint8_t channelNumber, uint16_t acceleration)
{
  writeCommand(setAccelerationCommand);
  write7BitData(channelNumber);
  write14BitData(acceleration);
  writeCRC();
}



void Maestro::writeByte(uint8_t dataByte)
{
  _stream->write(dataByte);

  if(_CRCEnabled)
  {
    _CRCByte ^= dataByte;
    for (uint8_t j = 0; j < 8; j++)
    {
      if (_CRCByte & 1)
      {
        _CRCByte ^= CRC7Polynomial;
      }
      _CRCByte >>= 1;
    }
  }
}

void Maestro::writeCRC()
{
  if(_CRCEnabled)
  {
    _stream->write(_CRCByte);
    _CRCByte = 0; // Reset CRCByte to initial value.
  }
}

void Maestro::writeCommand(uint8_t commandByte)
{
  if (_deviceNumber != deviceNumberDefault)
  {
    writeByte(baudRateIndication);
    write7BitData(_deviceNumber);
    write7BitData(commandByte);
  }
  else
  {
    writeByte(commandByte);
  }
}

void Maestro::write7BitData(uint8_t data)
{
  writeByte(data & 0x7F);
}

void Maestro::write14BitData(uint16_t data)
{
  writeByte(data & 0x7F);
  writeByte((data >> 7) & 0x7F);
}



/*
 * ConfigurableFirmataBlink.ino generated by FirmataBuilder
 * Thu Jul 28 2016 09:35:49 GMT-0400 (EDT)
 */

#include <ConfigurableFirmata.h>

#include <DigitalOutputFirmata.h>
DigitalOutputFirmata digitalOutput;

#include <FirmataExt.h>
FirmataExt firmataExt;

#include <SoftModem.h>
SoftModem modem = SoftModem();

void systemResetCallback()
{
  for (byte i = 0; i < TOTAL_PINS; i++) {
    if (IS_PIN_ANALOG(i)) {
    } else if (IS_PIN_DIGITAL(i)) {
      Firmata.setPinMode(i, OUTPUT);
    }
  }
  firmataExt.reset();
}

void setup()
{
  //delay(100);
  modem.begin();
  delay(100);
  Firmata.setFirmwareVersion(FIRMWARE_MAJOR_VERSION, FIRMWARE_MINOR_VERSION);

  firmataExt.addFeature(digitalOutput);
  Firmata.attach(SYSTEM_RESET, systemResetCallback);

  Firmata.begin(modem);

  systemResetCallback();
}

void loop()
{
  while(Firmata.available()) {
    delay(10);
    Firmata.processInput();
  }

}
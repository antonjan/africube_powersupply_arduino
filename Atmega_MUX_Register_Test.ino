#include <Wire.h>
#include <EEPROM.h>

#define TCA_ADDR 0x70  // TCA9548APWR default address
#define MAX_ADDR 0x48  // Assumed address of MAX77986; verify with your datasheet

// Function to select a particular channel on the TCA9548A
void selectTCAChannel(uint8_t channel) {
  if (channel > 7) return; // Only channels 0-7 valid
  Wire.beginTransmission(TCA_ADDR);
  Wire.write(1 << channel); // This will enable only that channel
  Wire.endTransmission();
  delay(10); // Allow time for switching
}

void setup() {
  Wire.begin();

  // Clear EEPROM locations 0x20 and 0x21 for our test results
  EEPROM.write(0x20, 0xFF); // To store I2C contact result (error code)
  EEPROM.write(0x21, 0xFF); // To store the read register value

  // Select channel 6, where the MAX77986 is supposed to be connected.
  selectTCAChannel(6);

  // Try to contact the MAX77986 at address MAX_ADDR.
  // The error variable will be 0 if the device acknowledges.
  Wire.beginTransmission(MAX_ADDR);
  byte error = Wire.endTransmission();
  
  // Write the error code to EEPROM at address 0x20.
  EEPROM.write(0x20, error);

  // If device acknowledged (error == 0), attempt to read register 0x00.
  if (error == 0) {
    Wire.beginTransmission(MAX_ADDR);
    Wire.write(0x00); // Assumed register to read; adjust based on datasheet if needed.
    error = Wire.endTransmission(false); // Send a restart rather than a stop.
    
    if (error == 0) {
      Wire.requestFrom(MAX_ADDR, (uint8_t)1);
      if (Wire.available()) {
        byte regVal = Wire.read();
        EEPROM.write(0x21, regVal);
      }
    }
  }
}

void loop() {
  // Nothing to do here.
}

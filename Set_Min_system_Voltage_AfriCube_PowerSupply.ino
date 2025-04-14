#include <Wire.h>

#define MAX77986_ADDRESS_READ 0xD7  //I2C Address to read
#define MAX77986_ADDRESS_WRITE 0xD6  //I2C Address to write
#define CHG_CNFG_04 0x1A   // Address of the CHG_CNFG_04 register
#define MINSYS_MASK 0b01100000   // Bitmask for MINSYS bits in CHG_CNFG_04 register (bits 6:5)

void TCA9548A(uint8_t bus);
uint8_t readRegister(uint8_t regAddress);
void writeRegister(uint8_t regAddr, uint8_t value);
void setMinSysVoltage(uint8_t minsSysValue);

void setup() {

  // Initialize serial communication for debugging
  Serial.begin(9600);

  // Allow devices to initialize
  delay(100);

  // Initialize I2C communication
  Wire.begin();

  // Select bus 0 on the TCA9548A multiplexer
  TCA9548A(0);

  // Set the minimum system voltage (e.g., 3.6V corresponds to 0b10 for MAX77986A)
  setMinSysVoltage(0b10);  // Set MINSYS to 3.6V
  /*0b00: 3.4V 3.0V
    0b01: 3.5V 3.1V
    0b10: 3.6V 3.5V
    0b11: 3.7V 3.6V */
}

void loop() {
  // put your main code here, to run repeatedly:

}

void TCA9548A(uint8_t bus){

  Wire.beginTransmission(0x70);  // TCA9548A address
  Wire.write(1 << bus);          // send byte to select bus
  Wire.endTransmission();
  Serial.print(bus);
}

//Function to read register value via I2C 
uint8_t readRegister(uint8_t regAddress) {
  Wire.beginTransmission(MAX77986_ADDRESS_READ);
  Wire.write(regAddress);
  Wire.endTransmission(false); // Send a repeated start

  Wire.requestFrom(MAX77986_ADDRESS_READ, 1); // Request 1 byte from the register
  if (Wire.available()) {
    return Wire.read();
  } else {
    Serial.println("Error: Failed to read register.");
    return 0xFF; // Return an invalid value in case of error
  }
}

//Function to write register value via I2C 
void writeRegister(uint8_t regAddr, uint8_t value) {
  Wire.beginTransmission(MAX77986_ADDRESS_WRITE);
  Wire.write(regAddr);
  Wire.write(value);
  Wire.endTransmission();

  Serial.print("Written 0x");
  Serial.print(value, HEX);
  Serial.print(" to register 0x");
  Serial.println(regAddr, HEX);
}

// Function to set the minimum system voltage for MAX77986AEFD+
void setMinSysVoltage(uint8_t minsSysValue) {
  // Ensure the value is within the valid range (0b00 to 0b11)
  if (minsSysValue > 0b11) {
    Serial.println("Invalid MINSYS value! Must be 0b00 to 0b11.");
    return;
  }

  // Read the current value of CHG_CNFG_04 register
  uint8_t regValue = readRegister(CHG_CNFG_04);

  // Clear the existing MINSYS bits (6:5) and set the new value
  regValue &= ~MINSYS_MASK;         // Clear bits 6:5
  regValue |= (minsSysValue << 5);  // Set new MINSYS value

  // Write the updated value back to the register
  writeRegister(CHG_CNFG_04, regValue);

  // Debug print
  Serial.print("MINSYS set to value: ");
  Serial.println(minsSysValue, BIN);
}

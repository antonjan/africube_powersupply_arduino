#include <Wire.h>

#define MAX77986_ADDRESS_READ 0xD7  //I2C Address to read
#define MAX77986_ADDRESS_WRITE 0xD6  //I2C Address to write
#define CHG_CNFG_05 0x1B   // Address of the CHG_CNFG_05 register
#define B2SOVRC_MASK 0b00001111   // Bitmask for B2SOVRC bits in CHG_CNFG_05 register (bits 3:0)

void TCA9548A(uint8_t bus);
uint8_t readRegister(uint8_t regAddress);
void writeRegister(uint8_t regAddr, uint8_t value);
void setB2SOvercurrentThreshold(uint8_t threshold);

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);

  // Allow devices to initialize
  delay(100);

  // Initialize I2C communication
  Wire.begin();

  // Select bus 0 on the TCA9548A multiplexer
  TCA9548A(0);

  // Set the Battery to System Overcurrent Threshold (e.g., 6.0A corresponds to 0x7)
  setB2SOvercurrentThreshold(0x7);  // Set B2SOVRC to 6.0A

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

// Function to set the Battery to System Overcurrent Threshold (B2SOVRC)
void setB2SOvercurrentThreshold(uint8_t threshold) {
  // Ensure the value is within the valid range (0x0 to 0xF)
  if (threshold > 0xF) {
    Serial.println("Invalid B2SOVRC value! Must be between 0x0 and 0xF.");
    return;
  }

  // Read the current value of CHG_CNFG_05 register
  uint8_t regValue = readRegister(CHG_CNFG_05);

  // Clear the existing B2SOVRC bits (3:0) and set the new value
  regValue &= ~B2SOVRC_MASK;       // Clear bits 3:0
  regValue |= (threshold & B2SOVRC_MASK);  // Set new B2SOVRC value

  // Write the updated value back to the register
  writeRegister(CHG_CNFG_05, regValue);

  // Debug print
  Serial.print("B2SOVRC set to value: ");
  Serial.println(threshold, HEX);
}

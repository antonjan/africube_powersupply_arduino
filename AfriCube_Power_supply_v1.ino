


#include <Wire.h>

#define MAX77986_ADDRESS 0x6B  //I2C Address

#define CHG_INT 0x10  // Address of the CHG_INT register (Interrupts)

#define CHG_INT_MASK 0x11  // Address of the CHG_INT_MASK register (Mask Interrupts)

#define CHG_INT_OK 0x12   // Address of the CHG_INT_OK register (Status Indicator)

#define CHG_DETAILS_00 0x13   // Address of the CHG_DETAILS_00 register

#define CHG_DETAILS_01 0x14   // Address of the CHG_DETAILS_01 register

#define CHG_DETAILS_02 0x15   // Address of the CHG_DETAILS_02 register

#define CHG_CNFG_00 0x16   // Address of the CHG_CNFG_00 register
#define SS_ENV_MASK 0b11000000   // Bitmask for SS_ENV bits in CHG_CNFG_00 register (bits 7:6)
#define SS_PAT_MASK 0b00100000   // Bitmask for SS_PAT bits in CHG_CNFG_00 register (bit 5)
#define BATRMV_MSK_MASK 0b00010000 // Bitmask for BATRMV_MSK bits in CHG_CNFG_00 register (bit 4)
#define MODE_MASK 0b00001111  // Bitmask for MODE bits in CHG_CNFG_00 register (bits 3:0)

#define CHG_CNFG_01 0x17   // Address of the CHG_CNFG_01 register
#define TKEN_MASK 0b10000000
#define WDTEN_MASK 0b01000000
#define CHG_RSTRT_MASK 0b00110000
#define FCHGTIME_MASK 0b00000111

#define CHG_CNFG_02 0x18   // Address of the CHG_CNFG_02 register
#define CHG_CC_MASK 0b01111111

#define CHG_CNFG_03 0x19   // Address of the CHG_CNFG_03 register

#define CHG_CNFG_04 0x1A   // Address of the CHG_CNFG_04 register
#define SYS_TRACK_DIS_MASK 0b10000000
#define MINSYS_MASK 0b01100000   // Bitmask for MINSYS bits in CHG_CNFG_04 register (bits 6:5)
#define CHG_CV_PRM_MASK 0b00011111

#define CHG_CNFG_05 0x1B   // Address of the CHG_CNFG_05 register
#define B2SOVRC_DTC_MASK 0b10000000
#define B2SOVRC_ALARM_ONLY_MASK 0b01000000
#define B2SOVRC_CTRL_MASK 0b00100000
#define RECYCLE_EN_MASK 0b00010000
#define B2SOVRC_MASK 0b00001111   // Bitmask for B2SOVRC bits in CHG_CNFG_05 register (bits 3:0)

#define CHG_CNFG_06 0x1C   // Address of the CHG_CNFG_06 register

#define CHG_CNFG_07 0x1D   // Address of the CHG_CNFG_07 register

#define CHG_CNFG_08 0x1E   // Address of the CHG_CNFG_08 register
#define AUDIO_MODE_MASK 0b10000000
#define BCKSYS_MASK 0b01110000
#define FMBST_MASK 0b00001000
#define SLOWLX_MASK 0b00000100
#define FSW_MASK 0b00000010
#define DISKIP_MASK 0b00000001

#define CHG_CNFG_09 0x1F   // Address of the CHG_CNFG_09 register

#define CHG_CNFG_10 0x20   // Address of the CHG_CNFG_10 register

#define CHG_CNFG_11 0x21   // Address of the CHG_CNFG_11 register

#define CHG_CNFG_12 0x22   // Address of the CHG_CNFG_12 register

#define CHG_CNFG_13 0x23   // Address of the CHG_CNFG_13 register

#define STAT_CNFG 0x24    // Address of the STAT_CNFG register

/*void TCA9548A(uint8_t bus);
  uint8_t readRegister(uint8_t regAddress);
  void writeRegister(uint8_t regAddr, uint8_t value);

  void setMaskRegister(
     uint8_t aicl_mask,
     uint8_t chgin_mask,
     uint8_t inlim_mask,
     uint8_t chg_mask,
     uint8_t bat_mask,
     uint8_t spr_2_mask,
     uint8_t disqbat_mask,
     uint8_t byp_mask
   );
  
  CHG_CNFG_00
    void setSpreadSpectrum(uint8_t ssEnvValue);
    void setSpreadSpectrumPattern(uint8_t ssPatValue);
    void setBatteryRemovalMask(bool mask);
    void setMode(uint8_t mode);
  CHG_CNFG_01
    void setTrickleCharge(bool enable);
    void setWatchdogTimer(bool enable);
    void setChargerRestartThreshold(uint8_t threshold);
    void setFastChargeTimer(uint8_t time);
  CHG_CNFG_02
    void setFastChargeCurrent(uint8_t currentCode);
    
  CHG_CNFG_04
    void setSysTrackingDisable(uint8_t disable);
    void setMinSysVoltage(uint8_t minsSysValue);
    void setChargeTerminationVoltage(uint8_t voltageCode)
  CHG_CNFG_05
    void setB2SOVRC_Debounce(uint8_t debounceTime);
    void setB2SOVRC_AlarmOnly(uint8_t alarmOnly);
    void setB2SOVRC_MonitoringControl(uint8_t mode);
    void setRecycleEnable(uint8_t enable);
    void setB2SOvercurrentThreshold(uint8_t threshold);
    
  CHG_CNFG_08
    void setAudioMode(uint8_t enable);
    void setBCKSYS(uint8_t value);
    void setFactoryModeBoost(uint8_t enable);
    void setLXSlopeControl(uint8_t slopeControl);
    void setSwitchingFrequency(uint8_t frequency);
    void setChargerSkipMode(uint8_t disable);
  CHG_CNFG_09
    void setCHGINInputCurrentLimit(uint8_t value);
    
  CHG_CNFG_11
    void setVBYPTargetVoltage(uint8_t value);
    
  CHG_CNFG_13
    void setJeitaEnable(uint8_t enable);
    void setChgCvCool(uint8_t enable);
    void setChgCcWarm(uint8_t enable);
    void setRegTemp(uint8_t temp);
  
  */


// the setup function runs once when you press reset or power the board
void setup() {

  pinMode(0, INPUT);  //Serial input device from USB
  pinMode(1, OUTPUT); //Serial output device to USB

// Initialize serial communication for debugging
  Serial.begin(9600);

  // Allow devices to initialize
  delay(100);

  // Initialize I2C communication
  Wire.begin();



   // Configure PC4 (SDA) and PC5 (SCL) as inputs with pull-ups enabled
  pinMode(A4, INPUT_PULLUP); // SDA (PC4)
  pinMode(A5, INPUT_PULLUP); // SCL (PC5)

  // Select bus 0 on the TCA9548A multiplexer
  TCA9548A(0);
  // Read CHG_DETAILS_00 to 02 and store values in chgDetails 00 to 02
  uint8_t chgDetails00 = readRegister(CHG_DETAILS_00);
  uint8_t chgDetails01 = readRegister(CHG_DETAILS_01);
  uint8_t chgDetails02 = readRegister(CHG_DETAILS_02);
  //Print values for each CHG_DETAILS register
  Serial.print("Registers:");
  Serial.print("\tCHG_DETAILS_00:");
  Serial.println(chgDetails00, HEX);
  Serial.print("\tCHG_DETAILS_01:");
  Serial.println(chgDetails01, HEX);
  Serial.print("\tCHG_DETAILS_02:");
  Serial.println(chgDetails02, HEX);


}

// the loop function runs over and over again forever
void loop() {
  
}


// Select I2C BUS
void TCA9548A(uint8_t bus){
  Wire.beginTransmission(0x70);  // TCA9548A address
  Wire.write(1 << bus);          // send byte to select bus
  Wire.endTransmission();
  Serial.print(bus);
}

//Function to read register value via I2C 
uint8_t readRegister(uint8_t regAddress) {
  Wire.beginTransmission(MAX77986_ADDRESS);
  Wire.write(regAddress);
  Wire.endTransmission(false); // Send a repeated start

  Wire.requestFrom(MAX77986_ADDRESS, 1); // Request 1 byte from the register
  if (Wire.available()) {
    return Wire.read();
  } else {
    Serial.println("Error: Failed to read register.");
    return 0xFF; // Return an invalid value in case of error
  }
}

//Function to write register value via I2C 
void writeRegister(uint8_t regAddr, uint8_t value) {
  Wire.beginTransmission(MAX77986_ADDRESS);
  Wire.write(regAddr);
  Wire.write(value);
  Wire.endTransmission();

  Serial.print("Written 0x");
  Serial.print(value, HEX);
  Serial.print(" to register 0x");
  Serial.println(regAddr, HEX);
}


/**
 * Function to set the mask register for charger interrupts.
 * @param aicl_mask: Mask for AICL Interrupt (0b0: Unmasked, 0b1: Masked)
 * @param chgin_mask: Mask for CHGIN Interrupt (0b0: Unmasked, 0b1: Masked)
 * @param inlim_mask: Mask for Input Current Limit Interrupt (0b0: Unmasked, 0b1: Masked)
 * @param chg_mask: Mask for Charger Interrupt (0b0: Unmasked, 0b1: Masked)
 * @param bat_mask: Mask for Battery Interrupt (0b0: Unmasked, 0b1: Masked)
 * @param spr_2_mask: Mask for SPR_2 (Reserved, keep default)
 * @param disqbat_mask: Mask for DISQBAT Interrupt (0b0: Unmasked, 0b1: Masked)
 * @param byp_mask: Mask for Bypass Interrupt (0b0: Unmasked, 0b1: Masked)
 */
void setMaskRegister(
    uint8_t aicl_mask,
    uint8_t chgin_mask,
    uint8_t inlim_mask,
    uint8_t chg_mask,
    uint8_t bat_mask,
    uint8_t spr_2_mask,
    uint8_t disqbat_mask,
    uint8_t byp_mask
) {
    // Construct the mask register value
    uint8_t mask_value = (aicl_mask << 7) |
                         (chgin_mask << 6) |
                         (inlim_mask << 5) |
                         (chg_mask << 4) |
                         (bat_mask << 3) |
                         (spr_2_mask << 2) |
                         (disqbat_mask << 1) |
                         (byp_mask << 0);

    // Write the mask value to the mask register
    writeRegister(CHG_INT_MASK, mask_value);
}



// Function to set Spread Spectrum Control (SS_ENV) bits
void setSpreadSpectrum(uint8_t ssEnvValue) {
  if (ssEnvValue > 0b11) {
    Serial.println("Error: Invalid SS_ENV value. Must be between 0b00 and 0b11.");
    return;
  }

  // Read the current value of the CHG_CNFG_00 register
  uint8_t regValue = readRegister(CHG_CNFG_00);

  // Clear the existing SS_ENV bits (7:6) and set the new value
  regValue &= ~SS_ENV_MASK;  // Clear SS_ENV bits
  regValue |= (ssEnvValue << 6);  // Set new SS_ENV value

  // Write the updated value back to the register
  writeRegister(CHG_CNFG_00, regValue);

  // Debug print
  Serial.print("SS_ENV set to value: ");
  Serial.println(ssEnvValue, BIN);
}

// Function to set Spread Spectrum Pattern (SS_PAT) bit
void setSpreadSpectrumPattern(uint8_t ssPatValue) {
  if (ssPatValue > 0b1) {
    Serial.println("Error: Invalid SS_PAT value. Must be either 0b0 (pseudo-random) or 0b1 (linear).");
    return;
  }

  // Read the current value of the CHG_CNFG_00 register
  uint8_t regValue = readRegister(CHG_CNFG_00);

  // Clear the existing SS_PAT bit (5) and set the new value
  regValue &= ~SS_PAT_MASK;  // Clear SS_PAT bit
  regValue |= (ssPatValue << 5);  // Set new SS_PAT value

  // Write the updated value back to the register
  writeRegister(CHG_CNFG_00, regValue);

  // Debug print
  Serial.print("SS_PAT set to value: ");
  Serial.println(ssPatValue, BIN);
}

// Function to set Battery Removal Mask (BATRMV_MSK) bit
void setBatteryRemovalMask(bool mask) {
  // Read the current value of the CHG_CNFG_00 register
  uint8_t regValue = readRegister(CHG_CNFG_00);

  // Clear the existing BATRMV_MSK bit (4) and set the new value
  regValue &= ~BATRMV_MSK_MASK;  // Clear BATRMV_MSK bit
  regValue |= (mask << 4);   // Set new BATRMV_MSK value

  // Write the updated value back to the register
  writeRegister(CHG_CNFG_00, regValue);

  // Debug print
  Serial.print("BATRMV_MSK set to: ");
  Serial.println(mask ? "Masked" : "Unmasked");
}


void setMode(uint8_t mode) {
  if (mode > 0xF) {
    Serial.println("Error: Invalid MODE value. MODE must be between 0x0 and 0xF.");
    return;
  }

  // Read the current value of the CHG_CNFG_00 register
  uint8_t chgConfig00 = readRegister(CHG_CNFG_00);

  /// Clear the MODE bits (3:0) and set the new mode using the mask
  chgConfig00 &= ~MODE_MASK;       // Clear bits 3:0
  chgConfig00 |= (mode & MODE_MASK);  // Set new MODE value

  // Write the updated value back to the register
  writeRegister(CHG_CNFG_00, chgConfig00);

  Serial.print("MODE set to 0x");
  Serial.println(mode, HEX);
}

// Function to enable or disable Trickle Charge (TKEN)
void setTrickleCharge(bool enable) {
  // Read the current value of the CHG_CNFG_01 register
  uint8_t regValue = readRegister(CHG_CNFG_01);

  // Clear the existing TKEN bit (7) and set the new value
  regValue &= ~TKEN_MASK;  // Clear TKEN bit
  regValue |= (enable << 7); // Set new TKEN value

  // Write the updated value back to the register
  writeRegister(CHG_CNFG_01, regValue);

  // Debug print
  Serial.print("TKEN set to: ");
  Serial.println(enable ? "Enabled" : "Disabled");
}

// Function to enable or disable Watchdog Timer (WDTEN)
void setWatchdogTimer(bool enable) {
  // Read the current value of the CHG_CNFG_01 register
  uint8_t regValue = readRegister(CHG_CNFG_01);

  // Clear the existing WDTEN bit (6) and set the new value
  regValue &= ~WDTEN_MASK;  // Clear WDTEN bit
  regValue |= (enable << 6); // Set new WDTEN value

  // Write the updated value back to the register
  writeRegister(CHG_CNFG_01, regValue);

  // Debug print
  Serial.print("WDTEN set to: ");
  Serial.println(enable ? "Enabled" : "Disabled");
}

// Function to set Charger Restart Threshold (CHG_RSTRT)
void setChargerRestartThreshold(uint8_t threshold) {
  if (threshold > 0b11) {
    Serial.println("Error: Invalid CHG_RSTRT value. Must be between 0b00 and 0b11.");
    return;
  }

  // Read the current value of the CHG_CNFG_01 register
  uint8_t regValue = readRegister(CHG_CNFG_01);

  // Clear the existing CHG_RSTRT bits (5:4) and set the new value
  regValue &= ~CHG_RSTRT_MASK;  // Clear CHG_RSTRT bits
  regValue |= (threshold << 4); // Set new CHG_RSTRT value

  // Write the updated value back to the register
  writeRegister(CHG_CNFG_01, regValue);

  // Debug print
  Serial.print("CHG_RSTRT set to: ");
  Serial.println(threshold, BIN);
}

// Function to set Fast-Charge Timer (FCHGTIME)
void setFastChargeTimer(uint8_t time) {
  if (time > 0b111) {
    Serial.println("Error: Invalid FCHGTIME value. Must be between 0b000 and 0b111.");
    return;
  }

  // Read the current value of the CHG_CNFG_01 register
  uint8_t regValue = readRegister(CHG_CNFG_01);

  // Clear the existing FCHGTIME bits (2:0) and set the new value
  regValue &= ~FCHGTIME_MASK;  // Clear FCHGTIME bits
  regValue |= (time & 0b111); // Set new FCHGTIME value

  // Write the updated value back to the register
  writeRegister(CHG_CNFG_01, regValue);

  // Debug print
  Serial.print("FCHGTIME set to: ");
  Serial.println(time, BIN);
}

// Function to set Fast-Charge Current (CHG_CC)
void setFastChargeCurrent(uint8_t currentCode) {
  if (currentCode > 0x6E) {
    Serial.println("Error: Invalid current code. Must be between 0x00 and 0x6E.");
    return;
  }

  // Read the current value of the CHG_CNFG_02 register
  uint8_t regValue = readRegister(CHG_CNFG_02);

  // Clear the existing CHG_CC bits (6:0) and set the new value
  regValue &= ~CHG_CC_MASK;  // Clear CHG_CC bits
  regValue |= (currentCode & 0x7F); // Set new CHG_CC value

  // Write the updated value back to the register
  writeRegister(CHG_CNFG_02, regValue);

  // Debug print
  Serial.print("CHG_CC set to: ");
  Serial.print(currentCode, HEX);
  Serial.print(" (");
  Serial.print(currentCode * 50);  // Convert code to current in mA
  Serial.println("mA)");
}





// Function to set SYS_TRACK_DIS (Buck SYS Tracking Disable Control)
void setSysTrackingDisable(uint8_t disable) {
  if (disable > 1) {
    Serial.println("Error: Invalid disable value. Must be 0 or 1.");
    return;
  }

  // Read the current value of the CHG_CNFG_04 register
  uint8_t regValue = readRegister(CHG_CNFG_04);

  // Clear the SYS_TRACK_DIS bit and set the new value
  regValue &= ~SYS_TRACK_DIS_MASK;  // Clear SYS_TRACK_DIS bit
  regValue |= (disable << 7); // Set the SYS_TRACK_DIS value

  // Write the updated value back to the register
  writeRegister(CHG_CNFG_04, regValue);

  // Debug print
  if (disable == 0) {
    Serial.println("SYS tracking enabled.");
  } else {
    Serial.println("SYS tracking disabled.");
  }
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

// Function to set CHG_CV_PRM (Charge Termination Voltage)
void setChargeTerminationVoltage(uint8_t voltageCode) {
  if (voltageCode > 0x1F) {
    Serial.println("Error: Invalid voltage code. Must be between 0x00 and 0x1F.");
    return;
  }

  // Read the current value of the CHG_CNFG_04 register
  uint8_t regValue = readRegister(CHG_CNFG_04);

  // Clear the CHG_CV_PRM bits (4:0) and set the new value
  regValue &= ~CHG_CV_PRM_MASK;  // Clear CHG_CV_PRM bits
  regValue |= (voltageCode & 0x1F); // Set new CHG_CV_PRM value

  // Write the updated value back to the register
  writeRegister(CHG_CNFG_04, regValue);

  // Debug print
  Serial.print("CHG_CV_PRM set to: ");
  float terminationVoltage = 4.1500 + (voltageCode * 0.0125);  // Example for MAX77985A
  Serial.println(terminationVoltage, 4);  // Print the voltage with 4 decimal places
}

// Function to set B2SOVRC_DTC (BATT to SYS Overcurrent Debounce to QBATT Clear Control)
void setB2SOVRC_Debounce(uint8_t debounceTime) {
  if (debounceTime > 1) {
    Serial.println("Error: Invalid debounce time. Must be 0 or 1.");
    return;
  }

  // Read the current value of the CHG_CNFG_05 register
  uint8_t regValue = readRegister(CHG_CNFG_05);

  // Clear the B2SOVRC_DTC bit and set the new value
  regValue &= ~B2SOVRC_DTC_MASK;  // Clear B2SOVRC_DTC bit
  regValue |= (debounceTime << 7); // Set new B2SOVRC_DTC value

  // Write the updated value back to the register
  writeRegister(CHG_CNFG_05, regValue);

  // Debug print
  if (debounceTime == 0) {
    Serial.println("B2SOVRC debounce set to 105µs.");
  } else {
    Serial.println("B2SOVRC debounce set to 10ms.");
  }
}

// Function to set B2SOVRC_ALARM_ONLY (B2SOVRC Alarm Only Control)
void setB2SOVRC_AlarmOnly(uint8_t alarmOnly) {
  if (alarmOnly > 1) {
    Serial.println("Error: Invalid alarm control value. Must be 0 or 1.");
    return;
  }

  // Read the current value of the CHG_CNFG_05 register
  uint8_t regValue = readRegister(CHG_CNFG_05);

  // Clear the B2SOVRC_ALARM_ONLY bit and set the new value
  regValue &= ~B2SOVRC_ALARM_ONLY_MASK;  // Clear B2SOVRC_ALARM_ONLY bit
  regValue |= (alarmOnly << 6); // Set new B2SOVRC_ALARM_ONLY value

  // Write the updated value back to the register
  writeRegister(CHG_CNFG_05, regValue);

  // Debug print
  if (alarmOnly == 0) {
    Serial.println("B2SOVRC Alarm Only is disabled.");
  } else {
    Serial.println("B2SOVRC Alarm Only is enabled.");
  }
}

// Function to set B2SOVRC_CTRL (Battery Mode B2SOVRC Monitoring Control)
void setB2SOVRC_MonitoringControl(uint8_t mode) {
  if (mode > 1) {
    Serial.println("Error: Invalid monitoring mode. Must be 0 (Automatic) or 1 (Continuous).");
    return;
  }

  // Read the current value of the CHG_CNFG_05 register
  uint8_t regValue = readRegister(CHG_CNFG_05);

  // Clear the B2SOVRC_CTRL bit and set the new value
  regValue &= ~B2SOVRC_CTRL_MASK;  // Clear B2SOVRC_CTRL bit
  regValue |= (mode << 5); // Set new B2SOVRC_CTRL value

  // Write the updated value back to the register
  writeRegister(CHG_CNFG_05, regValue);

  // Debug print
  if (mode == 0) {
    Serial.println("B2SOVRC monitoring set to Automatic mode.");
  } else {
    Serial.println("B2SOVRC monitoring set to Continuous mode.");
  }
}

// Function to set RECYCLE_EN (B2S OCP or DISIBS Event Recycle Option)
void setRecycleEnable(uint8_t enable) {
  if (enable > 1) {
    Serial.println("Error: Invalid recycle enable value. Must be 0 or 1.");
    return;
  }

  // Read the current value of the CHG_CNFG_05 register
  uint8_t regValue = readRegister(CHG_CNFG_05);

  // Clear the RECYCLE_EN bit and set the new value
  regValue &= ~RECYCLE_EN_MASK;  // Clear RECYCLE_EN bit
  regValue |= (enable << 4); // Set new RECYCLE_EN value

  // Write the updated value back to the register
  writeRegister(CHG_CNFG_05, regValue);

  // Debug print
  if (enable == 0) {
    Serial.println("Recycle option disabled.");
  } else {
    Serial.println("Recycle option enabled.");
  }
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

// Function to enable or disable Audio Mode
void setAudioMode(uint8_t enable) {
  if (enable > 1) {
    Serial.println("Error: Invalid audio mode value. Must be 0 (disabled) or 1 (enabled).");
    return;
  }

  // Read the current value of the CHG_CNFG_08 register
  uint8_t regValue = readRegister(CHG_CNFG_08);

  // Clear the AUDIO_MODE bit and set the new value
  regValue &= ~AUDIO_MODE_MASK;  // Clear AUDIO_MODE bit
  regValue |= (enable << 7); // Set new AUDIO_MODE value

  // Write the updated value back to the register
  writeRegister(CHG_CNFG_08, regValue);

  // Debug print
  if (enable == 0) {
    Serial.println("Audio mode disabled.");
  } else {
    Serial.println("Audio mode enabled.");
  }
}

// Function to set BCKSYS (System voltage setting)
void setBCKSYS(uint8_t value) {
  if (value > 7) {
    Serial.println("Error: Invalid BCKSYS setting. Must be between 0 and 7.");
    return;
  }

  // Read the current value of the CHG_CNFG_08 register
  uint8_t regValue = readRegister(CHG_CNFG_08);

  // Clear the BCKSYS[2:0] bits and set the new value
  regValue &= ~BCKSYS_MASK;  // Clear BCKSYS bits
  regValue |= (value << 4); // Set new BCKSYS value

  // Write the updated value back to the register
  writeRegister(CHG_CNFG_08, regValue);

  // Debug print
  Serial.print("BCKSYS set to: ");
  Serial.println(value, HEX);
}

// Function to enable or disable Factory Mode Boost
void setFactoryModeBoost(uint8_t enable) {
  if (enable > 1) {
    Serial.println("Error: Invalid factory mode boost value. Must be 0 (disabled) or 1 (enabled).");
    return;
  }

  // Read the current value of the CHG_CNFG_08 register
  uint8_t regValue = readRegister(CHG_CNFG_08);

  // Clear the FMBST bit and set the new value
  regValue &= ~FMBST_MASK;  // Clear FMBST bit
  regValue |= (enable << 3); // Set new FMBST value

  // Write the updated value back to the register
  writeRegister(CHG_CNFG_08, regValue);

  // Debug print
  if (enable == 0) {
    Serial.println("Factory mode boost disabled.");
  } else {
    Serial.println("Factory mode boost enabled.");
  }
}

// Function to set LX slope control
void setLXSlopeControl(uint8_t slopeControl) {
  if (slopeControl > 1) {
    Serial.println("Error: Invalid LX slope control value. Must be 0 (fast) or 1 (slow).");
    return;
  }

  // Read the current value of the CHG_CNFG_08 register
  uint8_t regValue = readRegister(CHG_CNFG_08);

  // Clear the SLOWLX bit and set the new value
  regValue &= ~SLOWLX_MASK;  // Clear SLOWLX bit
  regValue |= (slopeControl << 2); // Set new SLOWLX value

  // Write the updated value back to the register
  writeRegister(CHG_CNFG_08, regValue);

  // Debug print
  if (slopeControl == 0) {
    Serial.println("Fastest LX slope selected.");
  } else {
    Serial.println("Slowest LX slope selected.");
  }
}

// Function to set Switching Frequency
void setSwitchingFrequency(uint8_t frequency) {
  if (frequency > 1) {
    Serial.println("Error: Invalid switching frequency value. Must be 0 (2.6 MHz) or 1 (1.3 MHz).");
    return;
  }

  // Read the current value of the CHG_CNFG_08 register
  uint8_t regValue = readRegister(CHG_CNFG_08);

  // Clear the FSW bit and set the new value
  regValue &= ~FSW_MASK;  // Clear FSW bit
  regValue |= (frequency << 1); // Set new FSW value

  // Write the updated value back to the register
  writeRegister(CHG_CNFG_08, regValue);

  // Debug print
  if (frequency == 0) {
    Serial.println("Switching frequency set to 2.6 MHz.");
  } else {
    Serial.println("Switching frequency set to 1.3 MHz.");
  }
}

// Function to enable or disable Charger Skip Mode
void setChargerSkipMode(uint8_t disable) {
  if (disable > 1) {
    Serial.println("Error: Invalid skip mode value. Must be 0 (enabled) or 1 (disabled).");
    return;
  }

  // Read the current value of the CHG_CNFG_08 register
  uint8_t regValue = readRegister(CHG_CNFG_08);

  // Clear the DISKIP bit and set the new value
  regValue &= ~DISKIP_MASK;  // Clear DISKIP bit
  regValue |= (disable); // Set new DISKIP value

  // Write the updated value back to the register
  writeRegister(CHG_CNFG_08, regValue);

  // Debug print
  if (disable == 0) {
    Serial.println("Auto skip mode enabled.");
  } else {
    Serial.println("Skip mode disabled.");
  }
}

// Function to set the CHGIN input current limit
void setCHGINInputCurrentLimit(uint8_t value) {
  if (value > 0x6D) {
    Serial.println("Error: Invalid current limit value. Must be between 0x00 and 0x6D.");
    return;
  }

  // Read the current value of the CHG_CNFG_09 register
  uint8_t regValue = readRegister(CHG_CNFG_09);

  // Clear the CHGIN_ILIM[6:0] bits and set the new value
  regValue &= ~0x7F;  // Clear CHGIN_ILIM bits
  regValue |= value;  // Set new CHGIN_ILIM value

  // Write the updated value back to the register
  writeRegister(CHG_CNFG_09, regValue);

  // Debug print
  Serial.print("CHGIN input current limit set to: ");
  Serial.print(value * 50); // Convert to mA
  Serial.println("mA");
}

// Function to set the VBYP target output voltage
void setVBYPTargetVoltage(uint8_t value) {
  if (value > 0x7A) {
    Serial.println("Error: Invalid voltage setting. Must be between 0x00 (5.0V) and 0x7A (12.0V).");
    return;
  }

  // Read the current value of the CHG_CNFG_11 register
  uint8_t regValue = readRegister(CHG_CNFG_11);

  // Clear the VBYPSET[6:0] bits and set the new value
  regValue &= ~0x7F;  // Clear VBYPSET bits
  regValue |= value;  // Set new VBYPSET value

  // Write the updated value back to the register
  writeRegister(CHG_CNFG_11, regValue);

  // Debug print
  float voltage = 5.0 + (value * 0.1);  // Calculate voltage based on 100mV step
  Serial.print("VBYP target output voltage set to: ");
  Serial.print(voltage, 1); // Print with one decimal place
  Serial.println("V");
}

// Function to enable or disable JEITA
void setJeitaEnable(uint8_t enable) {
  // Read current CHG_CNFG_13 register value
  uint8_t regValue = readRegister(CHG_CNFG_13);

  // Clear JEITA_EN bit (bit 7)
  regValue &= ~0x80;

  // Set JEITA_EN based on input (0 = disable, 1 = enable)
  regValue |= (enable << 7);

  // Write the updated value back to the register
  writeRegister(CHG_CNFG_13, regValue);

  // Debug print
  Serial.print("JEITA enabled: ");
  Serial.println(enable ? "Yes" : "No");
}

// Function to set battery termination voltage based on JEITA temperature range
void setChgCvCool(uint8_t enable) {
  // Read current CHG_CNFG_13 register value
  uint8_t regValue = readRegister(CHG_CNFG_13);

  // Clear CHG_CV_COOL bit (bit 5)
  regValue &= ~0x20;

  // Set CHG_CV_COOL based on input (0 = use CHG_CV_PRM, 1 = use JEITA adjusted voltage)
  regValue |= (enable << 5);

  // Write the updated value back to the register
  writeRegister(CHG_CNFG_13, regValue);

  // Debug print
  Serial.print("Battery termination voltage adjusted by JEITA: ");
  Serial.println(enable ? "Yes" : "No");
}

// Function to set the battery fast-charge current based on JEITA temperature range
void setChgCcWarm(uint8_t enable) {
  // Read current CHG_CNFG_13 register value
  uint8_t regValue = readRegister(CHG_CNFG_13);

  // Clear CHG_CC_WARM bit (bit 4)
  regValue &= ~0x10;

  // Set CHG_CC_WARM based on input (0 = use CHG_CC, 1 = set to 50% of CHG_CC)
  regValue |= (enable << 4);

  // Write the updated value back to the register
  writeRegister(CHG_CNFG_13, regValue);

  // Debug print
  Serial.print("Battery fast-charge current adjusted by JEITA: ");
  Serial.println(enable ? "Yes" : "No");
}

// Function to set the thermal regulation temperature
void setRegTemp(uint8_t temp) {
  if (temp > 0x9) {
    Serial.println("Error: Invalid temperature setting. Must be between 0x0 (85°C) and 0x9 (130°C).");
    return;
  }

  // Read current CHG_CNFG_13 register value
  uint8_t regValue = readRegister(CHG_CNFG_13);

  // Clear REGTEMP[3:0] bits
  regValue &= ~0x0F;

  // Set REGTEMP[3:0] based on input
  regValue |= (temp & 0x0F);

  // Write the updated value back to the register
  writeRegister(CHG_CNFG_13, regValue);

  // Debug print
  Serial.print("Junction Temperature Thermal Regulation set to: ");
  Serial.print(85 + (temp * 5));  // Calculate temperature in Celsius
  Serial.println("°C");
}

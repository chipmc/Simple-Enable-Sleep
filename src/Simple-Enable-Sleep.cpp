/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/chipmc/Documents/Maker/Particle/Utilities/Simple-Enable-Sleep/src/Simple-Enable-Sleep.ino"
/*
* Project Simple-Enable-Sleep Modes
* Description: Tests the 3rd Generation Device (with and without Carrier) Enable sleep with the RTC
* Author: Charles McClelland
* Date: Started 5-17-2019 
* 
* Implements the following:
* Reports Battery State of Charge
* Goes into 10 seconds of Enable sleep
* Repeats
* 
* v0.10 - Initial Release
*/

#include "MCP79410RK.h"                             // Real Time Clock

void setup();
void loop();
#line 17 "/Users/chipmc/Documents/Maker/Particle/Utilities/Simple-Enable-Sleep/src/Simple-Enable-Sleep.ino"
Serial1DebugOutput debugOutput(57600);          // default is 9600 and log everything
MCP79410 rtc;                                       // Rickkas MCP79410 libarary

// Program Variables                      
char batteryString[64] = "Null";
int wakeInSeconds = 30;
unsigned long stayAwakeTime = 60 * 1000;
int blueLED = D7;

// setup() runs once, when the device is first turned on.
void setup() { 

  rtc.setup();                                                        // Start the real time clock
  rtc.clearAlarm();                                                   // Ensures alarm is still not set from last cycle

  pinMode(blueLED,OUTPUT);
  digitalWrite(blueLED,HIGH);

/*
  System.setPowerConfiguration(SystemPowerConfiguration());  // To restore the default configuration

  takeMeasurement();                                              // Test the battery state of charge
  Particle.publish("State",batteryString,PRIVATE);
    SystemPowerConfiguration conf;
    conf.powerSourceMaxCurrent(550) // Set maximum current the power source can provide (applies only when powered through VIN)
        .powerSourceMinVoltage(5080) // Set minimum voltage the power source can provide (applies only when powered through VIN)
        .batteryChargeCurrent(512) // Set battery charge current
        .batteryChargeVoltage(4210) // Set battery termination voltage
        .feature(SystemPowerFeature::USE_VIN_SETTINGS_WITH_USB_HOST); // For the cases where the device is powered through VIN
                                                                     // but the USB cable is connected to a USB host, this feature flag
                                                                     // enforces the voltage/current limits specified in the configuration
                                                                     // (where by default the device would be thinking that it's powered by the USB Host)
  System.setPowerConfiguration(conf); // returns SYSTEM_ERROR_NONE (0) in case of success
*/
  delay(2000);
  digitalWrite(blueLED,LOW);
}

void loop() {
    PMIC power(true);
    Log.trace("Current PMIC settings:");
    Log.trace("VIN Vmin: %u", power.getInputVoltageLimit());
    Log.trace("VIN Imax: %u", power.getInputCurrentLimit());
    Log.trace("Ichg: %u", power.getChargeCurrentValue());
    Log.trace("Iterm: %u", power.getChargeVoltageValue());
    Log.trace("Iterm: %u", power.getFault());
    Log.trace("Iterm: %u", power.getSystemStatus());
    Log.trace("Iterm: %u", power.readOpControlRegister());
    int powerSource = System.powerSource();
    int batteryState = System.batteryState();
    float batterySoc = System.batteryCharge();
    constexpr char const* batteryStates[] = {
        "unknown", "not charging", "charging",
        "charged", "discharging", "fault", "disconnected"
    };
    constexpr char const* powerSources[] = {
        "unknown", "vin", "usb host", "usb adapter",
        "usb otg", "battery"
    };
    Log.trace("Power source: %s", powerSources[std::max(0, powerSource)]);
    Log.trace("Battery state: %s", batteryStates[std::max(0, batteryState)]);
    Log.trace("Battery charge: %f", batterySoc);

    delay(2000);
/*
    if (millis() > stayAwakeTime) {                                   // Enable sleep so each time we wake we reset the device
      rtc.setAlarm(wakeInSeconds);
    }
*/
    rtc.loop();                                                         // keeps the clock up to date
  
}



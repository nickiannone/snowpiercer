
#include "sensors/gpsSensor.ino"
#include "sensors/temperatureHumiditySensor.ino"
#include "comms/transmitService.ino"

// TODO: Initialize with proper configs!
GPSSensor gpsSensor;
TemperatureHumiditySensor temperatureHumiditySensor;
TransmitService transmitService;
// TODO: Add camera!

void setup() {
  // Initialize serial communication at 9600 bits per second
  Serial.begin(9600);
  Serial.println("Starting...");

  // Set up our transmit service (provides DHCP, NTP time sync, and data transmission to server)
  transmitService.setup();

  // Set up our sensors
  gpsSensor.setup();
  temperatureHumiditySensor.setup();
  // TODO: Set up camera! (Before or after transmit service?)

  Serial.println("Setup complete");
}

void loop() {
  // Print a message to the serial monitor
  Serial.println("Sampling...");

  // Read the GPS, temperature, and humidity
  time_t sampleTime = now();
  GPSData* gpsData = gpsSensor.read();
  TemperatureHumidityData* temperatureHumidityData = temperatureHumiditySensor.read();

  // TODO: Do something with the camera?

  // Condense into a data frame
  DataFrame frame = DataFrame(sampleTime, temperatureHumidityData, gpsData);

  // Send it to the server
  Serial.println("Sending data to server...");
  if (transmitService.transmit(&frame)) {
    Serial.println("Data sent successfully");
  } else {
    Serial.println("Failed to send data");
    // TODO: Buffer the data and send it later!
  }

  // Wait for a second
  Serial.println("Waiting for a second...");
  delay(1000);
}

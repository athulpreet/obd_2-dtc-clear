#include <mcp_can.h>
#include <SPI.h>

// Set CS pin for MCP2515
const int SPI_CS_PIN = 9;

// Initialize MCP2515 using SPI
MCP_CAN CAN(SPI_CS_PIN);

void setup() {
  Serial.begin(115200);
  while (!Serial) {;} // Wait for serial port to open

  // Initialize MCP2515
  if (CAN.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK) {
    Serial.println("MCP2515 Initialized Successfully!");
  } else {
    Serial.println("Error Initializing MCP2515...");
    while (1);
  }

  // Clear all DTCs
  clearDTC();
}

void loop() {
  // Nothing to do here
}

void clearDTC() {
  // Define the message to send
  byte data[8] = {0x04, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  byte len = 8;
  byte ext = 0;
  byte rtr = 0;
  unsigned long canId = 0x7DF;

  // Send the message
  if (CAN.sendMsgBuf(canId, ext, len, data) != CAN_OK) {
    Serial.println("Error sending DTC clear message...");
  } else {
    Serial.println("DTCs cleared successfully!");
  }
}

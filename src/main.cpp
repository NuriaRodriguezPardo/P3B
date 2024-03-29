#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#define SERVICE_UUID        "6e400001-b5a3-f393-e0a9-e50e24dcca9e"
#define CHARACTERISTIC_UUID "6e400001-b5a3-f393-e0a9-e50e24dcca9e"

BLEServer *pServer;
BLECharacteristic *pCharacteristic;

class MyServerCallbacks : public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      Serial.println("Dispositivo conectado");
    };

    void onDisconnect(BLEServer* pServer) {
      Serial.println("Dispositivo desconectado");
    }
};

void setup() {
    Serial.begin(115200);
    BLEDevice::init("Nuria"); // Inicia el dispositivo BLE con un nombre
    pServer = BLEDevice::createServer();
    pServer->setCallbacks(new MyServerCallbacks());

    BLEService *pService = pServer->createService(SERVICE_UUID);
    pCharacteristic = pService->createCharacteristic(
                        CHARACTERISTIC_UUID,
                        BLECharacteristic::PROPERTY_READ |
                        BLECharacteristic::PROPERTY_WRITE
                    );

    //pCharacteristic->setValue("Hello World");
    pService->start();

    BLEAdvertising *pAdvertising = pServer->getAdvertising();
    pAdvertising->start();

    Serial.println("El dispositivo se ha iniciado, ¡ahora puedes emparejarlo con Bluetooth!");
}

void loop() {
    // No necesitas hacer nada en el bucle principal para el manejo de BLE
}

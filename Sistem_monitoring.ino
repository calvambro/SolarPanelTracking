        #include <HardwareSerial.h>
        HardwareSerial PZEMSerial(2); // Menggunakan serial 2 (pin 16 17)

        #include <WiFi.h>
        #include <HTTPClient.h>
        #include <ArduinoJson.h>
        #include <ModbusMaster.h>
        #include <time.h> 

        #define MAX485_DE 19
        #define MAX485_RE 18

        char ssid[] = "SmartRoomPrototype";
        char pass[] = "Binus123!";

        // Server NTP
        const char* ntpServer = "pool.ntp.org";
        const long  gmtOffset_sec = 7 * 3600;  
        const int   daylightOffset_sec = 0;   

        static uint8_t pzemSlaveAddr = 0x01; //slave address
        static uint16_t NewshuntAddr = 0x0001; //r shunt 100A

        ModbusMaster node;

        float PZEMVoltage = 0;
        float PZEMCurrent = 0;
        float PZEMPower = 0;
        float PZEMEnergy = 0;

        unsigned long startMillisPZEM;
        unsigned long currentMillisPZEM;
        const unsigned long periodPZEM = 1000;

        unsigned long startMillisReadData;
        unsigned long currentMillisReadData;
        const unsigned long periodReadData = 1000;

        int ResetEnergy = 0;
        int a = 1;
        unsigned long startMillis1;

void setup() {
    delay(5000);
    startMillis1 = millis();
    Serial.begin(9600);

    // Gunakan hardware serial UART2 di ESP32
    PZEMSerial.begin(9600, SERIAL_8N2, 16, 17);  // Rx = GPIO 16, Tx = GPIO 17
    
    WiFi.begin(ssid, pass);
    Serial.print("Connecting to ");
    Serial.println(ssid);

     while (WiFi.status() != WL_CONNECTED) {
       delay(500);
       Serial.print(".");
     }
    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    Serial.println("NTP setup completed.");
    
    startMillisPZEM = millis();
    pinMode(MAX485_RE, OUTPUT);
    pinMode(MAX485_DE, OUTPUT);
    digitalWrite(MAX485_RE, 0);
    digitalWrite(MAX485_DE, 0);
    
    node.preTransmission(preTransmission);
    node.postTransmission(postTransmission);
    node.begin(pzemSlaveAddr, PZEMSerial);

    delay(1000);
    
    startMillisReadData = millis();
}

void loop() 
{      
        if ((millis()- startMillis1 >= 10000) && (a ==1))
        {
          setShunt(pzemSlaveAddr);
          changeAddress(0XF8, pzemSlaveAddr);    
          a = 0;
        }

        currentMillisPZEM = millis(); 
        
        if (currentMillisPZEM - startMillisPZEM >= periodPZEM)    
        {    
          uint8_t result;  
          result = node.readInputRegisters(0x0000, 6);  
          if (result == node.ku8MBSuccess)  
          {
              uint32_t tempdouble = 0x00000000;    
              PZEMVoltage = node.getResponseBuffer(0x0000) / 100.0;      
              PZEMCurrent = node.getResponseBuffer(0x0001) / 100.0; 

              tempdouble =  (node.getResponseBuffer(0x0003) << 16) + node.getResponseBuffer(0x0002); 
              PZEMPower = tempdouble / 10.0;     

              tempdouble =  (node.getResponseBuffer(0x0005) << 16) + node.getResponseBuffer(0x0004);   
              PZEMEnergy = tempdouble;                                                                    
              
              startMillisPZEM = currentMillisPZEM ; 
          }
        }      
        /* Data submission to API  */
        
        currentMillisReadData = millis();        
        if (currentMillisReadData - startMillisReadData >= periodReadData)  
        {
            Serial.print("Vdc : "); Serial.print(PZEMVoltage); Serial.println(" V ");
            Serial.print("Idc : "); Serial.print(PZEMCurrent); Serial.println(" A ");
            Serial.print("Power : "); Serial.print(PZEMPower); Serial.println(" W ");
            Serial.print("Energy : "); Serial.print(PZEMEnergy); Serial.println(" Wh ");
            
            struct tm timeinfo;
            if (!getLocalTime(&timeinfo)) {
              Serial.println("Gagal mengambil waktu dari NTP");
              return;
            }

            // Format waktu menjadi string "dd/MM/yyyy HH:mm:ss"
            char datetime[25];
            strftime(datetime, sizeof(datetime), "%Y-%m-%d %H:%M:%S", &timeinfo);

            // Kirim data ke API
            unsigned long currentMillisReadData = millis();
            if (currentMillisReadData - startMillisReadData >= periodReadData) {
              HTTPClient http;
              http.begin("http://www.test.pantausolarpanel.com/api/data");
              http.addHeader("Content-Type", "application/json");
              http.addHeader("Authorization", "Bearer kunci_api");
              DynamicJsonDocument jsonDoc(2048);
              jsonDoc["datetime"] = datetime; // Ganti dengan waktu sekarang
              jsonDoc["volt"] = PZEMVoltage;
              jsonDoc["watt"] = PZEMPower;
              jsonDoc["ampere"] = PZEMCurrent;
              jsonDoc["wattHours"] = PZEMEnergy;
              Serial.println(jsonDoc.as<String>());
              int responseCode = http.POST(jsonDoc.as<String>());
              if (responseCode == 200) {
                Serial.println("Data terkirim!");
              } else {
                Serial.println("Gagal mengirim data!");
              }
              http.end();
              startMillisReadData = currentMillisReadData;
            }
          }
          
}

void preTransmission()    
{
        /* 1- PZEM-017 DC Energy Meter */
        if(millis() - startMillis1 > 5000) 
        {
          digitalWrite(MAX485_RE, 1); 
          digitalWrite(MAX485_DE, 1);
          delay(1);
        }
}

void postTransmission() 
{
        
        /* 1- PZEM-017 DC Energy Meter */
        if(millis() - startMillis1 > 5000) 
        {
          delay(3);     
          digitalWrite(MAX485_RE, 0);   
          digitalWrite(MAX485_DE, 0);
          }
}

void setShunt(uint8_t slaveAddr) 
{

        /* 1- PZEM-017 DC Energy Meter */
        
        static uint8_t SlaveParameter = 0x06;
        static uint16_t registerAddress = 0x0003; 

        uint16_t u16CRC = 0xFFFF;
        u16CRC = crc16_update(u16CRC, slaveAddr); 
        u16CRC = crc16_update(u16CRC, SlaveParameter);
        u16CRC = crc16_update(u16CRC, highByte(registerAddress));
        u16CRC = crc16_update(u16CRC, lowByte(registerAddress));
        u16CRC = crc16_update(u16CRC, highByte(NewshuntAddr));
        u16CRC = crc16_update(u16CRC, lowByte(NewshuntAddr));
      
        preTransmission(); 

        PZEMSerial.write(slaveAddr); 
        PZEMSerial.write(SlaveParameter);
        PZEMSerial.write(highByte(registerAddress));
        PZEMSerial.write(lowByte(registerAddress));
        PZEMSerial.write(highByte(NewshuntAddr));
        PZEMSerial.write(lowByte(NewshuntAddr));
        PZEMSerial.write(lowByte(u16CRC ));
        PZEMSerial.write(highByte(u16CRC));
        delay(10);
        postTransmission();  
        delay(100);
}

void changeAddress(uint8_t OldslaveAddr, uint8_t NewslaveAddr)
{

        /* 1- PZEM-017 DC Energy Meter */
    
        static uint8_t SlaveParameter = 0x06;
        static uint16_t registerAddress = 0x0002; 
        uint16_t u16CRC = 0xFFFF; 
        u16CRC = crc16_update(u16CRC, OldslaveAddr);
        u16CRC = crc16_update(u16CRC, SlaveParameter);
        u16CRC = crc16_update(u16CRC, highByte(registerAddress));
        u16CRC = crc16_update(u16CRC, lowByte(registerAddress));
        u16CRC = crc16_update(u16CRC, highByte(NewslaveAddr));
        u16CRC = crc16_update(u16CRC, lowByte(NewslaveAddr));
        preTransmission();   
        PZEMSerial.write(OldslaveAddr);   
        PZEMSerial.write(SlaveParameter);
        PZEMSerial.write(highByte(registerAddress));
        PZEMSerial.write(lowByte(registerAddress));
        PZEMSerial.write(highByte(NewslaveAddr));
        PZEMSerial.write(lowByte(NewslaveAddr));
        PZEMSerial.write(lowByte(u16CRC));
        PZEMSerial.write(highByte(u16CRC));
        delay(10);
        postTransmission();   
        delay(100);
}

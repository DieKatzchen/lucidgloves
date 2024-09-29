class SerialCommunication : public ICommunication {
  private:
    bool m_isOpen;

  public:
    SerialCommunication() {
      m_isOpen = false;
    }

    bool isOpen(){
      return m_isOpen;
    }

    void start(){
      //Serial.setTimeout(1000000);
      Serial.begin(SERIAL_BAUD_RATE);
      m_isOpen = true;
    }

    void output(const std::vector< uint8_t > &vec){
      Serial.print(vec);
      Serial.flush();
    }

    bool readData(const std::vector< uint8_t > *vec){
      byte size = Serial.readBytesUntil('\n', vec, 100);
      vec[size] = '\0';
      return input != NULL && sizeof(vec) > 0;
    }
};

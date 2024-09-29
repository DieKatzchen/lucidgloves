//Interface for communication

class ICommunication {

  public:
    virtual bool isOpen() = 0;

    virtual void start() = 0;

    virtual void output(const std::vector< uint8_t > &vec) = 0;

    virtual bool readData(const std::vector< uint8_t > *vec) = 0;
};

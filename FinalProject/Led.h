class Led
{
  public:
    Led(int pin);
    void setValue(uint32_t);
  private:
    int pin;
};
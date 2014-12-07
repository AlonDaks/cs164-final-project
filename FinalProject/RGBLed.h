class RGBLed
{
  public:
    RGBLed(int red_pin, int green_pin, int blue_pin);
    void setValue(Color c);
  private:
    int red_pin;
    int green_pin;
    int blue_pin;
};
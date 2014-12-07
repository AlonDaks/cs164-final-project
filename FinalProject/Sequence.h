class Sequence
{
  public:
    Sequence();
    void Sequence::add(uint16_t duration, Color c);
    struct Color;
  private:
    Keyframe[] frames;
    int num_frames;
    struct Keyframe;
};
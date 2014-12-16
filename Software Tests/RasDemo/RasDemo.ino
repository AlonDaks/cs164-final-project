#include <LedAnim.h>

///////////////////////////////////
// Setup Hardware:

const int upperDataPin = 22;  // anode
const int lowerDataPin = 23;  // red pin

SimpleLed upperLed = SimpleLed(upperDataPin);
SimpleLed lowerLed = SimpleLed(lowerDataPin);

Sequence seqUpper = Sequence();
SeqNode animUpper = SeqNode(upperLed, seqUpper, FOREVER); // Create anim

Sequence seqLower = Sequence();
SeqNode animUpper = SeqNode(upperLed, seqLower, FOREVER); // Create anim

AnimPlayer player = AnimPlayer();

void setup() {
seqUpper.append(seconds(.3), RED, 0)
   .append(seconds(.1), OFF, 0)
   .append(seconds(.4), RED, 0)
   .append(seconds(.2), OFF, 0)
   .append(seconds(1), RED, 0)
   .append(seconds(.1), OFF, 0)
   .append(seconds(.1), RED, 0)
   .append(seconds(.1), OFF, 0)
   .append(seconds(.1), RED, 0)
   .append(seconds(.1), OFF, 0);
   .append(seconds(.5), RED, 0);
   .append(seconds(.5), OFF, 0);
   
seqUpper.append(seconds(.3), OFF, 0)
   .append(seconds(.1), RED, 0)
   .append(seconds(.4), OFF, 0)
   .append(seconds(.2), RED, 0)
   .append(seconds(1), OFF, 0)
   .append(seconds(.1), RED, 0)
   .append(seconds(.1), OFF, 0)
   .append(seconds(.1), RED, 0)
   .append(seconds(.1), OFF, 0)
   .append(seconds(.1), RED, 0)
   .append(seconds(1), RED, 0);  
   
   uint16_t rec1 = player.play(animUpper);
   
}


void loop() {

}


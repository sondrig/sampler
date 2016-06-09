#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <signal.h>
#include "lib/RtMidi.h"
using namespace std;

bool done;
static void finish(int ignore) {
  done = true;
}

void listDevices(RtMidiIn *channel) {
  // Check inputs.
  cout << "Input channels:" << endl;
  unsigned int channelCount = channel->getPortCount();
  for ( unsigned int i = 0; i < channelCount; i++ ) {
    cout << i+1 << ": " << channel->getPortName(i) << endl;
  }
}

void listDevices(RtMidiOut *channel) {
  // Check outputs.
  cout << "Output channel:" << endl;
  unsigned int channelCount = channel->getPortCount();
  for ( unsigned int i = 0; i < channelCount; i++ ) {
    cout << i+1 << ": " << channel->getPortName(i) << endl;
  }
}

int main()
{
  RtMidiIn  *midiin = 0;
  RtMidiOut *midiout = 0;
  unsigned int selectedPort = 0;
  vector<unsigned char> message;
  int nBytes, i;
  double stamp;

  midiin = new RtMidiIn();
  listDevices(midiin);

  midiout = new RtMidiOut();
  listDevices(midiout);

  midiin->openPort(selectedPort);
  done = false;
  (void) signal(SIGINT, finish);
  cout << "Reading messages from " << midiin->getPortName(selectedPort) << endl;

  while (!done) {
    stamp = midiin->getMessage( &message );
    nBytes = message.size();

    for ( i=0; i<nBytes; i++ )
      std::cout << "Byte " << i << " = " << (int)message[i] << ", ";
    if ( nBytes > 0 )
      std::cout << "stamp = " << stamp << std::endl;
    usleep(100);
  }

  delete midiin;
  delete midiout;

  return 0;
}


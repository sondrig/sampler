#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <signal.h>
#include "lib/RtMidi.h"
using namespace std;

void midiMessageCallback(double delta, vector<unsigned char> *message, void *userData) {
  int nBytes = message->size();
  for (int i = 0; i < nBytes; i++) {
    cout << "Byte " << i << " = " << (int)message->at(i) << ", ";
  }
  if (nBytes > 0) {
    cout << "delta = " << delta << endl;
  }
}


int main() {
  string cliInput;
  RtMidiIn  *inChannel = 0;
  signed int selectedDevice = -1;

  inChannel = new RtMidiIn();
  unsigned int deviceCount = inChannel->getPortCount();
  
  if(!deviceCount) {
    cout << "No input devices available. Plug one in and try again!" << endl;
    goto cleanup;
  }
  // Print list of devices
  cout << "Input devices:" << endl;
  for ( unsigned int i = 0; i < deviceCount; i++ ) {
    cout << "#" << i << ": " << inChannel->getPortName(i) << endl;
  }
  if(deviceCount == 1) {
    selectedDevice = 0;
  }
  while(selectedDevice < 0) {
    cout << "Connect device: ";
    getline(cin, cliInput);
    selectedDevice = stoi(cliInput);
    cout << "You picked channel #" << selectedDevice;
    if((selectedDevice + 1) > deviceCount) {
      cout << " which is not available. Please try again." << endl;
      selectedDevice = -1;
    }
    else {
      cout << endl;
    }
  }

  // open port
  inChannel->openPort(selectedDevice);
  // assign callback
  inChannel->setCallback(&midiMessageCallback);
  cout << "Connected." << endl;

  // wait for commands
  cout << "Logging incoming midi messages. Enter 'quit' to exit." << endl;
  cliInput = "";
  while(cliInput != "quit") {
    getline(cin, cliInput);
  }

cleanup:
  delete inChannel;

  return 0;
}


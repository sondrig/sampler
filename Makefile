all:
	cd src && clang++ -Wall -D__MACOSX_CORE__ -o ../bin/main main.cpp lib/RtMidi.cpp -framework CoreMidi -framework CoreAudio -framework CoreFoundation -std=c++11

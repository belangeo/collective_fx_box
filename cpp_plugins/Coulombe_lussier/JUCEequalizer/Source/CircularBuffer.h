/*
  ==============================================================================

    CircularBuffer.h
    Created: 1 May 2020 9:54:41am
    Author:  Remi PC

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
class CircularBuffer {
public:
	CircularBuffer();
	CircularBuffer(int bufferSize, int delayLength);
	float getData();
	void setData(float data);
	void nextSample();
private:
	AudioSampleBuffer buffer;
	int writeIndex;
	int readIndex;
	int delayLength;
};
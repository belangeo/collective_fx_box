/*
  ==============================================================================

    CircularBuffer.cpp
    Created: 1 May 2020 9:54:41am
    Author:  Remi PC

  ==============================================================================
*/

#include "CircularBuffer.h"

CircularBuffer::CircularBuffer()
{
	buffer = AudioSampleBuffer();
	writeIndex = readIndex = delayLength = 0;
}

CircularBuffer::CircularBuffer(int bufferSize, int delayLength)
{
	buffer = AudioSampleBuffer(1, bufferSize);
	buffer.clear();
	writeIndex = delayLength;
	readIndex = 0;
	this->delayLength = delayLength;
}

float CircularBuffer::getData()
{
	return buffer.getSample(0, readIndex);
}

void CircularBuffer::setData(float data)
{
	buffer.setSample(0, writeIndex, data);
}

void CircularBuffer::nextSample()
{
	int bufferLength = buffer.getNumSamples();
	readIndex = ((bufferLength + writeIndex) - delayLength) % bufferLength;
	writeIndex = (writeIndex + 1) % bufferLength;
}

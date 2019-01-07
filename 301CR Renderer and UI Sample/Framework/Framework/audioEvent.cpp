#include "audioEvent.h"

//
//audioEvent::audioEvent(std::string fileName)
//{
//
//
//
//}

audioEvent::audioEvent(int soundId)
{

	whichSubsystemsInvovlved.push_back(Audio);

	nameOfEvent = "Playing audio sample";

	eventType = audio;

	void* temp1 = new void*;

	//int egg = sizeof(fileName);
	//int egg2 = sizeof(std::string);

	memcpy(temp1, &soundId, sizeof(int));

	testBin->eventVoidPointerVector.push_back(temp1);
}

audioEvent::~audioEvent()
{
}

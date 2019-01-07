#include "gameEvent.h"



gameEvent::gameEvent()
{
	
	//testBin = (void*)malloc(sizeof(testBin));
	//for (int i = 0; i < testBin->eventVoidPointerVector.size(); i++)
	//{
	//	testBin->eventVoidPointerVector[i] = (void*)malloc(sizeof(testBin->eventVoidPointerVector[i]));
	//}

}

void gameEvent::clearMemory()
{

	for (int i = 0; i <testBin->eventVoidPointerVector.size(); i++)
	{
		delete testBin->eventVoidPointerVector[i];
	}
	delete testBin;
}


gameEvent::~gameEvent()
{
	//for (int i = 0; i < testBin->eventVoidPointerVector.size(); i++)
	//{
	//	delete testBin->eventVoidPointerVector[i];
	//}

	//delete testBin;


	
}

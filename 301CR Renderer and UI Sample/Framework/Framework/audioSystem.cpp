#include "audioSystem.h"
#include <iostream>


//fmod and channel setup.
audioSystem::audioSystem()
{

	system = NULL;
	lowLevelSystem = NULL;

	
	FMOD::Studio::System::create(&system);

	if (system)
	{
		std::cout << "Audio system created!" << "/n";
	}

	system->getLowLevelSystem(&lowLevelSystem);

	if (lowLevelSystem) {
		std::cout << "Low-level (fmod) audio system created." << "\n";
	}


	lowLevelSystem->setSoftwareFormat(0, FMOD_SPEAKERMODE_STEREO, 0);
	system->initialize(1024, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, NULL);
}


audioSystem::~audioSystem()
{
}


// loads a wav file into an fmod sound, there is a vector of sounds with a correspoonding vector of sound names to allow for easy use of these sound effects later on.
void audioSystem::loadSound(char fileName[])
{
	FMOD::Sound* newSound = NULL;

	lowLevelSystem->createSound(fileName, FMOD_LOOP_OFF, NULL, &newSound);

	//newSound.setdef

	gameSounds.push_back(newSound);
	//gameSoundNames.push_back(fileName);

}


//This function plays a sound based on the soundID of the currently loaded sound effects.
void audioSystem::playAudio(int soundIdToPlay)
{

	//lowLevelSystem->createSound(soundName, FMOD_LOOP_OFF, NULL, &meow);
	//"meow.wav" backup

	//meow->setDefaults(16400, 0);


	//if (meow) {
	//	std::cout << "Sound loaded." << "\n";
	//}


	for (int i = 0; i < gameSounds.size(); i++)
	{
		if (i == soundIdToPlay)
		{
			lowLevelSystem->playSound(gameSounds[i], NULL, false, &channelToUse);
		}
	}



	//if (soundId < gameSounds.size())
	//{
	//	
	//}

	//else 
	//{
	//	std::cout << "The sound is not loaded!" << "\n";
	//}

	soundToUSe = NULL;
}

void audioSystem::audioEventSolver(gameEvent * gameEventToSolve)
{
	
	

	if (gameEventToSolve->eventType == gameEvent::audio)
	{
		//std::string fileNameToUse = *(std::string*)gameEventToSolve->testBin->eventVoidPointerVector[0];
		int soundIdToUse = *(int*)gameEventToSolve->testBin->eventVoidPointerVector[0];

		playAudio(soundIdToUse);
	}

	gameEventToSolve->whichSubsystemsInvovlved.pop_back();
}

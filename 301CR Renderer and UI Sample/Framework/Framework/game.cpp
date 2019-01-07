#include "game.h"

int playerId = 0;

sf::Texture* playerTexture;
sf::Texture* goblinTexture;
sf::Texture* ogreTexture;
sf::Texture* wallTexture;
sf::Texture* doorTexture;

//setting up renderer, physics as well as ui's
void game::setUp(std::string windowName, int Width, int Height)
{
	physics = new physicsSync(0.0f, 0.0f);

	audioSystemGame = new audioSystem();

	imageLoader imageLoader1;

	playerTexture = imageLoader1.loadTexture("../Textures/player.png");

	goblinTexture = imageLoader1.loadTexture("../Textures/goblin.png");

	ogreTexture = imageLoader1.loadTexture("../Textures/ogre.png");

	wallTexture = imageLoader1.loadTexture("../Textures/wall.png");

	doorTexture = imageLoader1.loadTexture("../Textures/door.png");

	audioSystemGame->loadSound("../Sounds/swing3.wav");

	audioSystemGame->loadSound("../Sounds/bottle.wav");

	levelSetup(15, 15, "../Levels/level0.png");


	gui.BattleGUISetup();

	//add gameObjects here!
	//gameObject* object1 = new gameObject();
	//object1->setup(b2Vec2(500, 500), 0, 50, 50, sf::Color::Black, 0.3, 0.3, 0.3, true);
	//gameObjectsVector.push_back(object1);



	//wallObject* object3 = new wallObject(b2Vec2(1000.0f, 1000.0f));
	//gameObjectsVector.push_back(object3);
	//




	//gameObjectsSetup();

	physics->physicsSetup();
	input = new inputHandler();

	input->setUpRenderer(rendererGame);
}

void game::gameObjectsSetup()
{
	// could be an issue here in the future with objects not updating!
	for (int i = 0; i < gameObjectsVector.size(); i++)
	{
		//adding all of the gameobject data into the physics susbsystem for it to create physics objects based on it
		//ADDED THIS
		


		physics->positionVectors.push_back(gameObjectsVector[i]->position);
		physics->rotationVectors.push_back(gameObjectsVector[i]->rotation);
		physics->sizeVectors.push_back(b2Vec2(gameObjectsVector[i]->sizeX, gameObjectsVector[i]->sizeY));
		gameObjectsVector[i]->gameObjectId = i;

		physics->addPhysicsObject(gameObjectsVector[i]->position.x, gameObjectsVector[i]->position.y, gameObjectsVector[i]->sizeX, gameObjectsVector[i]->sizeY, gameObjectsVector[i]->density, gameObjectsVector[i]->friction, gameObjectsVector[i]->linearDamping, gameObjectsVector[i]->IsStatic, gameObjectsVector[i]->gameObjectId);
	}
}

Enemy * enemyThatYouAreFighting;
player * playerCharacter;

gameObject * enemyHPElement;
gameObject * playerHPElement;
gameObject * potionElement;

// function to deal with the collision of the various gameobjects within the scene
void game::gameObjectsCollide()
{
	if (physics->listener.data1 != NULL)
	{
		//std::cout << "it do";
	}

	// if player gameobject collides with a gameobject with the name 'enemy'
	if (physics->listener.data1 == playerId && gameObjectsVector[physics->listener.data2]->whatType == gameObject::Enemy && rendererBattle == NULL)
	{
		
			
	
			// the name of the enemy you are fighting
			gui.addNewGUIElementWithText(b2Vec2(1000.0, 450.0f), 100.0f, 50.0f, sf::Color::Red, false, gameObjectsVector[physics->listener.data2]->gameObjectName);
			//Enemy* egg = new Enemy(Enemy*)gameObjectsVector[physics->listener.data2];

			//creating a pointer to this enemy for use later
			enemyThatYouAreFighting = (Enemy*)gameObjectsVector[physics->listener.data2];

			// enemy's health UI Setup
			gui.addNewGUIElementWithText(b2Vec2(1000.0, 600.0f), 100.0f, 50.0f, sf::Color::Red, false, ("HP: " + std::to_string(enemyThatYouAreFighting->health)));
			enemyHPElement = gui.gameObjectsInGUI.back();

			//creating a pointer to player for use later
			playerCharacter = (player*)gameObjectsVector[playerId];
			
			// player's health UI Setup
			gui.addNewGUIElementWithText(b2Vec2(100.0, 300.0f), 100.0f, 50.0f, sf::Color::Red, false, ("HP: " + std::to_string(playerCharacter->health)));
			playerHPElement = gui.gameObjectsInGUI.back();

			gui.addNewGUIElementWithText(b2Vec2(300.0, 600.0f), 100.0f, 50.0f, sf::Color::Red, false, "Remaining: " + (std::to_string(playerCharacter->numberOfPotions)));
			potionElement = gui.gameObjectsInGUI.back();

			//gui.addNewGUIElementWithText(b2Vec2(1000.0, 600.0f), 100.0f, 50.0f, sf::Color::Red, false, std::string(gameObjectsVector[physics->listener.data2]->gameObjectName));
			rendererBattle = new renderer("FIGHT!", 1280, 720);

			battleGame = new battle();

			enemyToFightInBattle = physics->listener.data2;
		
	}

	else if (physics->listener.data2 == playerId && gameObjectsVector[physics->listener.data1]->whatType == gameObject::Enemy && rendererBattle == NULL)
	{
		potionElement = gui.gameObjectsInGUI[1];
		// the name of the enemy you are fighting
		gui.addNewGUIElementWithText(b2Vec2(1000.0, 450.0f), 100.0f, 50.0f, sf::Color::Red, false, gameObjectsVector[physics->listener.data1]->gameObjectName);

		//creating a pointer to this enemy for use later
		enemyThatYouAreFighting = (Enemy*)gameObjectsVector[physics->listener.data1];

		// enemy's health UI Setup
		gui.addNewGUIElementWithText(b2Vec2(1000.0, 600.0f), 100.0f, 50.0f, sf::Color::Red, false, ("HP: " + std::to_string(enemyThatYouAreFighting->health)));
		enemyHPElement = gui.gameObjectsInGUI.back();

		playerCharacter = (player*)gameObjectsVector[playerId];
		gui.addNewGUIElementWithText(b2Vec2(100.0, 300.0f), 100.0f, 50.0f, sf::Color::Red, false, ("HP: " + std::to_string(playerCharacter->health)));
		playerHPElement = gui.gameObjectsInGUI.back();

		gui.addNewGUIElementWithText(b2Vec2(300.0, 600.0f), 100.0f, 50.0f, sf::Color::Red, false, "Remaining: " + (std::to_string(playerCharacter->numberOfPotions)));
		potionElement = gui.gameObjectsInGUI.back();


		rendererBattle = new renderer("FIGHT!", 1280, 720);
		
		battleGame = new battle();

	

		enemyToFightInBattle = physics->listener.data1;
	}


	if (physics->listener.data1 == playerId && gameObjectsVector[physics->listener.data2]->whatType == gameObject::Door)
	{
		door* newDoor = (door*)gameObjectsVector[physics->listener.data2];
		levelSetup(15, 15, newDoor->whereDoorLeads);

	}

	else if (physics->listener.data2 == playerId && gameObjectsVector[physics->listener.data1]->whatType == gameObject::Door)
	{
		door* newDoor = (door*)gameObjectsVector[physics->listener.data1];
		levelSetup(15, 15, newDoor->whereDoorLeads);

	}


	//DEBUG
	if (physics->listener.data1 != NULL)
	{
		std::cout << gameObjectsVector[physics->listener.data1]->gameObjectName << std::endl;
	}

	if (physics->listener.data2 != NULL)
	{
		std::cout << gameObjectsVector[physics->listener.data2]->gameObjectName << std::endl;
	}



	//reseting the hit data after the player has moved away from it
	if (physics->listener.data1 == physics->listener.data3 && physics->listener.data2 == physics->listener.data4)
	{
		physics->listener.data1 = NULL;
		physics->listener.data2 = NULL;
		physics->listener.data3 = NULL;
		physics->listener.data4 = NULL;
	}

	else
	{
		physics->listener.data1 = NULL;
		physics->listener.data2 = NULL;
		physics->listener.data3 = NULL;
		physics->listener.data4 = NULL;
	}


	
}

// creating a level out of game objects using game level data produced in the level class
void game::levelSetup(int SizeX, int SizeY, std::string imageFileName)
{
// wiping previous level's data  such as gameojects and related physics data

	if (gameObjectsVector.size() > 0)
	{	
		for (int i = 0; i < gameObjectsVector.size(); i++)
		{
			delete gameObjectsVector[i];
		}
		gameObjectsVector.clear();
	}

	if (physics->physicsBodies.size() > 0)
	{

		physics->physicsBodies.clear();
	}

	if (physics->positionVectors.size() > 0)
	{
		physics->positionVectors.clear();
	}

	if (physics->rotationVectors.size() > 0)
	{
		physics->rotationVectors.clear();
	}

	if (physics->sizeVectors.size() > 0)
	{
		physics->sizeVectors.clear();
	}




	level newLevel = level(SizeX, SizeY, imageFileName);
	newLevel.roomLayout(imageFileName);

	int doorNumber = 0;
	for (int i = 0; i < SizeX; i++)
	{
		for (int j = 0; j < SizeY; j++)
		{
			if (newLevel.levelData[i][j].whichChunk == level::playerLocation)
			{
				player* playerCharacter = new player();
				playerCharacter->setup(b2Vec2(newLevel.levelData[i][j].actualPositionX, newLevel.levelData[i][j].actualPositionY), 0, 15, 15, sf::Color::Yellow, 0.3, 0.3, 0.3, false);
				playerCharacter->setNameOfObject("player");
				playerCharacter->gameObjectShape.setFillColor(sf::Color::White);
				playerCharacter->gameObjectShape.setTexture(playerTexture);
			//	object2->gameObjectShape.setOrigin(newLevel.levelData[i][j].actualPositionX, newLevel.levelData[i][j].actualPositionY);
				gameObjectsVector.push_back(playerCharacter);
				playerId = gameObjectsVector.size() - 1;
			}

			if (newLevel.levelData[i][j].whichChunk == level::wall)
			{
				gameObject* wallObject1 = (new wallObject(b2Vec2(newLevel.levelData[i][j].actualPositionX, newLevel.levelData[i][j].actualPositionY)));
				wallObject1->setNameOfObject("wall");
				wallObject1->gameObjectShape.setFillColor(sf::Color::White);
				wallObject1->gameObjectShape.setTexture(wallTexture);
				gameObjectsVector.push_back(wallObject1);
			}

			if (newLevel.levelData[i][j].whichChunk == level::goblinLocation)
			{
				Goblin* enemyObject = (new Goblin());
				enemyObject->EnemySetup(b2Vec2(newLevel.levelData[i][j].actualPositionX, newLevel.levelData[i][j].actualPositionY));
				enemyObject->setNameOfObject("Goblin");
				enemyObject->gameObjectShape.setFillColor(sf::Color::White);
				enemyObject->gameObjectShape.setTexture(goblinTexture);
				gameObjectsVector.push_back(enemyObject);

			}

			if (newLevel.levelData[i][j].whichChunk == level::ogreLocation)
			{
				ogre* enemyObject = (new ogre());
				enemyObject->EnemySetup(b2Vec2(newLevel.levelData[i][j].actualPositionX, newLevel.levelData[i][j].actualPositionY));
				enemyObject->setNameOfObject("Ogre");
				enemyObject->gameObjectShape.setFillColor(sf::Color::White);
				enemyObject->gameObjectShape.setTexture(ogreTexture);
				gameObjectsVector.push_back(enemyObject);

			}

			if (newLevel.levelData[i][j].whichChunk == level::doorLocation)
			{
				door* doorObject = (new door());
				doorObject->setup(b2Vec2(newLevel.levelData[i][j].actualPositionX, newLevel.levelData[i][j].actualPositionY), 0, 25, 25, sf::Color::Yellow, 0.3, 0.3, 0.3, true);
				//enemyObject->EnemySetup(b2Vec2(newLevel.levelData[i][j].actualPositionX, newLevel.levelData[i][j].actualPositionY));
				doorObject->setNameOfObject("Door" + std::to_string(doorNumber));
				doorObject->gameObjectShape.setFillColor(sf::Color::White);
				doorObject->gameObjectShape.setTexture(doorTexture);

				doorObject->whereDoorLeads = newLevel.doorEntrances[doorNumber];
				gameObjectsVector.push_back(doorObject);


				doorNumber++;
			}
		}
	}
	
	if (rendererGame == NULL)
	{
		rendererGame = new renderer(imageFileName, 1920, 1080);

	}

	else {

		rendererGame->gameWindow->setTitle(imageFileName);
	}
	gameObjectsSetup();

	//rendererGame->gameWindow->setView()
	rendererGame->gameWindow->setSize(sf::Vector2u(newLevel.sizeBetweenObjects*newLevel.levelData.size(), newLevel.sizeBetweenObjects*newLevel.levelData.size()));
	//rendererGame->gameWindow.
	
}

bool isThereAnotherPlayer = 0;

void game::update()
{
	physics->physicsUpdate(1.0f / 60.0f, 6, 2);

	//networkConnection.networkUpdate();
	serverGame.serverUpdate();
	serverGame.givePosition(physics->positionVectors[playerId].x, physics->positionVectors[playerId].y);

	if (isThereAnotherPlayer == 0)
	{
		addOtherPlayer();
		

	}


	if (serverGame.newPosition != NULL && player2Id != 999)
	{
		//float xNew = serverGame.newPosition->x;

		physics->positionVectors[player2Id].x = serverGame.newPosition->x;
		physics->positionVectors[player2Id].y = serverGame.newPosition->y;

		//delete serverGame.newPosition;
	}


	gameObjectsCollide();

	rendererGame->updateRenderer(gameObjectsVector, physics->positionVectors, physics->rotationVectors, physics->sizeVectors);

	for (int i = 0; i < gameObjectsVector.size(); i++)
	{
		if (gameObjectsVector[i]->toBeRemoved == true)
		{
			//gameObjectsVector.erase(gameObjectsVector.begin() + i);
			gameObjectsVector[i] = new gameObject();
		}
	}


	//gui.updateGUIElementText(gui.gameObjectsInGUI[enemyto])

	/*if (rendererBattle != NULL)
	{
		rendererBattle->updateRenderer(gui.gameObjectsInGUI, )
	}*/

	/*
	b2Vec2 position = b2Vec2(physics->positionVectors[1].x, physics->positionVectors[1].y);
	float32 angle = physics->rotationVectors[1];
	printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);*/

	if (rendererBattle != NULL)
	{
		battleScreen = true;
		input->setUpRenderer(rendererBattle);
	}

	else
	{
		input->setUpRenderer(rendererGame);
		battleScreen = false;
	}

}

void game::eventHandler()
{
	for (int i = 0; i < gameEventsVector.size(); i++)
	{
		for (int j = 0; j < gameEventsVector[i]->whichSubsystemsInvovlved.size(); j++)
		{
			if (gameEventsVector[i]->whichSubsystemsInvovlved.size() > 0 && gameEventsVector[i]->whichSubsystemsInvovlved[j] == gameEvent::Physics)
			{
				physics->physicsEventSolver(gameEventsVector[i]);
			}

			if (gameEventsVector[i]->whichSubsystemsInvovlved.size() > 0 && gameEventsVector[i]->whichSubsystemsInvovlved[j] == gameEvent::Audio)
			{
				audioSystemGame->audioEventSolver(gameEventsVector[i]);
			}

			// new event solver for battle
			if (gameEventsVector[i]->whichSubsystemsInvovlved.size() > 0 && gameEventsVector[i]->whichSubsystemsInvovlved[j] == gameEvent::Battle)
			{
				if (battleGame != NULL)
				{
					battleGame->battleEventSolver(gameEventsVector[i]);
				}

				if (playerCharacter != NULL)
				{
					gui.updateGUIElementText(playerHPElement, "HP: " + std::to_string(playerCharacter->health));

					gui.updateGUIElementText(potionElement, "Remaining: " + std::to_string(playerCharacter->numberOfPotions));
					//playerHPElement->gameObjectText.setString(std::to_string(playerCharacter->health));
				}



				if (enemyThatYouAreFighting != NULL)
				{

					gui.updateGUIElementText(enemyHPElement, "HP: " + std::to_string(enemyThatYouAreFighting->health));
					//enemyThatYouAreFighting->gameObjectText.setString(std::to_string(enemyThatYouAreFighting->health));
				}
			}
		}

	}

	for (int i = 0; i < gameEventsVector.size(); i++)
	{

		if (gameEventsVector[i]->whichSubsystemsInvovlved.size() == 0)
		{
			//clearing the memory that the gameEvents were using and get rid of them
			gameEventsVector.back()->clearMemory();
			delete gameEventsVector.back();
			gameEventsVector.pop_back();
			//gameEventsVector.clear()

		}
	}
}

void game::guiHandler()
{
	

}

void game::inputHandlerGame()
{



	inputHandler::buttons whichButtonHasBeenPressed = input->whichKey();


	if (whichButtonHasBeenPressed == inputHandler::closed) {
		rendererGame->gameWindow->close();

	}

	/*
	If the event isn't an Event::Closed, we check to see if it's an Event::KeyPressed. If so,
	we run through a check to see if an arrow key is being pressed. Dependent on the key(s) being
	pressed, our textured square moves in different directions. This approach has several issues
	as discussed in the lecture, so you'll want to abstract and refine this. Can you think of any
	problems which might occur when two keys are pressed simultaneously?

	Next, if the Escape key is pressed, we consider that to be a close instruction from the user
	and the window exits.
	*/


	if (whichButtonHasBeenPressed == inputHandler::leftArrow && battleScreen == false)
	{

		gameEventsVector.push_back(new gameEvent(eventMove(-10.0f, 0.0f, gameObjectsVector[playerId])));
		//networkConnection = new networkSync();
	}

	if (whichButtonHasBeenPressed == inputHandler::rightArrow && battleScreen == false)
	{
		gameEventsVector.push_back(new gameEvent(eventMove(10.0f, 0.0f, gameObjectsVector[playerId])));
		//networkConnection.disconnect();
	}
	if (whichButtonHasBeenPressed == inputHandler::upArrow && battleScreen == false)
	{

		gameEventsVector.push_back(new gameEvent(eventMove(0.0f, 10.0f, gameObjectsVector[playerId])));
	}

	if (whichButtonHasBeenPressed == inputHandler::upArrow && battleScreen == true)
	{

		gui.GUIHandlerNextElement(gui.gameObjectsInGUI);
	}
	if (whichButtonHasBeenPressed == inputHandler::downArrow && battleScreen == false)
	{
		gameEventsVector.push_back(new gameEvent(eventMove(0.0f, -10.0f, gameObjectsVector[playerId])));
	}
	if (whichButtonHasBeenPressed == inputHandler::downArrow && battleScreen == true)
	{

		gui.GUIHandlerPreviousElement(gui.gameObjectsInGUI);
		
	}

	if (whichButtonHasBeenPressed == inputHandler::space && battleScreen == true)
	{
		//gameObjectsVector.pop_back();
		//delete gameObjectsVector.front();
		//gameObjectsVector.resize(gameObjectsVector.size() - 1);
		//texturedShape.move(sf::Vector2f(0.0f, 0.5f));
		//physics.physicsBodies[1]->ApplyForce(b2Vec2(0, -1), b2Vec2(position.x + 5, position.y + 5), 1);

		//audioSystemGame->playAudio("meow.wav");
		//gameEventsVector.push_back(new gameEvent(audioEvent(0)));
		if (gui.gameObjectsInGUI[gui.currentlySelectedElement]->gameObjectName == "Attack!")
		{
			gameEventsVector.push_back(new gameEvent(audioEvent(0)));
			gameEventsVector.push_back(new gameEvent(battleEvent(gameObjectsVector[playerId], gameObjectsVector[enemyToFightInBattle])));
			// enemy fighting back. MOVE THIS LATER
			gameEventsVector.push_back(new gameEvent(battleEvent(gameObjectsVector[enemyToFightInBattle], gameObjectsVector[playerId])));
			

		}

		if (gui.gameObjectsInGUI[gui.currentlySelectedElement]->gameObjectName == "Potion!")
		{
			//gameEventsVector.push_back(new gameEvent(battleEvent(gameObjectsVector[playerId], gameObjectsVector[enemyToFightInBattle])));
			gameEventsVector.push_back(new gameEvent(audioEvent(1)));
			gameEventsVector.push_back(new gameEvent(potionEvent(gameObjectsVector[playerId])));

			// enemy fighting back. MOVE THIS LATER
			gameEventsVector.push_back(new gameEvent(battleEvent(gameObjectsVector[enemyToFightInBattle], gameObjectsVector[playerId])));


			// enemy fighting back. MOVE THIS LATER
		}



		//gui.GUIHandlerFirstElement(gui.gameObjectsInGUI);

	}

	if (whichButtonHasBeenPressed == inputHandler::W)
	{
		//char test = sf::Keyboard::Key();
		//audioSystemGame->playAudio("ahem_x.wav");
		//gameObjectsVector.pop_back();
		//delete gameObjectsVector.front();
		//gameObjectsVector.resize(gameObjectsVector.size() - 1);
		//texturedShape.move(sf::Vector2f(0.0f, 0.5f));
		//physics.physicsBodies[1]->ApplyForce(b2Vec2(0, -1), b2Vec2(position.x + 5, position.y + 5), 1);
	
	}

	if (whichButtonHasBeenPressed == inputHandler::escape && battleScreen == true)
	{
		input->rendererEvent->gameWindow->close();
		input->rendererEvent = NULL;
		rendererBattle = NULL;
	
	}

	if (whichButtonHasBeenPressed == inputHandler::resized)
	{
		// update the view to the new size of the window

	}
	gui.GUIUpdate(gui.gameObjectsInGUI);
}

void game::addOtherPlayer()
{
	if (serverGame.otherPlayer == true)
	{
		std::cout << "BIG FUCKING EGG";


		player* playerCharacter = new player();
		playerCharacter->setup(b2Vec2(gameObjectsVector[playerId]->position.x + 50, gameObjectsVector[playerId]->position.y + 50), 0, 15, 15, sf::Color::Yellow, 0.3, 0.3, 0.3, false);
		playerCharacter->setNameOfObject("player2");
		playerCharacter->gameObjectShape.setFillColor(sf::Color::Blue);
		playerCharacter->gameObjectShape.setTexture(playerTexture);


		gameObjectsVector.push_back(playerCharacter);

		player2Id = gameObjectsVector.size() - 1;

		if (physics->physicsBodies.size() > 0)
		{

			physics->physicsBodies.clear();
		}

		if (physics->positionVectors.size() > 0)
		{
			physics->positionVectors.clear();
		}

		if (physics->rotationVectors.size() > 0)
		{
			physics->rotationVectors.clear();
		}

		if (physics->sizeVectors.size() > 0)
		{
			physics->sizeVectors.clear();
		}

		gameObjectsSetup();

		isThereAnotherPlayer = 1;
	}
}

void game::render()
{
	// use the renderer to render the gameObjects to the screen

	

	if(battleScreen == true)
	{ 
		rendererBattle->renderToScreen(gui.gameObjectsInGUI);
		//gui.gameObjectsInGUI[0].
	
	}
	
	else
	{
		playerCharacter = NULL;
		enemyThatYouAreFighting = NULL;
		rendererGame->renderToScreen(gameObjectsVector);
	}


}

game::game()
{
}


game::~game()
{
}

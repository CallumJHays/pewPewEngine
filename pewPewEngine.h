// pewPewEngine/pewPewEngine.h

#ifndef __PEW_PEW_ENGINE__
#define __PEW_PEW_ENGINE__

#define true 1
#define false 0
#define bool uint8_t

typedef struct gameObjectData GameObjectData;
typedef struct gameObject GameObject;
typedef struct game PewPewEngine;

// linked list struct to hold custom gameObjectData
struct gameObjectData {
	char* key;
	void* value;
	GameObjectData* next;
};

// Game Objects as elements in link lists
struct gameObject {
	Sprite* sprite;
	char* type;
	void (* updateFunction)(PewPewEngine*, GameObject*);
	int updateEvery;
	int updateCounter;
	GameObjectData* data;
	GameObject* nextObject;
};

// game struct object
struct game {
	GameObject* firstObject;
	GameObject* lastObject;
	uint8_t stop;
	void (* updateFunction)(PewPewEngine*);
};

// creates and initializes a new PewPewEngine for you
PewPewEngine* createPewPewEngine(void);

// does all the required stuff to initialize the Teensy correctly
void initPewPewEngine(PewPewEngine* game);

// initializes a game object, assigns memory and appends it to the end of the linked list
GameObject* createGameObject(PewPewEngine* game, float x, float y, unsigned char width, unsigned char height, unsigned char* bitmap);

// destroy a game object. Frees the memory and relinks linked list nodes
void destroyGameObject(PewPewEngine* game, GameObject* obj);

// start the game egine
void runEngine(PewPewEngine* game);

#endif /* __PEW_PEW_ENGINE__ */

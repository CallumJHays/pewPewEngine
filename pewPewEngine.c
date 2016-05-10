// pewPewEngine/pewPewEngine.c
#include <stdint.h>
#include <stdlib.h>

#include "cpu_speed.h"
#include "lcd.h"
#include "graphics.h"
#include "sprite.h"

#include "pewPewEngine.h"
#include "inputs.h"
#include "leds.h"
#include "timer.h"

PewPewEngine* createPewPewEngine(void){
	PewPewEngine* game = (PewPewEngine*) malloc(sizeof(PewPewEngine));
	initPewPewEngine(game);
	return game;
}

void initPewPewEngine(PewPewEngine* game){
	set_clock_speed(CPU_8MHz);

	lcd_init(LCD_HIGH_CONTRAST);
	initInputs();
	initLEDs();

	game->firstObject = NULL;
	game->lastObject = NULL;
	game->updateFunction = NULL;
	game->stop = true;
}

GameObject* createGameObject(PewPewEngine* game, float x, float y, unsigned char width, unsigned char height, unsigned char* bitmap){
	GameObject* obj = (GameObject*) malloc(sizeof(GameObject));
	obj->sprite = (Sprite*) malloc(sizeof(Sprite));

	init_sprite(obj->sprite, x, y, width, height, bitmap);
	obj->type = NULL;
	obj->updateFunction = NULL;
	obj->updateEvery = 0;
	obj->updateCounter = 0;
	obj->data = NULL;
	obj->nextObject = NULL;

	// if the last object exists
	if(game->lastObject != NULL){
		game->lastObject->nextObject = obj;
		game->lastObject = obj;
	}

	// otherwise, this should be the first object in the list.
	else if(game->firstObject == NULL){
		game->firstObject = obj;
		game->lastObject = obj;
	}
	return obj;
}

void destroyGameObject(PewPewEngine* game, GameObject* obj){
	// manage linked list
	// if not the first or last object in the list
	if(obj != game->firstObject && obj != game->lastObject){
		// loop until it finds the gameObject in question
		GameObject* oldGameObject = game->firstObject;
		// should always break from within. if not something is wrong
		while(1){
			if(oldGameObject->nextObject == obj){
				oldGameObject->nextObject = obj->nextObject;
				break;
			}
		}

	} else {
		// if obj is the first object 
		if(obj == game->firstObject){
			game->firstObject = obj->nextObject;
		}
		// if obj was the last object
		if(obj == game->lastObject){
			game->lastObject = NULL;
		}
	}

	// free object from memory
	free(obj);
}

void runEngine(PewPewEngine* game){
	// while the game is running
	while(!game->stop){
		// set timeDiff since last turn.
		uint16_t timeDiff = getTimeDiff();

		// if a main game update function exists
		if(game->updateFunction != NULL){
			(*(game->updateFunction))(game);
		}

		// if a first object exists
		if(game->firstObject != NULL){
			GameObject* obj = game->firstObject;
			do{
				// if it's time to run the object update function
				if(obj->updateCounter <= 0){
					// if object has an update function and if the time for that function to update is up
					if(obj->updateFunction != NULL){
						// run the update function, passing in the engine and object pointers.
						(*(obj->updateFunction))(game, obj);
					}
				} else {
					// decrement update counter by time difference
					obj->updateCounter -= timeDiff;
				}

				// if a next object exists, set it for the loop reset
				if(obj->nextObject != NULL){
					obj = obj->nextObject;
				}
			} while(obj->nextObject != NULL); // while the next object still exists
		}

		// draw all game objects to screen
		// if a first object exists
		clear_screen();
		if(game->firstObject != NULL){
			GameObject* obj = game->firstObject;
			do{
				draw_sprite(obj->sprite);
				if(obj->nextObject != NULL){
					obj = obj->nextObject;
				}
			} while(obj->nextObject != NULL);
		}
	}
}

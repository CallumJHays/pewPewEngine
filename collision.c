// pewPewEngine/collision.c
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "sprite.h"
#include "pewPewEngine.h"
#include "collision.h"

GameObject* objectCollidingWithType(char* type, bool roundVals, GameObject* obj, bool thisObjCircular, bool objTypeCircular, PewPewEngine* game){
	// loop through game objects
	// a firstObject should exist
	if(game->firstObject != NULL){
		GameObject* objTesting = game->firstObject;
		do{
			// if object is of correct type
			if(strcmp(objTesting->type, type)){
				// if objects are colliding, return pointer to object colliding with.
				if(objectsColliding(true, obj, thisObjCircular, objTesting, objTypeCircular)){
					return objTesting;
				}
			}
		} while(obj->nextObject != NULL);
	}

	// if that failed, return NULL.
	return NULL;
}

bool objectsColliding(bool roundVals, GameObject* obj1, bool sp1Circular, GameObject* obj2, bool sp2Circular){
	float x1 = obj1->sprite->x;
	float y1 = obj1->sprite->y;
	float x2 = obj2->sprite->x;
	float y2 = obj2->sprite->y;
	if(roundVals){
		x1 = floor(x1 + 0.5);
		y1 = floor(y1 + 0.5);
		x2 = floor(x2 + 0.5);
		y2 = floor(y2 + 0.5);
	}
	// if both sprites collision have circular hitboxes
	if(sp1Circular && sp2Circular){
		return circularCollision(x1, y1, obj1->sprite->width / 2.0f, x2, y2, obj2->sprite->width / 2.0f);
	}
	// else if both sprites collision have rectangular hitboxes
	else if(!sp1Circular & !sp2Circular){
		return rectangularCollision(x1, y1, obj1->sprite->width, obj1->sprite->height,
									x2, y2, obj2->sprite->width, obj2->sprite->height);
	}
	// else one must be rectangular and one must be circular
	else{
		// if object 2 is circular, swap sprite 2 and sprite 1.
		if(sp2Circular){
			GameObject* swapTemp = obj2;
			obj2 = obj1;
			obj1 = swapTemp;
		}
		// return the correct result
		return circularRectCollision(x1, y1, obj1->sprite->width / 2.0f, 
									 x2, y2, obj2->sprite->width, obj2->sprite->height);
	}
}

bool rectangularCollision(float x1, float y1, int w1, int h1, float x2, float y2, int w2, int h2){
	return x1 + w1 - 1 >= x2
		&& y1 + h1 - 1 >= y2
		&& x2 + w2 - 1 >= x1
		&& y2 + h2 - 1 >= y1;
}

bool circularCollision(float x1, float y1, float rad1, float x2, float y2, float rad2){
	return pow(x1 - x2, 2) + pow(y1 - y2, 2) <= pow(rad1, 2) + pow(rad2, 2);
}

bool circularRectCollision(float x1, float y1, float rad1, float x2, float y2, int w2, int h2){
	// if the center of the circle is within the rectangle
	// we can reuse circular collision code for this
	if(circularCollision(x1, y1, rad1, x2 + w2, y2 + h2, 0)){
		return true;
	}
	// or if any edge on the rectangle intersects with the circle
	else{
		return lineIntersectingCircle(x2, y2, x2 + w2, y2, x1, y1, rad1)
			|| lineIntersectingCircle(x2 + w2, y2, x2 + w2, y2 + h2, x1, y1, rad1)
			|| lineIntersectingCircle(x2, y2, x2, y2 + h2, x1, y1, rad1)
			|| lineIntersectingCircle(x2, y2 + h2, x2 + w2, y2 + h2, x1, y1, rad1);
	}
}

bool lineIntersectingCircle(float x1, float y1, float x2, float y2, float circlex, float circley, float radius){
	// make sure that x1 < x2
	if(x2 < x1){
		float swapTemp = x2;
		x2 = x1;
		x1 = swapTemp;
		swapTemp = y2;
		y2 = y1;
		y1 = swapTemp;
	}

	// define line mathematically
	// y = gradient * x + offset;
	float gradient = (y2 - y1) / (x2 - x1);
	float offset = y1 - gradient * x1;

	// construct projection line that passes through circle center and is perpendicular to the line
	// y = projectionGradient * x + projectionOffset
	float projectionGradient = -1 / gradient; 
	float projectionOffset = circley - projectionGradient * circlex;

	// point of intersection
	float intersectX = (projectionOffset - offset) / (gradient - projectionGradient);
	float intersectY = projectionGradient * intersectX + projectionOffset;

	if(intersectX <= x1){
		return circularCollision(circlex, circley, radius, x1, y1, 0);
	} else if(intersectX >= x2){
		return circularCollision(circlex, circley, radius, x2, y2, 0);
	} else {
		return circularCollision(circlex, circley, radius, intersectX, intersectY, 0);
	}
}

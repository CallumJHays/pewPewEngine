// pewPewEngine/collision.h

#ifndef __PEW_PEW_COLLISION__
#define __PEW_PEW_COLLISION__

// Detects whether an object is colliding with any object of type 'type'.
// Returns a pointer to the object that is colliding with the object passed into the function.
// set roundVals to true if wanting visual only collision, false otherwise.
// the 'circular' bool flags dictates whether to perform circular or rectangular collision detection.
GameObject* objectCollidingWithType(char* type, bool roundVals, GameObject* obj, bool thisObjCircular, bool objTypeCircular, PewPewEngine* game);

// Object collision detection: returns true if colliding, false if not
// set circular to true for each sprite if performing circular collision.
// set to false if needing rectangular collision (the general case)
bool objectsColliding(bool roundVals, GameObject* obj1, bool sp1Circular, GameObject* obj2, bool sp2Circular);

// Rectage Collision: returns true if colliding, false if not
bool rectangularCollision(float x1, float y1, int w1, int h1, float x2, float y2, int w2, int h2);

// Circular collision: returns true if colliding, false if not
bool circularCollision(float x1, float y1, float rad1, float x2, float y2, float rad2);

// Circular to rectangular collision: assumes object true is a circle and 2 is a rectangle
bool circularRectCollision(float x1, float y1, float rad1, float x2, float y2, int w2, int h2);

// function tests if a line intersects a circle
bool lineIntersectingCircle(float x1, float y1, float x2, float y2, float circlex, float circley, float radius);

#endif /* __PEW_PEW_ENGINE__ */
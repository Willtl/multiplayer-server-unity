#ifndef UNITY_ROTATION_H_
#define UNITY_ROTATION_H_

#include <iostream>
#include <string>

class Rotation {
public:
	float x, y, z, w;

	void print_rotation();

	Rotation(float, float, float, float);
	virtual ~Rotation();
};

#endif

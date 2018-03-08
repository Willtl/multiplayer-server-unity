#ifndef UNITY_POSITION_H_
#define UNITY_POSITION_H_

#include <iostream>
#include <string>

class Position {
public:
	float x, y, z;

	void print_position();

	Position(float, float, float);
	virtual ~Position();
};

#endif

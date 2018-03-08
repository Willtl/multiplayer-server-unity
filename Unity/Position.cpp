#include "Position.h"

Position::Position(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

void Position::print_position() {
	std::cout << "Position" << " x: " << x << " y: " << y << " z: " << z << std::endl;
}

Position::~Position() {
}

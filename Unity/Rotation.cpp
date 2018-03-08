#include "Rotation.h"

Rotation::Rotation(float x, float y, float z, float w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

void Rotation::print_rotation() {
	std::cout << "Rotation" << " x: " << x << " y: " << y << " z: " << z << std::endl;
}

Rotation::~Rotation() {
}


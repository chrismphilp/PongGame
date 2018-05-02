#pragma once

class Ball {
	public:
		int size;
		int speed;
		float x_position;
		float y_position;
		float x_direction;
		float y_direction;

		Ball(int size, int speed, float x_position, float y_position, float x_direction, float y_direction) :
			size(size),
			speed(speed),
			x_position(x_position),
			y_position(y_position),
			x_direction(x_direction),
			y_direction(y_direction)
		{}
};
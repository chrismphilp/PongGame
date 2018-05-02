#pragma once

class Racket {
	public:
		int width;
		int height;
		int speed;
		float x_position;
		float y_position;

		Racket();

		Racket(int width, int height, int speed, float x_position, float y_position) :
			width(width),
			height(height),
			speed(speed),
			x_position(x_position),
			y_position(y_position)
		{}
};
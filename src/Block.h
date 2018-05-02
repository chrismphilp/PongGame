#pragma once

class Block {
	public:
		int health;
		int height;
		int width;
		float x_origin;
		float y_origin;

		Block(int height, float width, float x_origin, float y_origin, int health) :
			height(height),
			width(width),
			x_origin(x_origin),
			y_origin(y_origin),
			health(health)
		{}
};
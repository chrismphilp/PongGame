#pragma once

class Block {
	public:
		int health;
		int width;
		int height;
		float x_origin;
		float y_origin;

		Block() {};

		Block(int width, int height, float x_origin, float y_origin, int health) :
			width(width),
			height(height),
			x_origin(x_origin),
			y_origin(y_origin),
			health(health)
		{}

		void setValues(int width, int height, float x_origin, float y_origin, int health) {
			Block::width = width;
			Block::height = height;
			Block::x_origin = x_origin;
			Block::y_origin = y_origin;
			Block::health = health;
		}
};
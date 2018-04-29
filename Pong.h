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

class Player {
	public:
		Racket PlayerRacket;
		int score;

		Player(int width, int height, int speed, float x_position, float y_position) :
			score(0),
			PlayerRacket(width, height, speed, x_position, y_position)
		{}
};

class Window {
	public:
		int height;
		int interval;
		int width;

		Window(int width, int height, int interval) :
			width(width),
			height(height),
			interval(interval)
		{}
};

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

void update(int value);
void enable2D(int width, int height);
void draw();
std::string int2str(int x);
void keyboard();
void drawRect(float x, float y, float width, float height);
void drawText(float x, float y, std::string text);
void vec2_norm(float& x, float &y);
void updateBall();
void enable2D(int width, int height);

#pragma once
#include "Racket.h"

class Player {
	public:
		Racket PlayerRacket;
		int score;

		Player(int width, int height, int speed, float x_position, float y_position) :
			score(0),
			PlayerRacket(width, height, speed, x_position, y_position)
		{}
};
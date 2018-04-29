#include "stdafx.h"
#include <string>
#include <windows.h>
#include <iostream>
#include <conio.h>
#include <sstream> 
#include <math.h> 
#include <gl\gl.h>
#include <gl\glu.h>
#include <GL/freeglut.h>

#include "Pong.h"

#pragma comment(lib, "OpenGL32.lib")

// Keycodes
#define VK_W 0x57
#define VK_S 0x53

Window GameWindow(500, 200, (1000/60));
Ball PlayerBall(8, 5, 250, 100, -1.0f, 0.0f);
Player Player1(10, 80, 3, 10.0f, 50.0f);
Player Player2(10, 80, 3, 500 - 10.0f, 50);

// window size and update rate (60 fps)
int width = 500;
int height = 200;
int interval = 1000 / 60;

// ball
float ball_pos_x = width / 2;
float ball_pos_y = height / 2;
float ball_dir_x = -1.0f;
float ball_dir_y = 0.0f;
int ball_size = 8;
int ball_speed = 8;

// score
int score_left = 0;
int score_right = 0;

// rackets in general
int racket_width = 10;
int racket_height = 80;
int racket_speed = 3;

// left racket position
float racket_left_x = 10.0f;
float racket_left_y = 50.0f;

// right racket position
float racket_right_x = width - racket_width - 10;
float racket_right_y = 50;

int main(int argc, char** argv) {
	// initialize opengl (via glut)
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(GameWindow.width, GameWindow.height);
	glutCreateWindow("Pong Game");
	printf("%d\n%d", GameWindow.width, Player1.PlayerRacket.width);

	glutDisplayFunc(draw);
	glutTimerFunc(GameWindow.interval, update, 0);

	enable2D(GameWindow.width, GameWindow.height);
	glColor3f(1.0f, 1.0f, 1.0f);

	// start the whole thing
	glutMainLoop();
	return 0;
}

void draw() {
	// clear (has to be done at the beginning)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	// draw rackets
	drawRect(Player1.PlayerRacket.x_position, Player1.PlayerRacket.y_position, Player1.PlayerRacket.width, Player1.PlayerRacket.height);
	drawRect(Player2.PlayerRacket.x_position, Player2.PlayerRacket.y_position, Player2.PlayerRacket.width, Player2.PlayerRacket.height);

	// draw score
	drawText(
		GameWindow.width / 2 - 10, 
		GameWindow.height - 15,
		int2str(Player1.score) + ":" + int2str(Player2.score)
	);

	drawRect(
		PlayerBall.x_position - PlayerBall.size / 2, 
		PlayerBall.y_position - PlayerBall.size / 2, 
		PlayerBall.size, 
		PlayerBall.size
	);

	// swap buffers (has to be done at the end)
	glutSwapBuffers();
}

void update(int value) {
	// input handling
	keyboard();
	// update ball
	updateBall();
	// Call update() again in 'interval' milliseconds
	glutTimerFunc(GameWindow.interval, update, 0);
	// Redisplay frame
	glutPostRedisplay();
}

std::string int2str(int x) {
	// converts int to string
	std::stringstream ss;
	ss << x;
	return ss.str();
}

void keyboard() {
	// left racket
	if (GetAsyncKeyState(VK_W)) Player1.PlayerRacket.y_position += Player1.PlayerRacket.speed;
	if (GetAsyncKeyState(VK_S)) Player1.PlayerRacket.y_position -= Player1.PlayerRacket.speed;

	// right racket
	if (GetAsyncKeyState(VK_UP)) Player2.PlayerRacket.y_position += Player2.PlayerRacket.speed;
	if (GetAsyncKeyState(VK_DOWN)) Player2.PlayerRacket.y_position -= Player2.PlayerRacket.speed;
}

void drawRect(float x, float y, float width, float height) {
	glBegin(GL_QUADS);
		glVertex2f(x, y);
		glVertex2f(x + width, y);
		glVertex2f(x + width, y + height);
		glVertex2f(x, y + height);
	glEnd();
}

void drawText(float x, float y, std::string text) {
	glRasterPos2f(x, y);
	glutBitmapString(GLUT_BITMAP_8_BY_13, (const unsigned char*)text.c_str());
}

void vec2_norm(float& x, float &y) {
	// sets a vectors length to 1 (which means that x + y == 1)
	float length = sqrt((x * x) + (y * y));
	if (length != 0.0f) {
		length = 1.0f / length;
		x *= length;
		y *= length;
	}
}

void updateBall() {
	// fly a bit
	PlayerBall.x_position += PlayerBall.x_direction * PlayerBall.speed;
	PlayerBall.y_position += PlayerBall.y_direction * PlayerBall.speed;

	// hit by left racket?
	if (PlayerBall.x_position < Player1.PlayerRacket.x_position + Player1.PlayerRacket.width &&
		PlayerBall.x_position > Player1.PlayerRacket.x_position &&
		PlayerBall.y_position < Player1.PlayerRacket.y_position + Player1.PlayerRacket.height &&
		PlayerBall.y_position >  Player1.PlayerRacket.y_position) {
		// set fly direction depending on where it hit the racket
		// (t is 0.5 if hit at top, 0 at center, -0.5 at bottom)
		float t = ((PlayerBall.y_position - Player1.PlayerRacket.y_position) / Player1.PlayerRacket.height) - 0.5f;
		PlayerBall.x_direction = fabs(PlayerBall.x_direction); // force it to be positive
		PlayerBall.y_direction = t;
	}

	// hit by right racket?
	if (PlayerBall.x_position > Player2.PlayerRacket.x_position &&
		PlayerBall.x_position < Player2.PlayerRacket.x_position + Player2.PlayerRacket.width &&
		PlayerBall.y_position < Player2.PlayerRacket.y_position + Player2.PlayerRacket.height &&
		PlayerBall.y_position > Player2.PlayerRacket.y_position) {
		// set fly direction depending on where it hit the racket
		// (t is 0.5 if hit at top, 0 at center, -0.5 at bottom)
		float t = ((PlayerBall.y_position - Player2.PlayerRacket.y_position) / Player2.PlayerRacket.height) - 0.5f;
		PlayerBall.x_direction = -fabs(PlayerBall.x_direction); // force it to be positive
		PlayerBall.y_direction = t;
	}

	// hit left wall?
	if (PlayerBall.x_position < 0) {
		Player2.score++;
		PlayerBall.x_position = GameWindow.width / 2;
		PlayerBall.y_position = GameWindow.height / 2;
		PlayerBall.x_direction = fabs(PlayerBall.x_direction); // force it to be positive
		PlayerBall.y_direction = 0;
	}

	// hit right wall?
	if (PlayerBall.x_position > GameWindow.width) {
		Player1.score++;
		PlayerBall.x_position = GameWindow.width / 2;
		PlayerBall.y_position = GameWindow.height / 2;
		PlayerBall.x_direction = -fabs(PlayerBall.x_direction); // force it to be negative
		PlayerBall.y_direction = 0;
	}

	// hit top wall?
	if (PlayerBall.y_position > GameWindow.height) {
		PlayerBall.y_direction = -fabs(PlayerBall.y_direction); // force it to be negative
	}

	// hit bottom wall?
	if (PlayerBall.y_position < 0) {
		PlayerBall.y_direction = fabs(PlayerBall.y_direction); // force it to be positive
	}

	// make sure that length of dir stays at 1
	vec2_norm(PlayerBall.x_direction, PlayerBall.y_direction);
}

void enable2D(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, width, 0.0f, height, 0.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

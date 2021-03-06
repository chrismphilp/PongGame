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

Window	GameWindow(500, 200, (1000/60));
Ball	PlayerBall(8, 5, 250, 100, -1.0f, 0.0f);
Player	Player1(10, 80, 3, 10, 50);
Player	Player2(10, 80, 3, GameWindow.width - 10, 50);

int main(int argc, char** argv) {
	// initialize opengl (via glut)
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(GameWindow.width, GameWindow.height);
	glutCreateWindow("Pong Game");

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

	if (PlayerBall.y_position - 1 < Player2.PlayerRacket.y_position + 50 && 
		Player2.PlayerRacket.y_position + 50 < PlayerBall.y_position + 1);
	else if (PlayerBall.y_position > Player2.PlayerRacket.y_position + 50) {
		Player2.PlayerRacket.y_position = Player2.PlayerRacket.y_position + 1;
	}
	else {
		Player2.PlayerRacket.y_position = Player2.PlayerRacket.y_position - 1;
	}
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
	if (GetAsyncKeyState(VK_UP)) Player1.PlayerRacket.y_position += Player1.PlayerRacket.speed;
	if (GetAsyncKeyState(VK_DOWN)) Player1.PlayerRacket.y_position -= Player1.PlayerRacket.speed;
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
		PlayerBall.y_direction = ((rand() % (10 - 1) + 1) / 10.0);
	}

	// hit right wall?
	if (PlayerBall.x_position > GameWindow.width) {
		Player1.score++;
		PlayerBall.x_position = GameWindow.width / 2;
		PlayerBall.y_position = GameWindow.height / 2;
		PlayerBall.x_direction = -fabs(PlayerBall.x_direction); // force it to be negative
		PlayerBall.y_direction = ((rand() % (10 - 1) + 1) / 10.0);
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

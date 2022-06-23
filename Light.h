#pragma once

#include "ShadowCaster.h"
#include "Player.h"

class Light
{
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	int nRays;
public:
	Light(int nRays);
	void Render();
};

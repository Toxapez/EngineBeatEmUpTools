#pragma once
#include <string>
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "Vector2.h"
#include "Color.h"

#include <GL/glew.h>
#include "glfw3.h"
#include <vector>

#include "Mesh.h"
#include "Primitives.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut-3.7.6-bin/glut.h>
#endif
#include "Keyboard.h"


class OpenGLClass {
	static void CrearVentana();
public:
	static Color colorWindow;
	static int screenSizeX;
	static int screenSizeY;
	static Vector2 GetScreenSizeVector2();
	static void Finish();
	static void Start();
	static void Clear();
	static void Present();

	static const int mayorVersion;
	static const int minorVersion;
	static std::vector<Shader*> shaders;
	static std::vector<Mesh*> meshes;

	static glm::vec3 cameraPos;
	static glm::vec3 cameraFront;
	static glm::vec3 cameraUp;
	static glm::vec3 direction;

	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	static void input();
	static float lastX, lastY, yaw, pitch, fov;
	static bool firstMouse;
	static Vector2 VecToOpenGl(Vector2 v);
	static void LoadTextureFromSurface(SDL_Surface* s, unsigned int* texture);
	static glm::vec2 Vector2ToVec2(Vector2 v);
};


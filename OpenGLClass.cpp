#include "OpenGLClass.h"
#include "InputManager.h"


glm::vec3 OpenGLClass::cameraPos = glm::vec3(1.0f, 3.0f, 10.0f);
glm::vec3 OpenGLClass::cameraFront = glm::vec3(1.0f, 3.0f, 10.0f);
glm::vec3 OpenGLClass::cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 OpenGLClass::direction = glm::vec3(0);
bool OpenGLClass::firstMouse = true;

int OpenGLClass::screenSizeX = 1080;
int OpenGLClass::screenSizeY = 720;
float OpenGLClass::lastX = OpenGLClass::screenSizeX / 2, OpenGLClass::lastY = OpenGLClass::screenSizeY / 2,
OpenGLClass::yaw = -90, OpenGLClass::pitch = 0, OpenGLClass::fov = 45;
const int OpenGLClass::mayorVersion = 3;
const int OpenGLClass::minorVersion = 3;
Color OpenGLClass::colorWindow = Color(255,0,0);
std::vector<Shader*> OpenGLClass::shaders;
std::vector<Mesh*> OpenGLClass::meshes;


void OpenGLClass::CrearVentana() {


	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, mayorVersion);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minorVersion);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	auto context = SDL_GL_CreateContext(SDLClass::window);


	glewInit();

}

void OpenGLClass::Finish() {
}



void OpenGLClass::Start() {
	CrearVentana();
	shaders.push_back(new Shader(OpenGLClass::minorVersion, OpenGLClass::mayorVersion, "triangle1"));
	shaders.push_back(new Shader(OpenGLClass::minorVersion, OpenGLClass::mayorVersion, "line1"));
	shaders.push_back(new Shader(OpenGLClass::minorVersion, OpenGLClass::mayorVersion, "texture1"));
	shaders.push_back(new Shader(OpenGLClass::minorVersion, OpenGLClass::mayorVersion, "rect1"));
	shaders.push_back(new Shader(OpenGLClass::minorVersion, OpenGLClass::mayorVersion, "light1"));

	int dist = 40;
	for (int i = 0; i < 1; i++) {
		meshes.push_back(
			new Mesh(
				new TriangleP(),
				glm::vec3(0, 0, 0),//pos
				glm::vec3(0),//origin
				glm::vec3(0),//rot
				glm::vec3(1),//scale
				""
			)
		);
	}



}

void OpenGLClass::Clear() {
	glClearColor((float)SDLClass::colorWindow.r / 255, (float)SDLClass::colorWindow.g / 255,
		(float)SDLClass::colorWindow.b/255, 1);
	glClear(GL_COLOR_BUFFER_BIT );
}



void OpenGLClass::Present() {

	//if(Keyboard::KeyboardCheck(SDL_SCANCODE_UP))
	//	SDLClass::ChangeWindowSize(SDLClass::screenSizeX+10, SDLClass::screenSizeY+10);
	//
	//if (Keyboard::KeyboardCheck(SDL_SCANCODE_DOWN))
	//	SDLClass::ChangeWindowSize(SDLClass::screenSizeX-10, SDLClass::screenSizeY-10);

	//End Draw
	SDL_GL_SwapWindow(SDLClass::window);
	glFlush();

	glBindVertexArray(0);
	glUseProgram(0);
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}


Vector2 OpenGLClass::GetScreenSizeVector2() {
	return Vector2(screenSizeX, screenSizeY);
}

Vector2 OpenGLClass::VecToOpenGl(Vector2 v) {
	return Vector2(v.x / SDLClass::screenSizeX, -v.y / SDLClass::screenSizeY) * 2 - Vector2(1,-1);
}

void OpenGLClass::LoadTextureFromSurface(SDL_Surface* s, unsigned int* texture) {

	auto colors = s->format->BytesPerPixel;

	GLenum textureFormat;
	if (colors == 4) {   // alpha
		if (s->format->Rmask == 0x000000ff)
			textureFormat = GL_RGBA;
		else
			textureFormat = GL_BGRA;
	}
	else {             // no alpha
		if (s->format->Rmask == 0x000000ff)
			textureFormat = GL_RGB;
		else
			textureFormat = GL_BGR;
	}

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, texture);
	glBindTexture(GL_TEXTURE_2D, *texture);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, s->w, s->h, 0,
		textureFormat, GL_UNSIGNED_BYTE, s->pixels);


	glEnable(GL_TEXTURE_2D);

	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);

}

glm::vec2 OpenGLClass::Vector2ToVec2(Vector2 v) {
	return glm::vec2(int(v.x),int(v.y));
}
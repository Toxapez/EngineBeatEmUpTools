#include "Mesh.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Mesh::Mesh(
	Primitive* p,
	glm::vec3 position = glm::vec3(0.f),
	glm::vec3 origin = glm::vec3(0.f),
	glm::vec3 rotation = glm::vec3(0.f),
	glm::vec3 scale = glm::vec3(1.f),
	const char* textureName = "")
{
	primitive = p;
	this->position = position;
	this->origin = position;
	this->rotation = rotation;
	this->scale = scale;

	this->nrOfVertices = p->getNrOfVertices();
	this->nrOfIndices = p->getNrOfIndices();

	this->vertexArray = new Vertex[this->nrOfVertices];
	for (size_t i = 0; i < this->nrOfVertices; i++)
	{
		this->vertexArray[i] = p->getVertices()[i];
	}

	this->indexArray = new GLuint[this->nrOfIndices];
	for (size_t i = 0; i < this->nrOfIndices; i++)
	{
		this->indexArray[i] = p->getIndices()[i];
	}

	this->initVAO();
	this->updateModelMatrix();

	if (textureName != "") {
		unsigned char* image = stbi_load(textureName, &widthImage, &heightImage, NULL, 0);
		glGenTextures(1, &texture);

		glBindTexture(GL_TEXTURE_2D, texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthImage, heightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

		glGenerateMipmap(GL_TEXTURE_2D);

		glActiveTexture(0);
		glBindTexture(GL_TEXTURE_2D, 0);
		stbi_image_free(image);
	}
	glm::mat4 v(1);
	projectionMatrix = glm::perspective(glm::radians(45.0f), 640 / (float)480, 0.1f, 100.0f);
	
	viewMatrix = v;

	viewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));

	colorBlend = glm::vec3(255,0,0);
	giro = glm::vec3((rand() % 100) * .001, (rand() % 100) * .001, (rand() % 100) * .001);
}
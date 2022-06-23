#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glm/glm.hpp>
#include <fstream>
#include "Primitives.h"
#include <iostream>
#include <string>


class Shader
{
	const int versionMajor;
	const int versionMinor;
	std::string loadShaderSource(const char* fileName)
	{
		std::string temp = "";
		std::string src = "";

		std::ifstream file;

		//Vertex
		file.open(fileName);

		if (file.is_open())
		{
			while (getline(file, temp))
				src += temp + "\n";
		}

		file.close();

		std::string versionNr =
			std::to_string(this->versionMajor) +
			std::to_string(this->versionMinor) +
			"0";

		src.replace(src.find("#version"), 12, ("#version " + versionNr));

		return src;
	}

	void linkProgram(GLuint vertexShader, GLuint geometryShader, GLuint fragmentShader)
	{
		char infoLog[512];
		GLint success;

		this->id = glCreateProgram();

		glAttachShader(this->id, vertexShader);

		if (geometryShader)
			glAttachShader(this->id, geometryShader);

		glAttachShader(this->id, fragmentShader);

		glLinkProgram(this->id);

		glGetProgramiv(this->id, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(this->id, 512, NULL, infoLog);
		}

		glUseProgram(0);
	}

	GLuint loadShader(GLenum type, const char* fileName)
	{
		char infoLog[512];
		GLint success;

		GLuint shader = glCreateShader(type);
		std::string str_src = this->loadShaderSource(fileName);
		const GLchar* src = str_src.c_str();
		glShaderSource(shader, 1, &src, NULL);
		glCompileShader(shader);

		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

		return shader;
	}

	

public:
	GLuint id;
	void use()
	{
		glUseProgram(this->id);
	}

	void unuse()
	{
		glUseProgram(0);
	}

	Shader(const int versionMajor, const int versionMinor,
		std::string file, char* geometryFile = nullptr)
		: versionMajor(versionMajor), versionMinor(versionMinor)
	{
		GLuint vertexShader = 0;
		GLuint geometryShader = 0;
		GLuint fragmentShader = 0;

		vertexShader = loadShader(GL_VERTEX_SHADER, ("assets/shader/" + file + "/v.glsl").c_str());

		if (geometryFile != nullptr)
			geometryShader = loadShader(GL_GEOMETRY_SHADER, geometryFile);

		fragmentShader = loadShader(GL_FRAGMENT_SHADER, ("assets/shader/" + file + "/f.glsl").c_str());

		this->linkProgram(vertexShader, geometryShader, fragmentShader);

		//End
		glDeleteShader(vertexShader);
		glDeleteShader(geometryShader);
		glDeleteShader(fragmentShader);
	}

	void setMat4fv(glm::mat4 value, const GLchar* name, GLboolean transpose = GL_FALSE)
	{
		this->use();
		unsigned int n = glGetUniformLocation(id, name);
		glUniformMatrix4fv(n, 1, transpose, glm::value_ptr(value));

		this->unuse();
	}

	void setVec3fv(glm::vec3 value, const GLchar* name)
	{
		this->use();
		unsigned int n = glGetUniformLocation(id, name);
		glUniform3fv(n, 1, glm::value_ptr(value));

		this->unuse();
	}

	void setVec2fv(glm::vec2 value, const GLchar* name)
	{
		this->use();
		unsigned int n = glGetUniformLocation(id, name);
		glUniform2fv(n, 1, glm::value_ptr(value));

		this->unuse();
	}
};



class Mesh
{
	Vertex* vertexArray;
	unsigned nrOfVertices;
	GLuint* indexArray;
	unsigned nrOfIndices;

	int widthImage;
	int heightImage;

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
public:
	unsigned int texture;
	glm::vec3 position;
	glm::vec3 origin;
	glm::vec3 rotation;
	glm::vec3 scale;
	
	glm::vec3 colorBlend;

	glm::mat4 projectionMatrix;
	glm::mat4 ModelMatrix;
	glm::mat4 viewMatrix;

	glm::vec3 giro;

	Primitive* primitive;

	void initVAO()
	{
		//CreateVAO
		glCreateVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		
		//GEN VBO AND BIND AND SEND DATA
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, nrOfVertices * sizeof(Vertex), vertexArray, GL_STATIC_DRAW);
		
		//GEN EBO AND BIND AND SEND DATA
		if (this->nrOfIndices > 0)
		{
			glGenBuffers(1, &EBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, nrOfIndices * sizeof(GLuint), indexArray, GL_STATIC_DRAW);
		}
		
		//SET VERTEXATTRIBPOINTERS AND ENABLE (INPUT ASSEMBLY)
		//Position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
		glEnableVertexAttribArray(0);
		//Color
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
		glEnableVertexAttribArray(1);
		//uvs
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
		glEnableVertexAttribArray(2);
		
		//BIND VAO 0
		glBindVertexArray(0);
	}

	void updateUniforms(Shader* shader)
	{
		//shader->setMat4fv(ModelMatrix, "model");
		//shader->setMat4fv(projectionMatrix, "projection");
		//shader->setMat4fv(viewMatrix, "view");
		//shader->setVec3fv(colorBlend,"colorBlend");
		shader->setVec2fv(glm::vec2(SDLClass::screenSizeX,SDLClass::screenSizeY), "screensize");
	}

	void updateModelMatrix()
	{

		//ModelMatrix = glm::mat4(1.f);
		//ModelMatrix = glm::translate(ModelMatrix, origin);
		//ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));
		//ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));
		//ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));
		//ModelMatrix = glm::translate(ModelMatrix, position - origin);
		//ModelMatrix = glm::scale(ModelMatrix, scale);

		
		
	}
public:
	Mesh() {};
	Mesh(
		Primitive* primitive,
		glm::vec3 position,
		glm::vec3 origin,
		glm::vec3 rotation,
		glm::vec3 scale,
		const char* textureName);
	

	void render(Shader* shader)
	{

		for (size_t i = 0; i < this->nrOfVertices; i++)
		{
			this->vertexArray[i] = primitive->getVertices()[i];
		}

		for (size_t i = 0; i < this->nrOfIndices; i++)
		{
			this->indexArray[i] = primitive->getIndices()[i];
		}

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, nrOfVertices * sizeof(Vertex), vertexArray, GL_STATIC_DRAW);


		updateModelMatrix();
		updateUniforms(shader);

		
		shader->use();
		if (texture) {
			glActiveTexture(GL_TEXTURE0 + 0);
			glBindTexture(GL_TEXTURE_2D, texture);
			glUniform1i(glGetUniformLocation(shader->id, "texture1"), 0);
		}
		glBindVertexArray(this->VAO);

		
		

		//RENDER
		if (this->nrOfIndices == 0)
			glDrawArrays(GL_TRIANGLES, 0, nrOfVertices);
		if (this->nrOfIndices == 2)
			glDrawArrays(GL_LINES, 0, nrOfVertices);
		else
			glDrawElements(GL_TRIANGLES, nrOfIndices, GL_UNSIGNED_INT, 0);


		//Cleanup
		glBindVertexArray(0);
		glUseProgram(0);
		glActiveTexture(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

};


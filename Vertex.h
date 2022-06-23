#pragma once
struct Vertex
{
	glm::vec3 position;
	glm::vec4 color;
	glm::vec2 texcoord;
	glm::vec3 normal;
	Vertex() {};
	Vertex(glm::vec3 a, glm::vec4 b, glm::vec2 c, glm::vec3 d) {
		position= a;
		color	= b;
		texcoord= c;
		normal  = d;
	}
};

struct RotInfo
{
	glm::vec2 rotation;
	RotInfo() {};
	RotInfo(glm::vec2 f) {
		rotation = f;
	}
};

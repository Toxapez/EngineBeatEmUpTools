#include "Light.h"


Light::Light(int nr) {

	nRays = nr;
	//CreateVAO
	glCreateVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	double angle = (Meth::PI * 2) / nRays;

	RotInfo* vertexArray = new RotInfo[nRays*3];
	for (int i = 0; i < nRays * 3; i+= 3) {
		vertexArray[i] = glm::vec2(angle * i, 0);
		vertexArray[i+1] = glm::vec2(angle * i, 1);
		vertexArray[i+2] = glm::vec2(angle * i, 2);
	}


	//GEN VBO AND BIND AND SEND DATA
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(RotInfo) * nRays * 3, vertexArray, GL_STATIC_DRAW);

	int nrOfIndices = 1;

	GLuint* indexArray = new GLuint[nRays*3];
	for (int i = 0; i < nRays * 3; i+= 3) {
		indexArray[i] = 0;
		indexArray[i+1] = 1;
		indexArray[i+2] = 2;
	}


	//GEN EBO AND BIND AND SEND DATA
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * nRays * 3, indexArray, GL_STATIC_DRAW);

	//SET VERTEXATTRIBPOINTERS AND ENABLE (INPUT ASSEMBLY)
	//info
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(RotInfo), (GLvoid*)offsetof(RotInfo, rotation));
	glEnableVertexAttribArray(0);

	//BIND VAO 0
	glBindVertexArray(0);
}

void Light::Render() {
	glBindVertexArray(this->VAO);
	//RENDER
	glDrawArrays(GL_POINTS, 0, nRays*3);


	//Cleanup
	glBindVertexArray(0);
	glUseProgram(0);
}

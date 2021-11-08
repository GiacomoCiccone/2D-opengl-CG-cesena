#pragma once
#include "Sky.hpp"

Sky::Sky(int triangles) : Model(triangles) {}

void Sky::buildModel() {
	this->vertices.insert(this->vertices.end(), { glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0), glm::vec3(1.0, 1.0, 0.0) });
	this->colors.insert(this->colors.end(),
		{ glm::vec4(this->normalizeColors(255, 238, 182), 1.0), glm::vec4(this->normalizeColors(255, 238, 182), 1.0), glm::vec4(this->normalizeColors(255, 216, 157), 1.0), glm::vec4(this->normalizeColors(255, 216, 157), 1.0) });

	this->nv = 4;
}

void Sky::drawModel() {
	glBindVertexArray(this->VAO);

	glm::mat4 mat = glm::mat4(1.0);
	mat = glm::scale(mat, glm::vec3(SCR_WIDTH, SCR_HEIGHT, 1.0));


	this->setModelMatrix(mat);

	glUniformMatrix4fv(modelMatrixPTR, 1, GL_FALSE, glm::value_ptr(this->getModelMatrix()));

	glDrawArrays(GL_TRIANGLE_STRIP, 0, this->getNumVertices());
}
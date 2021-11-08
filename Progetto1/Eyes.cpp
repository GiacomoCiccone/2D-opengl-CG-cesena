#pragma once
#include "Eyes.hpp"

Eyes::Eyes(int triangles) : Model(triangles) {
	this->posx = this->posy = this->angle = 0.0;
}

void Eyes::buildModel() {
	float t = 0;
	float step = 2 * PI / this->nTriangles;

	this->vertices.clear();
	this->colors.clear();

	this->vertices.push_back(glm::vec3(0.0, 0.0, 0.0));
	this->colors.push_back(glm::vec4(this->normalizeColors(112, 35, 4), 1.0));
	for (t; t < 2 * PI; t += step)
	{
		this->vertices.push_back(glm::vec3(cos(t), sin(t), 0.0));
		this->colors.push_back(glm::vec4(this->normalizeColors(112, 35, 4), 1.0));
	}
	this->nv = this->vertices.size();
}

void Eyes::drawModel() {
	static int n = 0;
	glBindVertexArray(this->VAO);

	glm::mat4 mat = glm::mat4(1.0);
	mat = glm::translate(mat, glm::vec3(this->posx, this->posy, 1.0));
	mat = glm::rotate(mat, glm::radians(this->angle), glm::vec3(0.0, 0.0, 1.0));
	n % 2 == 0 ? mat = glm::translate(mat, glm::vec3(10, 17, 0.0)) : mat = glm::translate(mat, glm::vec3(-10,17, 0.0));
	mat = glm::scale(mat, glm::vec3(5, 10, 1.0));
	
	this->setModelMatrix(mat);

	glUniformMatrix4fv(modelMatrixPTR, 1, GL_FALSE, glm::value_ptr(this->getModelMatrix()));

	glDrawArrays(GL_TRIANGLE_FAN, 0, this->getNumVertices());
	n++;
}

void Eyes::setPos(float x, float y)
{
	this->posx = x;
	this->posy = y;
}

void Eyes::updateAngle(float delta)
{
	this->angle += delta;
}

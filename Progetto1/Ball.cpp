#pragma once
#include "Ball.hpp"

Ball::Ball(int triangles) : Model(triangles) {
	this->eyes = new Eyes(100);
	this->mouth = new Mouth(100);
	this->posx = this->posy = 0;
	this->oldPosx = -1;
	this->color = glm::vec4(1.0, 1.0, 1.0, 1.0);
}

void Ball::buildModel() {
	float t = 0;
	float step = 2 * PI / this->nTriangles;

	this->vertices.clear();
	this->colors.clear();

	this->vertices.push_back(glm::vec3(0.0, 0.0, 0.0));
	this->colors.push_back(color);
	for (t; t < 2 * PI; t+=step)
	{
		this->vertices.push_back(glm::vec3(cos(t), sin(t), 0.0));
		this->colors.push_back(color);
	}
	this->nv = this->vertices.size();

	this->eyes->buildModel();
	this->eyes->initVAO();

	this->mouth->buildModel();
	this->mouth->initVAO();
}

void Ball::drawModel() {
	this->oldPosx < this->posx ? this->eyes->updateAngle(-5) : this->oldPosx > this->posx ? this->eyes->updateAngle(5) : this->eyes->updateAngle(0.0);

	this->oldPosx < this->posx ? this->mouth->updateAngle(-5) : this->oldPosx > this->posx ? this->mouth->updateAngle(5) : this->mouth->updateAngle(0.0);
	
	this->eyes->setPos(this->posx, this->posy);
	this->eyes->drawModel();

	this->eyes->setPos(this->posx, this->posy);
	this->eyes->drawModel();

	this->mouth->setPos(this->posx, this->posy);
	this->mouth->drawModel();

	glBindVertexArray(this->VAO);

	glm::mat4 mat = glm::mat4(1.0);
	mat = glm::translate(mat, glm::vec3(this->posx, this->posy, 1.0));
	mat = glm::scale(mat, glm::vec3(40, 40, 1.0));


	this->setModelMatrix(mat);

	glUniformMatrix4fv(modelMatrixPTR, 1, GL_FALSE, glm::value_ptr(this->getModelMatrix()));

	glDrawArrays(GL_TRIANGLE_FAN, 0, this->getNumVertices());
}

void Ball::setPos(float x, float y)
{
	this->oldPosx = this->posx;
	this->posx = x;
	this->posy = y;
}

Eyes* Ball::getEyes()
{
	return this->eyes;
}

Mouth* Ball::getMouth()
{
	return this->mouth;
}

void Ball::setColor(glm::vec4 col)
{
	this->color = glm::vec4(this->normalizeColors(col.r, col.g, col.b), col.a);
}

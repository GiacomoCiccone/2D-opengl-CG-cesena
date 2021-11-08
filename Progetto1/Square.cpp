#pragma once
#include "Square.hpp"

Square::Square(int triangles) : Model(triangles) {}

void Square::buildModel() {
	this->vertices.insert(this->vertices.end(), { glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0), glm::vec3(1.0, 1.0, 0.0) });
	this->colors.insert(this->colors.end(),
		{ glm::vec4(this->normalizeColors(187, 84, 52), 1.0), glm::vec4(this->normalizeColors(187, 84, 52), 1.0), glm::vec4(this->normalizeColors(187, 84, 52), 1.0), glm::vec4(this->normalizeColors(187, 84, 52), 1.0) });

	this->nv = 4;
}

void Square::drawModel() {
	glBindVertexArray(this->VAO);

	glm::mat4 mat = glm::mat4(1.0);
	mat = glm::translate(mat, glm::vec3(this->offset + this->posx, this->posy, 1.0));
	mat = glm::scale(mat, glm::vec3(50, 50, 1.0));


	this->setModelMatrix(mat);

	glUniformMatrix4fv(modelMatrixPTR, 1, GL_FALSE, glm::value_ptr(this->getModelMatrix()));

	glDrawArrays(GL_TRIANGLE_STRIP, 0, this->getNumVertices());
}

void Square::setPos(float x, float y)
{
	this->posx = x;
	this->posy = y;
}

void Square::updateOffset(float delta) {
	if (this->offset + delta <= 0 && abs(this->offset + delta) <= SCR_WIDTH * 5)
	{
		this->offset += delta;
	}
}
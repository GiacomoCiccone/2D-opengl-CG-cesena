#pragma once
#include "ShadowTree.hpp"

ShadowTree::ShadowTree(int triangles) : Model(triangles) {
	this->posX = 0.0;
	this->posY = 0.0;
	this->scaleX = 0.0;
	this->scaleY = 0.0;
}

void ShadowTree::buildModel() {
	float t = 0;
	float step = 2 * PI / this->nTriangles;
	this->vertices.push_back(glm::vec3(0.0, 0.0, 0.0));
	this->colors.push_back(glm::vec4(this->normalizeColors(126, 154, 80), 0.2));
	for (t; t < 2 * PI; t += step)
	{
		this->vertices.push_back(glm::vec3(cos(t), sin(t), 0.0));
		this->colors.push_back(glm::vec4(this->normalizeColors(126, 154, 80), 1.0));
	}
	this->nv = this->vertices.size();
}

void ShadowTree::drawModel() {
	glBindVertexArray(this->VAO);

	glm::mat4 mat = glm::mat4(1.0);
	mat = glm::translate(mat, glm::vec3(this->posX, this->posY + 70, 1.0));
	mat = glm::scale(mat, glm::vec3(this->scaleX, this->scaleY, 1.0));


	this->setModelMatrix(mat);

	glUniformMatrix4fv(modelMatrixPTR, 1, GL_FALSE, glm::value_ptr(this->getModelMatrix()));

	glDrawArrays(GL_TRIANGLE_FAN, 0, this->getNumVertices());
}

void ShadowTree::setInfo(float posX, float posY, float scaleX, float scaleY) {

	this->posX = posX;
	this->posY = posY;
	this->scaleX = scaleX;
	this->scaleY = scaleY;
}

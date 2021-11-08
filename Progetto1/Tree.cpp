#pragma once
#include "Tree.hpp"

Tree::Tree(int triangles, bool isBackground) : Model(triangles) {
	this->isBackground = isBackground;
    this->posX = this->posY = this->scaleX = this->scaleY = 0.0;
}

void Tree::buildModel() {

    glm::vec4 color;

    this->isBackground ? color = glm::vec4(this->normalizeColors(150, 202, 198), 1.0) : color = glm::vec4(this->normalizeColors(120, 35, 68), 1.0);

    for (float i = 0; i < 1; i += 0.01)
    {
        this->vertices.push_back(glm::vec3(i, exp(i) - 1, 0.0));
        this->colors.push_back(glm::vec4(color));
        this->vertices.push_back(glm::vec3(i, 0.0, 0.0));
        this->colors.push_back(glm::vec4(color));
    }

    for (float i = 0; i < 1; i += 0.01)
    {
        this->vertices.push_back(glm::vec3(1 + i, exp(1 - i) - 1, 0.0));
        this->colors.push_back(glm::vec4(color));
        this->vertices.push_back(glm::vec3(1 + i, 0.0, 0.0));
        this->colors.push_back(glm::vec4(color));
    }
    this->nv = this->vertices.size();
}

void Tree::drawModel() {
	glBindVertexArray(this->VAO);

	glm::mat4 mat = glm::mat4(1.0);
    mat = glm::translate(mat, glm::vec3(this->posX, this->posY + 70, 1.0));
	mat = glm::scale(mat, glm::vec3(this->scaleX, this->scaleY, 0.0));

	this->setModelMatrix(mat);

	glUniformMatrix4fv(modelMatrixPTR, 1, GL_FALSE, glm::value_ptr(this->getModelMatrix()));

	glDrawArrays(GL_TRIANGLE_STRIP, 0, this->getNumVertices());
}

void Tree::setInfo(float posX, float posY, float scaleX, float scaleY) {
    this->posX = posX;
    this->posY = posY;
    this->scaleX = scaleX;
    this->scaleY = scaleY;
}
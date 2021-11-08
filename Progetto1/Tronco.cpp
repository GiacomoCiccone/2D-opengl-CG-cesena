#pragma once
#include "Tronco.hpp"

Tronco::Tronco(int triangles) : Model(triangles) {
    this->posX = this->posY = this->scaleX = this->scaleY = 0.0;
}

void Tronco::buildModel() {

    this->vertices.insert(this->vertices.end(), { glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0), glm::vec3(1.0, 1.0, 0.0) });
    this->colors.insert(this->colors.end(),
        { glm::vec4(this->normalizeColors(58, 32, 71), 1.0), glm::vec4(this->normalizeColors(58, 32, 71), 1.0), glm::vec4(this->normalizeColors(58, 32, 71), 1.0), glm::vec4(this->normalizeColors(58, 32, 71), 1.0) });
    this->nv = 4;
}

void Tronco::drawModel() {
    glBindVertexArray(this->VAO);

    glm::mat4 mat = glm::mat4(1.0);
    mat = glm::translate(mat, glm::vec3(this->posX, this->posY + 70, 1.0));
    mat = glm::scale(mat, glm::vec3(this->scaleX, this->scaleY, 0.0));

    this->setModelMatrix(mat);

    glUniformMatrix4fv(modelMatrixPTR, 1, GL_FALSE, glm::value_ptr(this->getModelMatrix()));

    glDrawArrays(GL_TRIANGLE_STRIP, 0, this->getNumVertices());
}

void Tronco::setInfo(float posX, float posY, float scaleX, float scaleY) {
    this->posX = posX;
    this->posY = posY;
    this->scaleX = scaleX;
    this->scaleY = scaleY;
}
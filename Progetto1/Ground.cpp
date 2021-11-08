#pragma once
#include "Ground.hpp"

Ground::Ground(int triangles, bool isOutline) : Model(triangles) {
    this->isOutline = isOutline;
}

void Ground::buildModel() {
    glm::vec4 color;
    this->isOutline ? color = glm::vec4(this->normalizeColors(43, 65, 26), 1.0) : color = glm::vec4(this->normalizeColors(145, 177, 94), 1.0);

    this->vertices.insert(this->vertices.end(), { glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0), glm::vec3(1.0, 1.0, 0.0) });
    this->colors.insert(this->colors.end(), { glm::vec4(color), glm::vec4(color), glm::vec4(color), glm::vec4(color) });

    this->nv = 4;
}

void Ground::drawModel() {
    glBindVertexArray(this->VAO);

    glm::mat4 mat = glm::mat4(1.0);
    mat = glm::translate(mat, glm::vec3(0, 0, 1.0));
    this->isOutline ? mat = glm::scale(mat, glm::vec3(SCR_WIDTH, 67, 1.0)) : mat = glm::scale(mat, glm::vec3(SCR_WIDTH, 60, 1.0));

    this->setModelMatrix(mat);

    glUniformMatrix4fv(modelMatrixPTR, 1, GL_FALSE, glm::value_ptr(this->getModelMatrix()));

    glDrawArrays(GL_TRIANGLE_STRIP, 0, this->getNumVertices());
}
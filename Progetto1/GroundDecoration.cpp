#pragma once
#include "GroundDecoration.hpp"

GroundDecoration::GroundDecoration(int triangles, bool isOutline) : Model(triangles) {
    this->isOutline = isOutline;
    this->posX = this->posY = 0.0;
}

void GroundDecoration::buildModel() {
    glm::vec4 color;
    this->isOutline ? color = glm::vec4(this->normalizeColors(41, 66, 27), 1.0) : color = glm::vec4(this->normalizeColors(126, 153, 82), 1.0);
    float t = 0;
    float step = 1.0 / 1000.f;
    for (t; t < 10.f; t += step)
    {
        if (this->isOutline)
        {
            if (cos(120 * t) < 0)
            {
                this->vertices.push_back(glm::vec3(t, (exp(cos(120 * t)) - 1 / NEPER) / 5 + 0.5 + (1 - abs(cos(120 * t))) * 0.1 + abs(cos(120 * t)) * 0.1, 0.0));
            }
            else {
                this->vertices.push_back(glm::vec3(t, (exp(cos(120 * t)) - 1 / NEPER) / 5 + 0.5 + (1 - abs(cos(120 * t))) * 0.1 + abs(cos(120 * t)) * 0.05, 0.0));
            }
        }
        else {
            this->vertices.push_back(glm::vec3(t, (exp(cos(120 * t)) - 1 / NEPER) / 5 + 0.5, 0.0));
        }
        
        this->colors.push_back(glm::vec4(color));
        this->vertices.push_back(glm::vec3(t, 0, 0.0));
        this->colors.push_back(glm::vec4(color));
    }
    this->nv = this->vertices.size();
}


void GroundDecoration::drawModel() {
    glBindVertexArray(this->VAO);

    glm::mat4 mat = glm::mat4(1.0);
    mat = glm::translate(mat, glm::vec3(this->posX, this->posY, 1.0));
    mat = glm::scale(mat, glm::vec3(SCR_WIDTH, 50, 0.0));

    this->setModelMatrix(mat);

    glUniformMatrix4fv(modelMatrixPTR, 1, GL_FALSE, glm::value_ptr(this->getModelMatrix()));

    glDrawArrays(GL_TRIANGLE_STRIP, 0, this->getNumVertices());
}

void GroundDecoration::setInfo(float posX, float posY) {
    this->posX = posX;
    this->posY = posY;
}
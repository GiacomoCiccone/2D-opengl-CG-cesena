#pragma once
#include "Grass.hpp"

extern noise::module::Perlin myModule;

Grass::Grass(int triangles) : Model(triangles) {
    this->posX = this->posY = 0.0;
}

void Grass::buildModel() {

    glm::vec4 color = glm::vec4(this->normalizeColors(76, 115, 62), 1.0);

    float t = 0;
    float step = 1.0 / 1000.f;
    for (t; t < 10.f; t += step)
    {
        myModule.SetOctaveCount(1);
        myModule.SetFrequency(8000);
        float value = myModule.GetValue(t / 10, 1-t/10, 0);
        this->vertices.push_back(glm::vec3(t, abs(value) / 8.0 + pow(sin(t * 0.5), 4) / 10 + 0.15, 0.0));
        this->colors.push_back(glm::vec4(color));
        this->vertices.push_back(glm::vec3(t, 0, 0.0));
        this->colors.push_back(glm::vec4(color));
    }
    this->nv = this->vertices.size();
}

void Grass::drawModel() {
    glBindVertexArray(this->VAO);

    glm::mat4 mat = glm::mat4(1.0);
    mat = glm::translate(mat, glm::vec3(this->posX, this->posY, 1.0));
    mat = glm::scale(mat, glm::vec3(SCR_WIDTH, 220, 0.0));

    this->setModelMatrix(mat);

    glUniformMatrix4fv(modelMatrixPTR, 1, GL_FALSE, glm::value_ptr(this->getModelMatrix()));

    glDrawArrays(GL_TRIANGLE_STRIP, 0, this->getNumVertices());
}

void Grass::setInfo(float posX, float posY) {
    this->posX = posX;
    this->posY = posY;
}
#pragma once
#include "Cloud.hpp"

noise::module::Perlin myModule;

Cloud::Cloud(int triangles) : Model(triangles) {
    for (int i = 0; i < 150; i++)
    {
        this->offset2.push_back(i * 700);
    }
}

void Cloud::buildModel() {
    float t = 0;
    float step = 1.0 / 1000.f;
    for (t; t < 1.f; t += step)
    {
        float offsetY;
        t > 0.5f ? offsetY = 1 - t : offsetY = t;
        myModule.SetOctaveCount(2);
        myModule.SetFrequency(1);
        float value = myModule.GetValue(t, t, t);
        this->vertices.push_back(glm::vec3(t, abs(value) + 1.f * offsetY, 0.0));
        this->colors.push_back(glm::vec4(1.0, 1.0, 1.0, 0.9));
        this->vertices.push_back(glm::vec3(t, 0, 0.0));
        this->colors.push_back(glm::vec4(1.0, 1.0, 1.0, 0.4));
    }
    this->nv = this->vertices.size();
}


void Cloud::drawModel() {
    srand(0);

    for (int i = 0; i < 150; i++)
    {
        glBindVertexArray(this->VAO);
        glm::mat4 mat = glm::mat4(1.0);
        float value = (double)rand() / RAND_MAX + 0.2;
        float width = value * 700;
        float height = value * 180;
        float totalOffset = this->offset + this->offset2.at(i);
        
        mat = glm::translate(mat, glm::vec3(totalOffset, SCR_HEIGHT - height - value * 150, 1.0));
        mat = glm::scale(mat, glm::vec3(width, height, 1.0));

        this->setModelMatrix(mat);

        glUniformMatrix4fv(modelMatrixPTR, 1, GL_FALSE, glm::value_ptr(this->getModelMatrix()));

        glDrawArrays(GL_TRIANGLE_STRIP, 0, this->getNumVertices());

        this->offset2.at(i) -= 0.5 * value;
        if (this->offset2.at(i) < 0 && abs(this->offset2.at(i)) > width)
        {
            this->offset2.at(i) = SCR_WIDTH * 5 + i * 700;
        }
    }

	
}

void Cloud::updateOffset(float delta) {
    if (this->offset + delta <= 0 && abs(this->offset + delta) <= SCR_WIDTH * 5/4)
    {
        this->offset += delta;
    }
}
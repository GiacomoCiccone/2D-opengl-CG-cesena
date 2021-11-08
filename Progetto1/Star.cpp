#pragma once
#include "Star.hpp"

Star::Star(int triangles) : Model(triangles) {
	this->posx = this->posy = 0.0;
	this->type = false;
}

void Star::buildModel() {
	int i;
	float stepA = (2 * PI) / this->nTriangles;
	float t;

	this->vertices.clear();
	this->colors.clear();

	this->vertices.push_back(glm::vec3(0.0, 0.0, 0.0));

	this->colors.push_back(glm::vec4(color));

	for (i = 0; i <= this->nTriangles; i++)
	{
		t = (float)i * stepA;

		if (i % 2 == 0)
			this->vertices.push_back(glm::vec3(cos(t), sin(t), 0.0));
		else
			this->vertices.push_back(glm::vec3(0.5 * cos(t), 0.5 * sin(t), 0.0));
		//Colore 
		this->colors.push_back(glm::vec4(color));


	}
	this->nv = this->vertices.size();
}

void Star::drawModel() {

	static float angle = 0.0;

	glBindVertexArray(this->VAO);

	glm::mat4 mat = glm::mat4(1.0);
	type == true ? mat = glm::translate(mat, glm::vec3(this->posx + this->offset, this->posy, 1.0)) : mat = glm::translate(mat, glm::vec3(this->posx , this->posy, 1.0));
	type == true ? mat = glm::rotate(mat, glm::radians(angle += 0.1), glm::vec3(0.0, 0.0, 1.0)) : mat = mat;
	type == true ? mat = glm::scale(mat, glm::vec3(40, 40, 1.0)) : mat = glm::scale(mat, glm::vec3(15, 15, 1.0));
	


	this->setModelMatrix(mat);

	glUniformMatrix4fv(modelMatrixPTR, 1, GL_FALSE, glm::value_ptr(this->getModelMatrix()));

	glDrawArrays(GL_TRIANGLE_FAN, 0, this->getNumVertices());
}

void Star::setPos(float x, float y)
{
	this->posx = x;
	this->posy = y;
}

void Star::setColor(glm::vec4 col)
{
	this->color = glm::vec4(this->normalizeColors(col.r, col.g, col.b), col.a);
}

void Star::setType(bool type)
{
	this->type = type;
}

void Star::updateOffset(float delta) {
	if (this->offset + delta <= 0 && abs(this->offset + delta) <= SCR_WIDTH * 5)
	{
		this->offset += delta;
	}
}
#pragma once
#include "MountainBG.hpp"

MountainBG::MountainBG(int triangles) : Model(triangles) {
}

void MountainBG::buildModel() {

	this->readFile("Montagna2.json");

	float n = this->pointsToInterpolate.size();
	float max = this->pointsToInterpolate[n - 1].x;

	for (int i = 1; i <= 20; i++)
	{
		for (int j = this->pointsToInterpolate.size() - 2; j >= this->pointsToInterpolate.size() - n - 1; j--) {
			this->pointsToInterpolate.push_back(glm::vec3(max + (max - this->pointsToInterpolate[j].x), this->pointsToInterpolate[j].y, 0.0));
		}
		max = this->pointsToInterpolate[this->pointsToInterpolate.size() - 1].x;
	}

	glm::vec4 color;
	color = glm::vec4(this->normalizeColors(150, 202, 198), 1.0);

	float* t = new float[this->pointsToInterpolate.size()];
	int i;
	float step = 1.0 / (float)(this->pointsToInterpolate.size() - 1);
	float passotg = 1.f / (this->nTriangles - 1);
	float tg, tgmapp, ampiezza, x, y;
	int is = 0;

	for (i = 0; i < this->pointsToInterpolate.size(); i++) {
		t[i] = float(i) * step;
	}

	for (tg = 0; tg <= 1; tg += passotg)
	{
		if (tg > t[is + 1]) is++;
		ampiezza = (t[is + 1] - t[is]);
		tgmapp = (tg - t[is]) / ampiezza;
		x = this->pointsToInterpolate[is].x * PHI0(tgmapp) + this->getDx(is, t) * (float)PHI1(tgmapp) * ampiezza + this->pointsToInterpolate[is + 1].x * PSI0(tgmapp) + this->getDx(is + 1, t) * (float)PSI1(tgmapp) * ampiezza;
		y = this->pointsToInterpolate[is].y * PHI0(tgmapp) + this->getDy(is, t) * (float)PHI1(tgmapp) * ampiezza + this->pointsToInterpolate[is + 1].y * PSI0(tgmapp) + this->getDy(is + 1, t) * (float)PSI1(tgmapp) * ampiezza;
		this->vertices.push_back(glm::vec3(x, y, 0.f));
		this->colors.push_back(glm::vec4(color));
		this->vertices.push_back(glm::vec3(x, 0, 0.f));
		this->colors.push_back(glm::vec4(color));
	}

	this->nv = this->vertices.size();
}

void MountainBG::drawModel() {
	glBindVertexArray(this->VAO);

	glm::mat4 mat = glm::mat4(1.0);
	mat = glm::translate(mat, glm::vec3(offset, 70, 1.0));
	mat = glm::scale(mat, glm::vec3(SCR_WIDTH, SCR_HEIGHT, 1.0));
	this->setModelMatrix(mat);

	glUniformMatrix4fv(modelMatrixPTR, 1, GL_FALSE, glm::value_ptr(this->getModelMatrix()));

	glDrawArrays(GL_TRIANGLE_STRIP, 0, this->getNumVertices());
}

void MountainBG::updateOffset(float delta) {
	if (this->offset + delta <= 0 && abs(this->offset + delta) <= SCR_WIDTH * 2.5)
	{
		this->offset += delta;
	}
}
#pragma once
#include "MountainFG.hpp"

MountainFG::MountainFG(int triangles, bool isOutline) : Model(triangles) {
	srand(time(0));
	this->isOutline = isOutline;
	this->tree = new Tree(0, false);
	this->tronco = new Tronco(2);
	this->grass = new Grass(0);
	this->groundDecoration = new GroundDecoration(0, false);
	this->groundDecorationOutline = new GroundDecoration(0, true);

	this->groundModel = new Ground(0, false);

	this->groundModelOutline = new Ground(0, true);

	this->shadowTree = new ShadowTree(100);
	
}

void MountainFG::buildModel() {

	this->readFile("Montagna1.json");

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
	this->isOutline ? color = glm::vec4(this->normalizeColors(157, 188, 101), 1.0) : color = glm::vec4(this->normalizeColors(126, 154, 80), 1.0);

	float* t = new float[this->pointsToInterpolate.size()];
	int i;
	float step = 1.0 / (float)(this->pointsToInterpolate.size() - 1);
	float passotg = 1.f / (this->nTriangles * 20 - 1);
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

	this->tree->buildModel();
	this->tree->initVAO();
	if (!this->isOutline)
	{
		for (int i = 0; i < this->pointsToInterpolate.size(); i++) {
			this->offsetsTree.push_back(((double)rand() / (RAND_MAX)));
		}
	}
	this->tronco->buildModel();
	this->tronco->initVAO();

	this->grass->buildModel();
	this->grass->initVAO();

	this->groundDecoration->buildModel();
	this->groundDecoration->initVAO();

	this->groundDecorationOutline->buildModel();
	this->groundDecorationOutline->initVAO();

	this->groundModel->buildModel();
	this->groundModel->initVAO();

	this->groundModelOutline->buildModel();
	this->groundModelOutline->initVAO();

	this->shadowTree->buildModel();
	this->shadowTree->initVAO();
}

void MountainFG::drawModel() {
	glm::mat4 mat = glm::mat4(1.0);

	if (!this->isOutline)
	{

		this->groundDecoration->setInfo(this->offset, 0);
		this->groundDecoration->drawModel();

		this->groundDecorationOutline->setInfo(this->offset, 0);
		this->groundDecorationOutline->drawModel();

		this->groundModel->drawModel();
		this->groundModelOutline->drawModel();

		this->grass->setInfo(this->offset, 60);
		this->grass->drawModel();

		for (int i = 0; i < this->pointsToInterpolate.size(); i++) {
			float offset = this->offsetsTree[i];
			float computedHeight = 0;
			if (i % 4 == 0)
			{
				for (int j = 4; j >= 1; j--) {

					float height = offset *  j * 20 + 20;
					float width = offset * j * 20 + 20;
					this->tree->setInfo(this->offset + this->pointsToInterpolate[i].x * SCR_WIDTH - width, this->pointsToInterpolate[i].y * SCR_HEIGHT + computedHeight - (offset / 2 * this->pointsToInterpolate[i].y * SCR_HEIGHT), width, height);
					this->tree->drawModel();
					computedHeight += height;

					if (j == 4)
					{
						this->tronco->setInfo(this->offset +  this->pointsToInterpolate[i].x * SCR_WIDTH, this->pointsToInterpolate[i].y * SCR_HEIGHT - (offset / 2 * this->pointsToInterpolate[i].y * SCR_HEIGHT) - 20 * offset, width / 10, 30);
						this->tronco->drawModel();

						this->shadowTree->setInfo(this->offset + this->pointsToInterpolate[i].x * SCR_WIDTH, this->pointsToInterpolate[i].y * SCR_HEIGHT - (offset / 2 * this->pointsToInterpolate[i].y * SCR_HEIGHT) - 20 * offset,
							width, height / 5);
						this->shadowTree->drawModel();
					}
				}
			}
		}

		
	}

	glBindVertexArray(this->VAO);
	mat = glm::mat4(1.0);
	this->isOutline ? mat = glm::translate(mat, glm::vec3(offset, 85, 1.0)) : mat = glm::translate(mat, glm::vec3(offset, 70, 1.0));
	mat = glm::scale(mat, glm::vec3(SCR_WIDTH, SCR_HEIGHT, 1.0));
	this->setModelMatrix(mat);

	glUniformMatrix4fv(modelMatrixPTR, 1, GL_FALSE, glm::value_ptr(this->getModelMatrix()));

	glDrawArrays(GL_TRIANGLE_STRIP, 0, this->getNumVertices());
}

void MountainFG::updateOffset(float delta) {
	if (this->offset + delta <= 0 && abs(this->offset + delta) <= SCR_WIDTH * 5)
	{
		this->offset += delta;
	}
}

float* MountainFG::getOffset()
{
	return &this->offset;
}

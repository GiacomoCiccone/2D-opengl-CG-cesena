#pragma once

#include "Model.hpp"
#include "Eyes.hpp"
#include "Mouth.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "constant.hpp"
#include <iostream>


extern GLuint modelMatrixPTR;

class Ball : public Model {
public:
	Ball(int nTriangles);
	void buildModel();
	void drawModel();
	void setPos(float x, float y);
	Eyes* getEyes();
	Mouth* getMouth();
	void setColor(glm::vec4 col);
private:
	float posx, posy, oldPosx;
	Eyes* eyes;
	Mouth* mouth;
	glm::vec4 color;
};

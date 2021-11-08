#pragma once

#include "Model.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "constant.hpp"
#include <iostream>


extern GLuint modelMatrixPTR;

class Mouth : public Model {
public:
	Mouth(int nTriangles);
	void buildModel();
	void drawModel();
	void setPos(float x, float y);
	void updateAngle(float delta);
private:
	float posx, posy, angle;
};

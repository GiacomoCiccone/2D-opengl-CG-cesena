#pragma once

#include "Model.hpp"
#include <noise/noise.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "constant.hpp"
#include <iostream>


extern GLuint modelMatrixPTR;

class GroundDecoration : public Model {
public:
	GroundDecoration(int nTriangles, bool isOutline);
	void buildModel();
	void drawModel();
	void setInfo(float posX, float posY);
private:
	bool isOutline;
	float posX, posY;
	float offset;
};
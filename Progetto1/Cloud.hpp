#pragma once

#include "Model.hpp"
#include <glm/glm.hpp>
#include <noise/noise.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "constant.hpp"
#include <iostream>

extern GLuint modelMatrixPTR;

class Cloud : public Model {
public:
	Cloud(int nTriangles);
	void buildModel();
	void drawModel();
	void updateOffset(float delta);
	std::vector<float> offset2;
};

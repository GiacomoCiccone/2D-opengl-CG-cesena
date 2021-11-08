#pragma once

#include "Model.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "constant.hpp"
#include <iostream>


extern GLuint modelMatrixPTR;

class MountainBG : public Model {
public:
	MountainBG(int nTriangles);
	void buildModel();
	void drawModel();
	void updateOffset(float delta);


};
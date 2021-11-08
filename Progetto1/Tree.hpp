#pragma once

#include "Model.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "constant.hpp"
#include <iostream>


extern GLuint modelMatrixPTR;

class Tree : public Model {
public:
	Tree(int nTriangles, bool isBackground);
	void buildModel();
	void drawModel();
	void setInfo(float posX, float posY, float scaleX, float scaleY);
private:
	float posX, posY, scaleX, scaleY;
	bool isBackground;
	float offset;
};

#pragma once

#include "Model.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "constant.hpp"
#include <iostream>


extern GLuint modelMatrixPTR;

class Star : public Model {
public:
	Star(int nTriangles);
	void buildModel();
	void drawModel();
	void setPos(float x, float y);
	void updateOffset(float delta);
	void setColor(glm::vec4 col);
	void setType(bool type);

private:
	float posx, posy;
	glm::vec4 color;
	bool type;
};

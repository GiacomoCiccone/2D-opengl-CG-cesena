#pragma once

#include "Model.hpp"
#include "Tree.hpp"
#include "Tronco.hpp"
#include "Grass.hpp"
#include "Ground.hpp"
#include "GroundDecoration.hpp"
#include "ShadowTree.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "constant.hpp"
#include <iostream>
#include <random>


extern GLuint modelMatrixPTR;

class MountainFG : public Model {
public:
	MountainFG(int nTriangles, bool isOutline);
	void buildModel();
	void drawModel();
	void updateOffset(float delta);
	float* getOffset();
private:
	bool isOutline;
	Tree* tree;
	Tronco* tronco;
	Grass* grass;
	GroundDecoration* groundDecoration, *groundDecorationOutline;
	Ground* groundModel, * groundModelOutline;
	ShadowTree* shadowTree;
	std::vector<float> offsetsTree;
	
};
#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <direct.h>
#include "json.hpp"
#include "constant.hpp"

using json = nlohmann::json;

class Model {
public:
	//constructor
	Model(int triangles);
	//This function init the VAO for the model
	void initVAO();
	//This function build the model and depends on the type of the model
	virtual void buildModel() = 0;
	//this function draw the model by the data in his VAO
	virtual void drawModel() = 0;

protected:
	GLuint VAO;
	GLuint VBO_P;	//position buffer
	GLuint VBO_C;	//color buffer
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec4> colors;
	std::vector<glm::vec3> pointsToInterpolate;
	float tens, bias, cont;
	int nv;			//vertices
	int nTriangles;	//triangles
	glm::mat4 modelMatrix;
	float offset;

	glm::vec3 normalizeColors(float r, float g, float b);

	//setters
	void setModelMatrix(glm::mat4 mat);
	//read model file if is an external json model
	void readFile(std::string path);

	//getters
	GLuint getVAO();
	int getNumVertices();
	glm::mat4 getModelMatrix();
	float getDx(int i, float* t);
	float getDy(int i, float* t);

};
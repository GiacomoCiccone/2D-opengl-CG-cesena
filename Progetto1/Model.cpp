#include "Model.hpp"

Model::Model(int triangles)
{
	this->nTriangles = triangles;
	this->modelMatrix = glm::mat4(1.0);
	this->VAO = 0;
	this->VBO_C = 0;
	this->VBO_P = 0;
	this->nv = 0;
	this->bias = 0.0;
	this->cont = 0.0;
	this->tens = 0.0;
	this->offset = 0.0;
}

void Model::initVAO()
{
	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);
	//Genero , rendo attivo, riempio il VBO della geometria dei vertici
	glGenBuffers(1, &this->VBO_P);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO_P);
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(glm::vec3), this->vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	//Genero , rendo attivo, riempio il VBO dei colori
	glGenBuffers(1, &this->VBO_C);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO_C);
	glBufferData(GL_ARRAY_BUFFER, this->colors.size() * sizeof(glm::vec4), this->colors.data(), GL_STATIC_DRAW);
	//Adesso carico il VBO dei colori nel layer 2
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);
}

void Model::setModelMatrix(glm::mat4 mat) {
	this->modelMatrix = mat;
}

GLuint Model::getVAO() {
	return this->VAO;
}

int  Model::getNumVertices() {
	return this->nv;
}

glm::mat4  Model::getModelMatrix() {
	return this->modelMatrix;
}

glm::vec3 Model::normalizeColors(float r, float g, float b) {
	return glm::vec3(r / 255.0, g / 255.0, b / 255.0);
}

void Model::readFile(std::string path) {

	try
	{
		std::ifstream i(path);
		json j;
		i >> j;

		for (int i = 0; i < j["vertices"].size(); i++)
		{
			this->pointsToInterpolate.push_back(glm::vec3(j["vertices"].at(i)[0], j["vertices"].at(i)[1], 0.0));
		}

		this->bias = j["parameters"]["Bias"];
		this->tens = j["parameters"]["Tension"];
		this->cont = j["parameters"]["Continuity"];

	}
	catch (const std::exception&)
	{
		std::cout << "Impossibile aprire il file " << path << std::endl;
	}
}

float Model::getDx(int i, float* t) {
	if (i == 0)
		return  0.5 * (1 - this->tens) * (1 - this->bias) * (1 - this->cont) * (this->pointsToInterpolate[i + 1].x - this->pointsToInterpolate[i].x) / (t[i + 1] - t[i]);
	if (i == this->pointsToInterpolate.size() - 1)
		return  0.5 * (1 - this->tens) * (1 - this->bias) * (1 - this->cont) * (this->pointsToInterpolate[i].x - this->pointsToInterpolate[i - 1].x) / (t[i] - t[i - 1]);

	if (i % 2 == 0)
		return  0.5 * (1 - this->tens) * (1 + this->bias) * (1 + this->cont) * (this->pointsToInterpolate.at(i).x - this->pointsToInterpolate.at(i - 1).x) / (t[i] - t[i - 1]) + 0.5 * (1 - this->tens) * (1 - this->bias) * (1 - this->cont) * (this->pointsToInterpolate.at(i + 1).x - this->pointsToInterpolate.at(i).x) / (t[i + 1] - t[i]);
	else
		return  0.5 * (1 - this->tens) * (1 + this->bias) * (1 - this->cont) * (this->pointsToInterpolate.at(i).x - this->pointsToInterpolate.at(i - 1).x) / (t[i] - t[i - 1]) + 0.5 * (1 - this->tens) * (1 - this->bias) * (1 + this->cont) * (this->pointsToInterpolate.at(i + 1).x - this->pointsToInterpolate.at(i).x) / (t[i + 1] - t[i]);
}

float Model::getDy(int i, float* t) {
	if (i == 0)
		return  0.5 * (1 - this->tens) * (1 - this->bias) * (1 - this->cont) * (this->pointsToInterpolate[i + 1].y - this->pointsToInterpolate[i].y) / (t[i + 1] - t[i]);
	if (i == this->pointsToInterpolate.size() - 1)
		return  0.5 * (1 - this->tens) * (1 - this->bias) * (1 - this->cont) * (this->pointsToInterpolate[i].y - this->pointsToInterpolate[i - 1].y) / (t[i] - t[i - 1]);

	if (i % 2 == 0)
		return  0.5 * (1 - this->tens) * (1 + this->bias) * (1 + this->cont) * (this->pointsToInterpolate.at(i).y - this->pointsToInterpolate.at(i - 1).y) / (t[i] - t[i - 1]) + 0.5 * (1 - this->tens) * (1 - this->bias) * (1 - this->cont) * (this->pointsToInterpolate.at(i + 1).y - this->pointsToInterpolate.at(i).y) / (t[i + 1] - t[i]);
	else
		return  0.5 * (1 - this->tens) * (1 + this->bias) * (1 - this->cont) * (this->pointsToInterpolate.at(i).y - this->pointsToInterpolate.at(i - 1).y) / (t[i] - t[i - 1]) + 0.5 * (1 - this->tens) * (1 - this->bias) * (1 + this->cont) * (this->pointsToInterpolate.at(i + 1).y - this->pointsToInterpolate.at(i).y) / (t[i + 1] - t[i]);
}
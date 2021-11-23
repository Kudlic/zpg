#include "Model.h"

Model::Model(GLboolean bit, const GLfloat* points, int size, int lineLen, int vecLen, int uniformCount, GLenum mode) {

	this->tex = nullptr;
	pointNo = size / lineLen;
	this->mode = mode;
	vbo = new VBO(points, size);

	int i_top = 0;

	if (uniformCount == 0)
		i_top = lineLen / vecLen;
	else
		i_top = uniformCount;


	vao = new VAO();
	vao->bind();
	for(int i =0; i < i_top; i++){
		vao->linkAttrib(*vbo, i, vecLen, GL_FLOAT, lineLen * sizeof(GL_FLOAT), (GLvoid*)(i* vecLen * sizeof(GL_FLOAT)));
	}
	vao->unbind();
	vbo->unbind();
}
Model::Model(const GLfloat* points, GLint pointNo, GLint lineLen) {
	this->tex = nullptr;
	this->pointNo = pointNo;
	this->lineLen = lineLen;
	this->mode = GL_TRIANGLES;
	vbo = new VBO(points, pointNo * lineLen);
	vao = new VAO();
	vao->bind();
}
Model::Model(const char* modelData) {
	this->tex = nullptr;
	this->mode = GL_TRIANGLES;

	int count = 0;
	Assimp::Importer importer;
	unsigned int importOptions = aiProcess_Triangulate
		| aiProcess_OptimizeMeshes              // slouèení malých plošek
		| aiProcess_JoinIdenticalVertices       // NUTNÉ jinak hodnì duplikuje
		| aiProcess_Triangulate                 // prevod vsech ploch na trojuhelniky
		| aiProcess_CalcTangentSpace;           // vypocet tangenty, nutny pro spravne pouziti normalove mapy
	const aiScene* scene = importer.ReadFile(modelData, importOptions);
	vector<float> data;
	if (scene) {
		aiMesh* mesh = scene->mMeshes[0];
		count = mesh->mNumFaces * 3;
		for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
			for (unsigned int j = 0; j < 3; j++)
			{
				data.push_back(mesh->mVertices[mesh->mFaces[i].mIndices[j]].x);
				data.push_back(mesh->mVertices[mesh->mFaces[i].mIndices[j]].y);
				data.push_back(mesh->mVertices[mesh->mFaces[i].mIndices[j]].z);
				data.push_back(mesh->mNormals[mesh->mFaces[i].mIndices[j]].x);
				data.push_back(mesh->mNormals[mesh->mFaces[i].mIndices[j]].y);
				data.push_back(mesh->mNormals[mesh->mFaces[i].mIndices[j]].z);
				data.push_back(mesh->mTextureCoords[0][mesh->mFaces[i].mIndices[j]].x);
				data.push_back(mesh->mTextureCoords[0][mesh->mFaces[i].mIndices[j]].y);
			}
		}
	}
	vbo = new VBO(data);
	vao = new VAO();
	vao->bind();

	this->pointNo = data.size()/8;
	this->lineLen = 8;
}
ModelBuilder Model::create(const GLfloat* points, GLint pointNo, GLint lineLen) {
	return ModelBuilder(points, pointNo, lineLen);
}
ModelBuilder Model::create(const char* modelData) {
	return ModelBuilder(modelData);
}

VAO* Model::getVAO() {
	return vao;
}

VBO* Model::getVBO() {
	return vbo;
}
int Model::getPointNo() {
	return pointNo;
}
GLenum Model::getMode() {
	return mode;
}
void Model::bindTexture(Texture* tex) {
	this->tex = tex;
}

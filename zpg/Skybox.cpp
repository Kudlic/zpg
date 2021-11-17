#include "Skybox.h"
#include "Models/plain.h"

Skybox::Skybox(ShaderProg* sp) {
	initialised = 0;

	Model* bottom = Model::create(plain, 6, 8).positionAttrib(0).texAttrib(6).build();
	Texture* tex1 = new TextureRGB("./Textures/negy.jpg", 0);
	bottom->bindTexture(tex1);

	Model* top = Model::create(plain, 6, 8).positionAttrib(0).texAttrib(6).build();
	Texture* tex2 = new TextureRGB("./Textures/posy.jpg", 0);
	top->bindTexture(tex2);

	Model* left = Model::create(plain, 6, 8).positionAttrib(0).texAttrib(6).build();
	Texture* tex3 = new TextureRGB("./Textures/negx.jpg", 0);
	left->bindTexture(tex3);

	Model* right = Model::create(plain, 6, 8).positionAttrib(0).texAttrib(6).build();
	Texture* tex4 = new TextureRGB("./Textures/posx.jpg", 0);
	right->bindTexture(tex4);

	Model* front = Model::create(plain, 6, 8).positionAttrib(0).texAttrib(6).build();
	Texture* tex5 = new TextureRGB("./Textures/negz.jpg", 0);
	front->bindTexture(tex5);

	Model* back = Model::create(plain, 6, 8).positionAttrib(0).texAttrib(6).build();
	Texture* tex6 = new TextureRGB("./Textures/posz.jpg", 0);
	back->bindTexture(tex6);

	this->sides[0] = Object(bottom, sp);
	MatrixHandler::translate( (&this->sides[0])->getMatRef(), glm::vec3(0.0f, -1.0f, .0f));
	MatrixHandler::rotate	((&this->sides[0])->getMatRef(), glm::radians(-90.f), glm::vec3(0.0f, 1.f, .0f));
	this->sides[1] = Object(top, sp);
	MatrixHandler::translate((&this->sides[1])->getMatRef(), glm::vec3(0.0f, 1.0f, .0f));
	MatrixHandler::rotate	((&this->sides[1])->getMatRef(), glm::radians(-90.f), glm::vec3(0.0f, 1.f, .0f));

	this->sides[2] = Object(left, sp);
	MatrixHandler::translate((&this->sides[2])->getMatRef(), glm::vec3(-1.0f, .0f, .0f));
	MatrixHandler::rotate	((&this->sides[2])->getMatRef(), glm::radians(180.f), glm::vec3(1.0f, .0f, .0f));
	MatrixHandler::rotate	((&this->sides[2])->getMatRef(), glm::radians(-90.f), glm::vec3(0.0f, .0f, -1.0f));
	this->sides[3] = Object(right, sp);
	MatrixHandler::translate((&this->sides[3])->getMatRef(), glm::vec3(1.0f, .0f, .0f));
	MatrixHandler::rotate	((&this->sides[3])->getMatRef(), glm::radians(90.f), glm::vec3(0.0f, .0f, -1.0f));
	this->sides[4] = Object(front, sp);
	MatrixHandler::translate((&this->sides[4])->getMatRef(), glm::vec3(.0f, .0f, -1.0f));
	MatrixHandler::rotate	((&this->sides[4])->getMatRef(), glm::radians(90.f), glm::vec3(0.0f, 1.0f, .0f));
	MatrixHandler::rotate	((&this->sides[4])->getMatRef(), glm::radians(-90.f), glm::vec3(.0f, .0f, 1.0f));
	this->sides[5] = Object(back, sp);
	MatrixHandler::translate((&this->sides[5])->getMatRef(), glm::vec3(.0f, .0f, 1.0f));
	MatrixHandler::rotate	((&this->sides[5])->getMatRef(), glm::radians(90.f), glm::vec3(1.0f, .0f, .0f));
	MatrixHandler::rotate	((&this->sides[5])->getMatRef(), glm::radians(-90.f), glm::vec3(0.0f, 1.0f, .0f));

}
void Skybox::draw() {

	for (int i = 0; i < 6; i++) {
		this->sides[i].draw();
	}
	glClear(GL_DEPTH_BUFFER_BIT);
}

void Skybox::update(glm::vec3 position) {
	if (!initialised) {
		this->position = position;

		MatrixHandler::rotate((&this->sides[0])->getMatRef(), glm::radians(90.f), glm::vec3(0.0f, 1.f, .0f));
		MatrixHandler::translate((&this->sides[0])->getMatRef(), position);
		MatrixHandler::rotate((&this->sides[0])->getMatRef(), glm::radians(-90.f), glm::vec3(0.0f, 1.f, .0f));

		MatrixHandler::rotate((&this->sides[1])->getMatRef(), glm::radians(90.f), glm::vec3(0.0f, 1.f, .0f));
		MatrixHandler::translate((&this->sides[1])->getMatRef(), position);
		MatrixHandler::rotate((&this->sides[1])->getMatRef(), glm::radians(-90.f), glm::vec3(0.0f, 1.f, .0f));

		MatrixHandler::rotate((&this->sides[2])->getMatRef(), glm::radians(90.f), glm::vec3(0.0f, .0f, -1.0f));
		MatrixHandler::rotate((&this->sides[2])->getMatRef(), glm::radians(-180.f), glm::vec3(1.0f, .0f, .0f));
		MatrixHandler::translate((&this->sides[2])->getMatRef(), position);
		MatrixHandler::rotate((&this->sides[2])->getMatRef(), glm::radians(180.f), glm::vec3(1.0f, .0f, .0f));
		MatrixHandler::rotate((&this->sides[2])->getMatRef(), glm::radians(-90.f), glm::vec3(0.0f, .0f, -1.0f));

		MatrixHandler::rotate((&this->sides[3])->getMatRef(), glm::radians(-90.f), glm::vec3(0.0f, .0f, -1.0f));
		MatrixHandler::translate((&this->sides[3])->getMatRef(), position);
		MatrixHandler::rotate((&this->sides[3])->getMatRef(), glm::radians(90.f), glm::vec3(0.0f, .0f, -1.0f));

		MatrixHandler::rotate((&this->sides[4])->getMatRef(), glm::radians(90.f), glm::vec3(.0f, .0f, 1.0f));
		MatrixHandler::rotate((&this->sides[4])->getMatRef(), glm::radians(-90.f), glm::vec3(0.0f, 1.0f, .0f));
		MatrixHandler::translate((&this->sides[4])->getMatRef(), position);
		MatrixHandler::rotate((&this->sides[4])->getMatRef(), glm::radians(90.f), glm::vec3(0.0f, 1.0f, .0f));
		MatrixHandler::rotate((&this->sides[4])->getMatRef(), glm::radians(-90.f), glm::vec3(.0f, .0f, 1.0f));

		MatrixHandler::rotate((&this->sides[5])->getMatRef(), glm::radians(90.f), glm::vec3(0.0f, 1.0f, .0f));
		MatrixHandler::rotate((&this->sides[5])->getMatRef(), glm::radians(-90.f), glm::vec3(1.0f, .0f, .0f));
		MatrixHandler::translate((&this->sides[5])->getMatRef(), position);
		MatrixHandler::rotate((&this->sides[5])->getMatRef(), glm::radians(90.f), glm::vec3(1.0f, .0f, .0f));
		MatrixHandler::rotate((&this->sides[5])->getMatRef(), glm::radians(-90.f), glm::vec3(0.0f, 1.0f, .0f));
		
		this->initialised = 1;
	}

	else {
		MatrixHandler::rotate((&this->sides[0])->getMatRef(), glm::radians(90.f), glm::vec3(0.0f, 1.f, .0f));
		MatrixHandler::translate((&this->sides[0])->getMatRef(), position - this->position);
		MatrixHandler::rotate((&this->sides[0])->getMatRef(), glm::radians(-90.f), glm::vec3(0.0f, 1.f, .0f));

		MatrixHandler::rotate((&this->sides[1])->getMatRef(), glm::radians(90.f), glm::vec3(0.0f, 1.f, .0f));
		MatrixHandler::translate((&this->sides[1])->getMatRef(), position - this->position);
		MatrixHandler::rotate((&this->sides[1])->getMatRef(), glm::radians(-90.f), glm::vec3(0.0f, 1.f, .0f));

		MatrixHandler::rotate((&this->sides[2])->getMatRef(), glm::radians(90.f), glm::vec3(0.0f, .0f, -1.0f));
		MatrixHandler::rotate((&this->sides[2])->getMatRef(), glm::radians(-180.f), glm::vec3(1.0f, .0f, .0f));
		MatrixHandler::translate((&this->sides[2])->getMatRef(), position - this->position);
		MatrixHandler::rotate((&this->sides[2])->getMatRef(), glm::radians(180.f), glm::vec3(1.0f, .0f, .0f));
		MatrixHandler::rotate((&this->sides[2])->getMatRef(), glm::radians(-90.f), glm::vec3(0.0f, .0f, -1.0f));

		MatrixHandler::rotate((&this->sides[3])->getMatRef(), glm::radians(-90.f), glm::vec3(0.0f, .0f, -1.0f));
		MatrixHandler::translate((&this->sides[3])->getMatRef(), position - this->position);
		MatrixHandler::rotate((&this->sides[3])->getMatRef(), glm::radians(90.f), glm::vec3(0.0f, .0f, -1.0f));

		MatrixHandler::rotate((&this->sides[4])->getMatRef(), glm::radians(90.f), glm::vec3(.0f, .0f, 1.0f));
		MatrixHandler::rotate((&this->sides[4])->getMatRef(), glm::radians(-90.f), glm::vec3(0.0f, 1.0f, .0f));
		MatrixHandler::translate((&this->sides[4])->getMatRef(), position - this->position);
		MatrixHandler::rotate((&this->sides[4])->getMatRef(), glm::radians(90.f), glm::vec3(0.0f, 1.0f, .0f));
		MatrixHandler::rotate((&this->sides[4])->getMatRef(), glm::radians(-90.f), glm::vec3(.0f, .0f, 1.0f));

		MatrixHandler::rotate((&this->sides[5])->getMatRef(), glm::radians(90.f), glm::vec3(0.0f, 1.0f, .0f));
		MatrixHandler::rotate((&this->sides[5])->getMatRef(), glm::radians(-90.f), glm::vec3(1.0f, .0f, .0f));
		MatrixHandler::translate((&this->sides[5])->getMatRef(), position - this->position);
		MatrixHandler::rotate((&this->sides[5])->getMatRef(), glm::radians(90.f), glm::vec3(1.0f, .0f, .0f));
		MatrixHandler::rotate((&this->sides[5])->getMatRef(), glm::radians(-90.f), glm::vec3(0.0f, 1.0f, .0f));
		this->position = position;
	}
}

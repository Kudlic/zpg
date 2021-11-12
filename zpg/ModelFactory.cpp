#include "ModelFactory.h"
Model* ModelFactory::premade(ModelType type) {
	switch (type) {
	case ModelType::sphereC:
		return Model::create(sphere, 2880, 6).positionAttrib(0).colorAttrib(3).build();
		break;
	case ModelType::sphereN:
		return Model::create(sphere, 2880, 6).positionAttrib(0).normalAttrib(3).build();
		break;
	case ModelType::plainN:
		return Model::create(plainOld, 6, 6).positionAttrib(0).normalAttrib(3).build();
		break;
	case ModelType::plainNT:
	{
		Model* model = Model::create(plain, 6, 8).positionAttrib(0).normalAttrib(3).texAttrib(6).build();
		Texture* tex = new Texture("./Textures/test.png", 0);
		model->bindTexture(tex);
		return model;
	}
		break;
	case ModelType::suziFlatN:
		Model::create(suziFlat, 2904, 6).positionAttrib(0).normalAttrib(3).build();
		break;
	case ModelType::suziSmoothN:
		Model::create(suziSmooth, 2904, 6).positionAttrib(0).normalAttrib(3).build();
		break;
	case ModelType::giftN:
		Model::create(gift, 66624, 6).positionAttrib(0).normalAttrib(3).build();
		break;
	case ModelType::treeN:
		Model::create(tree, 92814, 6).positionAttrib(0).normalAttrib(3).build();
		break;
	case ModelType::bushN:
		Model::create(bush, 8730, 6).positionAttrib(0).normalAttrib(3).build();
		break;
	}
}
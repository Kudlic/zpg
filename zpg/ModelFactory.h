#pragma once
#include "Model.h"
#include "Models/sphere.h"
#include "Models/suzi_flat.h"
#include "Models/suzi_smooth.h"
#include "Models/bushes.h"
#include "Models/plain.h"
#include "Models/tree.h"
#include "Models/gift.h"

enum class ModelType {
	sphereN,
	sphereC,
	suziFlatN,
	suziSmoothN,
	treeN,
	bushN,
	giftN,
	plainN,
	plainNT,
	houseTextured,
	terrain,
	treeO
};
class ModelFactory
{
public:
	static Model* premade(ModelType type);
};


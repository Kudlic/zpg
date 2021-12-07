#include "Path.h"

int choose(int n, int k) { //n nad k
	if (k == 0)
		return 1;
	else
		return (n * choose(n - 1, k - 1)) / k;
}

Path::Path() {
	this->t = 0.f;
	this->isForward = true;
}
void Path::addWaypoint(glm::vec3 point) {
	this->waypoints.push_back(point);
}
glm::vec3 Path::getNextPoint(float delta) {
	int pointNo = this->waypoints.size() - 1;
	glm::vec3 resPoint = glm::vec3(0.f);

	for (int i = 0; i <= pointNo; i++) {
		float coef = choose(pointNo, i) * pow(t, i) * pow((1-t), pointNo - i);
		//printf("Path coef: %f, IsForward: %d, PointNo: %d, t: %f\n", coef, isForward, pointNo, t);
		resPoint.x += this->waypoints.at(i).x * coef;
		resPoint.y += this->waypoints.at(i).y * coef;
		resPoint.z += this->waypoints.at(i).z * coef;
	}
	if (t > 1.0f || t < 0.0f) {
		isForward = !isForward;
		printf("Reversing resPoint: %f %f %f\n", resPoint.x, resPoint.y, resPoint.z);
		printf("Vector:\n");
		for (int j = 0; j < this->waypoints.size(); j++) {
			printf("\t point: %f %f %f\n", this->waypoints.at(j).x, this->waypoints.at(j).y, this->waypoints.at(j).z);
		}
	}
	if (isForward) t += delta;
	else t -= delta;
	printf("Path resPoint: %f %f %f\n", resPoint.x, resPoint.y, resPoint.z);
	return resPoint;
}

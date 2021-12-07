#pragma once
#include <glm/vec3.hpp>
#include<vector>
class Path
{
private:
	std::vector <glm::vec3> waypoints;
	bool isForward;
	float t;
public:
	Path();
	void addWaypoint(glm::vec3 point);
	glm::vec3 getNextPoint(float delta);
};


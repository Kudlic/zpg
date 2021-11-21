#pragma once
#include "Light.h"
class PointLight :
    public Light
{
protected:
    glm::vec3 position;
    float constant;
    float linear;
    float quadratic;
public:
    PointLight();
    PointLight(glm::vec3 position);
    PointLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 direction);
    void setPositionUni(GLint location);
    void setConstantUni(GLint location);
    void setLinearUni(GLint location);
    void setQuadraticUni(GLint location);
};


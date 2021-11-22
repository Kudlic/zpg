#pragma once
#include "Light.h"
class DirectionalLight :
    public Light
{
protected:
    glm::vec3 direction;
public:
    DirectionalLight();
    DirectionalLight(glm::vec3 direction);
    DirectionalLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 direction);
    void setDirectionUni(GLint location);
    void setDirection(glm::vec3 direction);
};


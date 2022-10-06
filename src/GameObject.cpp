#include <cstdio>
#include <GLFW/glfw3.h> 
#include "../include/GameObject.hpp"

using namespace glm;
GameObject::GameObject(){}

GameObject::GameObject(vec3 position){
    this->position = position;
}

void GameObject::setControlPoints(){
                
    this->p0 = glm::vec4(this->position.x, this->position.y, this->position.z, 1.0f);
    this->p1 = glm::vec4(this->position.x - 1.25f, this->position.y + 1.f, this->position.z + 1.25f, 1.0f);
    this->p2 = glm::vec4(this->position.x + 1.25f, this->position.y - 1.0f, this->position.z + 2.5f, 1.0f);
    this->p3 = glm::vec4(this->position.x - 1.25f, this->position.y + 1.0f, this->position.z + 3.75f, 1.0f);
}

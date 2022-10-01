#include <cstdio>
#include <GLFW/glfw3.h>  // Cria��o de janelas do sistema operacional
#include "sceneObj.hpp"

#define CUBE_SIZE 0.8
#define CUBE_SIZE_RABBIT 0.3
#define PLANE_SIZE_X 20
#define PLANE_SIZE_Z 20

using namespace glm;

SceneObj::SceneObj(int id, vec3 position, bool isRabbit = false){
    this->id = id;
    this->position = position;
    this->isRabbit = isRabbit;
    this->isAlive = true;
}

SceneObj::SceneObj(){
    this->isAlive = true;
}

void SceneObj::setPosition(vec3 position){
    this->position = position;
}


void SceneObj::setControlPoints(){
                
    this->p0 = glm::vec4(this->position.x, this->position.y, this->position.z, 1.0f);
    this->p1 = glm::vec4(this->position.x - 1.25f, this->position.y + 1.f, this->position.z + 1.25f, 1.0f);
    this->p2 = glm::vec4(this->position.x + 1.25f, this->position.y - 1.0f, this->position.z + 2.5f, 1.0f);
    this->p3 = glm::vec4(this->position.x - 1.25f, this->position.y + 1.0f, this->position.z + 3.75f, 1.0f);
}

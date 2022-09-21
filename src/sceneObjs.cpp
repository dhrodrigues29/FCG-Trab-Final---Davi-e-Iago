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

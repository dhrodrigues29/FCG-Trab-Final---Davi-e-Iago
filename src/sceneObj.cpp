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
    this->height = CUBE_SIZE;
    this->width = CUBE_SIZE;
    this->depth = CUBE_SIZE;
    this->hitBoxMax = vec3(0.0f, 0.0f, 0.0f);
    this->hitBoxMin = vec3(0.0f, 0.0f, 0.0f);
    this->isRabbit = isRabbit;
    this->isAlive = true;

    if(isRabbit){
        this->height = CUBE_SIZE_RABBIT;
        this->width = CUBE_SIZE_RABBIT;
        this->depth = CUBE_SIZE_RABBIT;
    }
}

SceneObj::SceneObj(){
    this->height = CUBE_SIZE;
    this->width = CUBE_SIZE;
    this->depth = CUBE_SIZE;
    this->isAlive = true;
}

void SceneObj::setPosition(vec3 position){
    this->position = position;
}

//faz a atualização do ponto máximo e mínimo da hitBox
void SceneObj::updateHitBox(){
    hitBoxMin.x = position.x - width;
    hitBoxMin.y = position.y - height;
    hitBoxMin.z = position.z - depth;
    hitBoxMax.x = position.x + width;
    hitBoxMax.y = position.y + height;
    hitBoxMax.z = position.z + depth;
}

//testa se a hitBox do animal bateu na parede do plano
bool SceneObj::wallColision(){
    if(hitBoxMin.x< -PLANE_SIZE_X+1 || hitBoxMin.x > PLANE_SIZE_Z -1)
        return true;
    if(hitBoxMin.z<-PLANE_SIZE_X +1 || hitBoxMin.z>PLANE_SIZE_Z-1)
        return true;
    if(hitBoxMax.x< -PLANE_SIZE_X+1 || hitBoxMax.x > PLANE_SIZE_Z -1)
        return true;
    if(hitBoxMax.z<-PLANE_SIZE_X +1 || hitBoxMax.z>PLANE_SIZE_Z-1)
        return true;
    return false;
}

//testa se um ponto qualquer esta dentro da hitBox do Animal
//usado para:
// - função de colisão de dois animais (cubeInsideCube)
// - testar se a camera da pessoa (que é um ponto) está colidindo com algum animal
bool SceneObj::pointInsideCube(vec3 point){
    if(point.x>= hitBoxMin.x && point.x <=hitBoxMax.x)
        if(point.y>=hitBoxMin.y && point.y <=hitBoxMax.y)
            if(point.z>=hitBoxMin.z && point.z<=hitBoxMax.z)
                return true;
    return false;
}

//testa se algum dos pontos da hitBox fornecida está dentro da hitBox do Animal
//usado para testar colisão entre dois animais
bool SceneObj::cubeInsideCube(vec3 otherHitBoxMin, vec3 otherHitBoxMax){
    vec3 aux;
    if(pointInsideCube(otherHitBoxMin))
        return true;
    if(pointInsideCube(otherHitBoxMax))
        return true;

    aux = vec3(otherHitBoxMin.x, otherHitBoxMin.y, otherHitBoxMax.z);
    if(pointInsideCube(aux))
        return true;

    aux = vec3(otherHitBoxMin.x, otherHitBoxMax.y, otherHitBoxMax.z);
    if(pointInsideCube(aux))
        return true;

    aux = vec3(otherHitBoxMin.x, otherHitBoxMax.y, otherHitBoxMin.z);
    if(pointInsideCube(aux))
        return true;

    aux = vec3(otherHitBoxMax.x, otherHitBoxMax.y, otherHitBoxMin.z);
    if(pointInsideCube(aux))
        return true;

    aux = vec3(otherHitBoxMax.x, otherHitBoxMin.y, otherHitBoxMin.z);
    if(pointInsideCube(aux))
        return true;

    aux = vec3(otherHitBoxMax.x, otherHitBoxMin.y, otherHitBoxMax.z);
    if(pointInsideCube(aux))
        return true;

    return false;
}
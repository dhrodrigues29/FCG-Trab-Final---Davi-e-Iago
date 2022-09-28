#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <glm/glm.hpp>

//Colisão Cubo-Cubo
bool cubeOnCubeCollision(glm::vec3 cameraPos, glm::vec3 bunnyPosition) {

    glm::vec3 camSize = glm::vec3(0.5f, 0.5f, 0.5f);
    glm::vec3 bunnySize = glm::vec3(0.5f, 0.5f, 0.5f);

    if(cameraPos.x + camSize.x >= bunnyPosition.x && bunnyPosition.x + bunnySize.x >= cameraPos.x &&
        cameraPos.z + camSize.z >= bunnyPosition.z && bunnyPosition.z + bunnySize.z >= cameraPos.z) {
        return true;
    }

    return false;

}

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <glm/glm.hpp>

//Colisão Cubo-Cubo
bool cubeOnCubeCollision(glm::vec3 cameraPos, glm::vec3 bunnyPosition) {

    glm::vec3 camSize = glm::vec3(0.5f, 0.5f, 0.5f);
    glm::vec3 bunnySize = glm::vec3(0.5f, 0.5f, 0.5f);

    //Seta a camera no chao para comparar com o coelho
    cameraPos.y = 0.0f;
    if(cameraPos.x + camSize.x >= bunnyPosition.x && bunnyPosition.x + bunnySize.x >= cameraPos.x &&
        cameraPos.y + camSize.y >= bunnyPosition.y && bunnyPosition.y + bunnySize.y >= cameraPos.y &&
        cameraPos.z + camSize.z >= bunnyPosition.z && bunnyPosition.z + bunnySize.z >= cameraPos.z) {
        return true;
    }

    return false;

}


//Colisão Cubo-Plano
bool cubeOnPlaneCollision(glm::vec3 cameraPos) {

    glm::vec3 camSize = glm::vec3(0.5f, 0.5f, 0.5f);

    //Seta o teto para comparar no pulo
    glm::vec3 planePosition = glm::vec3(0.0f, 3.0f, 0.0f);
    glm::vec3 planeSize = glm::vec3(20.0f, 0.0f, 20.0f);

    std::cout << "CameraPos: " << cameraPos.x + camSize.x << std::endl;
    std::cout << "PlanePos: " << planePosition.x + planeSize.x  << std::endl;

    if(fabs(cameraPos.x + camSize.x) >= planePosition.x && planePosition.x + planeSize.x >= cameraPos.x &&
        cameraPos.y + camSize.y >= planePosition.y && planePosition.y + planeSize.y >= cameraPos.y &&
        fabs(cameraPos.z + camSize.z) >= planePosition.z && planePosition.z + planeSize.z >= cameraPos.z) {
        return true;
    }

    return false;

}
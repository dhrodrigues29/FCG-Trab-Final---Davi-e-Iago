#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>

#ifndef _sceneObjs_hpp
#define _sceneObjs_hpp

using namespace glm;

class SceneObj{
public:
    int id;
    bool isRabbit;
    float width, height, depth;
    bool isAlive;
    vec3 position, hitBoxMin, hitBoxMax;
    SceneObj(int id, vec3 position, bool isRabbit);
    SceneObj();
    void setPosition(vec3 position);
    void setControlPoints();

    //Pontos de controle para curvas de bezier
    glm::vec4 p0; //= glm::vec4(-1.0f, -1.0f, 0.5f, 1.0f);
    glm::vec4 p1;//= glm::vec4(-0.25f, 2.0f, 0.5f, 1.0f);
    glm::vec4 p2; //= glm::vec4(0.25f,  -2.0f, 0.5f, 1.0f);
    glm::vec4 p3; //= glm::vec4(1.0f,   1.0f, 0.5f, 1.0f);

};

#endif // _sceneObjs_hpp

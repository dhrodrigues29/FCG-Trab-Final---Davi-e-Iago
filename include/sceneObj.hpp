#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>

#ifndef _sceneObj_hpp
#define _sceneObj_hpp

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
    void updateHitBox();
    bool wallColision();
    void setPosition(vec3 position);
    bool pointInsideCube(vec3 point);
    bool cubeInsideCube(vec3 otherHitBoxMin, vec3 otherHitBoxMax);
};

#endif // _sceneObj_hpp

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

};

#endif // _sceneObjs_hpp

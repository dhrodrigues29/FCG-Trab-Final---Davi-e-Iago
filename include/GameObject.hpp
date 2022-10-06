#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>
#define CUBE_SIZE 0.8
#define CUBE_SIZE_RABBIT 0.3
#define PLANE_SIZE 20


using namespace glm;

class GameObject{
public:

    float width, height, depth;
    vec3 position, hitBoxMin, hitBoxMax;
    GameObject(vec3 position);
    GameObject();
    void setControlPoints();

    //Pontos de controle para curvas de bezier
    glm::vec4 p0; 
    glm::vec4 p1;
    glm::vec4 p2; 
    glm::vec4 p3; 

};


#version 330 core

// Atributos de fragmentos recebidos como entrada ("in") pelo Fragment Shader.
// Neste exemplo, este atributo foi gerado pelo rasterizador como a
// interpolação da posição global e a normal de cada vértice, definidas em
// "shader_vertex.glsl" e "main.cpp".
in vec4 position_world;
in vec4 normal;

// Posição do vértice atual no sistema de coordenadas local do modelo.
in vec4 position_model;

// Coordenadas de textura obtidas do arquivo OBJ (se existirem!)
in vec2 texcoords;

// gouraud shading, calculado no vertex shader
in vec3 gouraud_color;

// Matrizes computadas no código C++ e enviadas para a GPU
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// Identificador que define qual objeto está sendo desenhado no momento

#define BUNNY    1
#define PLANE    2
#define COW      3
uniform int object_id;

// Parâmetros da axis-aligned bounding box (AABB) do modelo
uniform vec4 bbox_min;
uniform vec4 bbox_max;

// Variáveis para acesso das imagens de textura

uniform sampler2D TextureImage0; //BUNNY
uniform sampler2D TextureImage1; //PLANE
uniform sampler2D TextureImage2; //COW
uniform sampler2D TextureImage3; //GRASS
uniform sampler2D TextureImage4; //COW


// O valor de saída ("out") de um Fragment Shader é a cor final do fragmento.
out vec3 color;

// Constantes
#define M_PI   3.14159265358979323846
#define M_PI_2 1.57079632679489661923


void main()
{
    // Obtemos a posição da câmera utilizando a inversa da matriz que define o
    // sistema de coordenadas da câmera.
    vec4 origin = vec4(0.0, 0.0, 0.0, 1.0);
    vec4 camera_position = inverse(view) * origin;

    //Spotlight
    float spotlight_opening = 0.8660254; //cos(30)
    vec4 spotlight_position = vec4(0.0, 5.0, 0.0, 1.0);
    vec4 spotlight_direction = normalize(vec4(0.0, -1.0, 0.0, 0.0));

    // O fragmento atual é coberto por um ponto que percente à superfície de um
    // dos objetos virtuais da cena. Este ponto, p, possui uma posição no
    // sistema de coordenadas global (World coordinates). Esta posição é obtida
    // através da interpolação, feita pelo rasterizador, da posição de cada
    // vértice.
    vec4 p = position_world;

    // Normal do fragmento atual, interpolada pelo rasterizador a partir das
    // normais de cada vértice.
    vec4 n = normalize(normal);

    // Vetor que define o sentido da fonte de luz em relação ao ponto atual.
    vec4 l = normalize(vec4(0.0,1.0,0.0,1.0));

    // Vetor que define o sentido da câmera em relação ao ponto atual.
    vec4 v = normalize(camera_position - p);

    // Vetor que define o sentido da reflexão especular ideal.
    vec4 r = -l + 2*n*(dot(n,l));

    // Vetor que define blinn-phong
    vec4 h = normalize(l+v);

    // Coordenadas de textura U e V
    float U = 0.0;
    float V = 0.0;

    // Parâmetros que definem as propriedades espectrais da superfície
    vec3 Kd = vec3(0.0,0.0,0.0); // Refletância difusa
    vec3 Ks = vec3(0.0,0.0,0.0); // Refletância especular
    vec3 Ka = vec3(0.0,0.0,0.0); // Refletância ambiente
    float q = 1; // Expoente especular para o modelo de iluminação de Phong

   
    if ( object_id == PLANE )
    {
        // Coordenadas de textura do plano
        U = texcoords.x*8;
        V = texcoords.y*8;

       // Propriedades espectrais do plano
        Kd = vec3(0.2, 0.2, 0.2);
        Ks = vec3(0.3, 0.3, 0.3);
        Ka = vec3(0.2,0.2,0.2); 
        q = 10.0;
    }
    if ( object_id == COW )
    {
        // Propriedades espectrais da vaca
        Kd = vec3(0.08,0.4,0.8);
        Ks = vec3(0.8,0.8,0.8);
        Ka = vec3(0.04,0.2,0.4);
        q = 2.0;

        // Projeção planar
        float minx = bbox_min.x;
        float maxx = bbox_max.x;

        float miny = bbox_min.y;
        float maxy = bbox_max.y;

        float minz = bbox_min.z;
        float maxz = bbox_max.z;

        U = (position_model.x - minx) / (maxx - minx);
        V = (position_model.y - miny) / (maxy - miny);
    }

    vec3 planeTexture = texture(TextureImage0, vec2(U,V)).rgb;
    vec3 cowTexture = texture(colocarTexturaAqui, vec2(U,V)).rgb;
    
    // Espectro da fonte de iluminação
    vec3 I = vec3(1.0,1.0,1.0); 

    // Espectro da luz ambiente
    vec3 Ia = vec3(0.2, 0.2, 0.2); 

    // Termo difuso utilizando a lei dos cossenos de Lambert
    vec3 lambert_diffuse_term = Kd * I * max(0, dot(n,l)); 

    // Termo ambiente
    vec3 ambient_term =  Ka * Ia;// Termo ambiente

    // Termo especular utilizando o modelo de iluminação de Phong
    vec3 phong_specular_term  = Ks * I * pow(max(0, dot(r,v)), q); 
    
    q = 1;

    // Termo especular utilizando o modelo de iluminação de Blinn Phong
    vec3 blinn_phong_specular_term  = Ks * I * pow(dot(n, h), q);


    vec4 object_distance = normalize(position_world - spotlight_position);

    

    //Aplicat as cores com spotlight e texturas
    if(dot(object_distance, spotlight_direction) > spotlight_opening)
    {
        if ( object_id == PLANE )    
            color = planeTexture * (lambert_diffuse_term + ambient_term + blinn_phong_specular_term);
        else if ( object_id == COW )      
            color = cowTexture * (lambert_diffuse_term + ambient_term + blinn_phong_specular_term);
    }
    else
    {
        if ( object_id == PLANE )    
            color = planeTexture * (ambient_term);
        else if ( object_id == COW )      
            color = cowTexture * (ambient_term);
    }


    color = pow(color, vec3(1.0,1.0,1.0)/2.2);

}


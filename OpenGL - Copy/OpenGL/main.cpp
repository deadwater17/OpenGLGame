#include <iostream>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "glm/glm.hpp"

#include "Model.h"
#include "Texture.h"
#include "Shader.h"
#include "World.h"
#include "Player.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#undef main

SDL_Window* initializeSDL();
void initializeGLEW();
GLuint createShaderProgram(const GLchar* vertexShaderSrc, const GLchar* fragmentShaderSrc);
GLuint createVBO(const GLfloat* data, size_t dataSize);
GLuint createVAO(GLuint positionsVboID, GLuint colorsVboId);
void mainLoop(SDL_Window* window, GLuint programId, Player& player, Texture& playerTex, World& world);


int main()
{
    SDL_Window* window = initializeSDL();
    initializeGLEW();

    const GLfloat positions[] = {
        0.0f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f
    };

    const GLfloat colors[] = {
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
    };

    const GLchar* fragmentShaderSrc =
        "uniform sampler2D u_Texture;       " \
        "varying vec2 v_TexCoord;           " \
        "uniform vec3 u_ViewPos;            " \
        "uniform mat4 u_View;               " \
        "                                   " \
        "vec3 lightPos = vec3(10,10,10);    " \
        "vec3 diffuseColor = vec3(1,1,1);   " \
        "vec3 specularColor = vec3 (1,1,1); " \
        "                                   " \
        "varying vec3 v_Normal;             " \
        "varying vec3 v_FragPos;            " \
        "								    " \
        "void main()                        " \
        "{                                  " \
        "vec3 N = normalize(v_Normal);      " \
        "vec3 lightDir = normalize(lightPos - v_FragPos);   " \
        "float diff = max(dot(N, lightDir), 0.0);           " \
        "vec3 diffuse = diffuseColor * diff;                " \
        "                                                   " \
        "vec3 viewDir = normalize(u_ViewPos - v_FragPos);   " \
        "vec3 reflectDir = reflect(-lightDir,N);            " \
        "float spec = pow (max(dot(viewDir, reflectDir), 0.0),32);" \
        "vec3 specular = spec * specularColor;              " \
        "                                                   " \
        "vec4 viewPos = inverse(u_View) * vec4 (0,0,0,1);   " \
        "                                                   " \
        "vec4 tex = texture2D (u_Texture, v_TexCoord);      " \
        "vec3 lighting = diffuse + specular;                " \
        "gl_FragColor = vec4(lighting,1)* tex;              " \
        "}									";

    const GLchar* vertexShaderSrc =
        "attribute vec3 a_Position;             " \
        "attribute vec2 a_TexCoord;             " \
        "attribute vec3 a_Normal;               " \
        "uniform mat4 u_Projection;             " \
        "uniform mat4 u_Model;                  " \
        "                                       " \
        "varying vec3 v_FragPos;                " \
        "varying vec3 v_Normal;                 " \
        "varying vec2 v_TexCoord;               " \
        "void main()                            " \
        "{                                      " \
        " gl_Position = u_Projection * u_Model * vec4(a_Position, 1.0); " \
        "v_TexCoord = a_TexCoord;               " \
        "                                       " \
        "v_Normal = mat3(u_Model) * a_Normal;   " \
        "v_FragPos = vec3(u_Model * vec4(a_Position, 1.0));" \
        "}                                      ";


    GLuint programId = createShaderProgram(vertexShaderSrc, fragmentShaderSrc);
    //Model cat("curuthers.obj");
    //Texture catTex("Whiskers_diffuse.png");
    World world(vertexShaderSrc, fragmentShaderSrc);
    Player player(&world); // Instantiate the Player object
    Texture playerTex("Whiskers_diffuse.png");

    GLuint positionsVboID = createVBO(positions, sizeof(positions));
    GLuint colorsVboId = createVBO(colors, sizeof(colors));
    GLuint vaoId = createVAO(positionsVboID, colorsVboId);

    mainLoop(window, programId, player, playerTex, world);

    return 0;
}

SDL_Window* initializeSDL() {
    SDL_Window* window = SDL_CreateWindow("Triangle",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

    if (!SDL_GL_CreateContext(window)) {
        throw std::runtime_error("Failed to create OpenGL context");
    }

    return window;
}

void initializeGLEW() {
    if (glewInit() != GLEW_OK) {
        throw std::runtime_error("Failed to initialize GLEW");
    }
}

GLuint createShaderProgram(const GLchar* vertexShaderSrc, const GLchar* fragmentShaderSrc) {
    Shader shader(vertexShaderSrc, fragmentShaderSrc);
    return shader.getID();
}

GLuint createVBO(const GLfloat* data, size_t dataSize) {
    GLuint vboID = 0;
    glGenBuffers(1, &vboID);
    if (!vboID) {
        throw std::runtime_error("Failed to initialize VBO on GPU");
    }
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return vboID;
}

GLuint createVAO(GLuint positionsVboID, GLuint colorsVboId) {
    GLuint vaoId = 0;
    glGenVertexArrays(1, &vaoId);
    if (!vaoId) {
        throw std::runtime_error("Failed to initialize VAO on GPU");
    }
    glBindVertexArray(vaoId);

    glBindBuffer(GL_ARRAY_BUFFER, positionsVboID);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, colorsVboId);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return vaoId;
}

void mainLoop(SDL_Window* window, GLuint programId, Player& player, Texture& playerTex, World& world) {
    GLint projectionLoc = glGetUniformLocation(programId, "u_Projection");
    GLint modelLoc = glGetUniformLocation(programId, "u_Model"); // Get the location of the u_Model uniform

    bool quit = false;
    float angle = 0.0f;
    int width = 0;
    int height = 0;

    Uint32 lastTime = SDL_GetTicks();

    while (!quit) {

        Uint32 currentTime = SDL_GetTicks();
        float dt = (currentTime - lastTime) / 1000.0f; // Convert to seconds
        lastTime = currentTime;

        SDL_Event ev = { 0 };
        while (SDL_PollEvent(&ev)) {
            if (ev.type == SDL_QUIT) {
                quit = true;
            }
            else if (ev.type == SDL_KEYDOWN || ev.type == SDL_KEYUP) {
                world.keyboard[ev.key.keysym.scancode] = (ev.type == SDL_KEYDOWN);
            }
        }
        
        world.handleInput(dt); // Handle input for the world and player

        SDL_GetWindowSize(window, &width, &height);
        glViewport(0, 0, width, height);

        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(programId);
		//glBindVertexArray(player.vao_id());


        glm::mat4 view = glm::mat4(1.0f);  // Identity matrix
        GLint viewLoc = glGetUniformLocation(programId, "u_View");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));


        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, player.playerPos); // Use player's model position
        //model = glm::rotate(model, glm::radians(angle), glm::vec3(0, 1, 0));
        angle += 0.1f;

        //glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); // Set the model matrix
        
        //### PROJECTION MATRIX ( MOVED TO SHADER )
        //glm::mat4 projection = glm::perspective(glm::radians(120.0f),
        //    (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
        //glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        glBindTexture(GL_TEXTURE_2D, playerTex.id());

        glEnable(GL_DEPTH_TEST);
        //player.m_world->light.draw(player, player.playerPos); // Use Shader::draw method
        //glDrawArrays(GL_TRIANGLES, 0, player.vertex_count());
        glDisable(GL_CULL_FACE);

        world.render();

        SDL_GL_SwapWindow(window);


     }
}
#include <iostream>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "glm/glm.hpp"

#include "World.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#undef main

/*
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
        "uniform mat4 u_View;                   " \
        "                                       " \
        "varying vec3 v_FragPos;                " \
        "varying vec3 v_Normal;                 " \
        "varying vec2 v_TexCoord;               " \
        "void main()                            " \
        "{                                      " \
        " gl_Position = u_Projection * u_View * u_Model * vec4(a_Position, 1.0); " \
        "v_TexCoord = a_TexCoord;               " \
        "                                       " \
        "v_Normal = mat3(u_Model) * a_Normal;   " \
        "v_FragPos = vec3(u_Model * vec4(a_Position, 1.0));" \
        "}                                      ";


    GLuint programId = createShaderProgram(vertexShaderSrc, fragmentShaderSrc);

   
    return 0;
}

SDL_Window* initializeSDL() {
    SDL_Window* window = SDL_CreateWindow("OpenGLGame",
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

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, player.playerPos); // Use player's model position

        glBindTexture(GL_TEXTURE_2D, playerTex.id());

        glEnable(GL_DEPTH_TEST);
        glDisable(GL_CULL_FACE);

        world.render();

        SDL_GL_SwapWindow(window);


     }
}
*/

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


int main()
{
    SDL_Window* window = SDL_CreateWindow("OpenGL Game",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

    if (!SDL_GL_CreateContext(window))
    {
        throw std::runtime_error("Failed to create OpenGL context");
    }

    if (glewInit() != GLEW_OK)
    {
        throw std::runtime_error("Failed to initialze GLEW");
    }

    World world;

	bool quit = false;
    SDL_Event event;
    float lastTime = SDL_GetTicks() / 1000.0f;

	while (!quit)
	{
        float currentTime = SDL_GetTicks() / 1000.0f;
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;

		SDL_Event ev = { 0 };
		while (SDL_PollEvent(&ev))
		{
			if (ev.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
        // Render your scene here
        world.handleInput(deltaTime);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        world.update(deltaTime);
        world.render();

		SDL_GL_SwapWindow(window);
	}
}
#include <iostream>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "glm/glm.hpp"
#include "World.h"
#include "Model.h"
#include "Texture.h"
#include "Triangle.h"
#include "Shader.h"


#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#undef main

int main()
{
    SDL_Window* window = SDL_CreateWindow("Triangle",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

    //connection to GPU, checks if it's connected
    if (!SDL_GL_CreateContext(window))
    {
        throw std::runtime_error("Failed to create OpenGL context");
    }

    if (glewInit() != GLEW_OK)
    {
        throw std::runtime_error("Failed to initialze GLEW");
    }


    //points describing the shape (triangle)
    const GLfloat positions[] =
    {
        0.0f, 0.5f, 0.0f,       //x (starts from centre of the screen),y,z
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f
    };

    //defining the color of each point of the triangle
    const GLfloat colors[] =
    {
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
    };

    int w = 0;
    int h = 0;

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
        ""\
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


    Shader shader(vertexShaderSrc, fragmentShaderSrc);
	GLuint programId = shader.getID();

    Model cat("curuthers.obj");

    Texture catTex("Whiskers_diffuse.png");

	World world(vertexShaderSrc, fragmentShaderSrc);

    // Creating new Vertex Buffer Object (VBO) on the GPU and binding it
    GLuint positionsVboID = 0;  //VBO
    glGenBuffers(1, &positionsVboID);
    if (!positionsVboID)
    {
        throw std::runtime_error("Failed to Initialise VBO on GPU");
    }
    glBindBuffer(GL_ARRAY_BUFFER, positionsVboID);
    //upload copy of data from memory to VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
    //resets the state
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //creating VBO and uploading data onto it and assigning it to position 1 of VAO
    GLuint colorsVboId = 0;
    //creating colors VBO on GPU and binding it
    glGenBuffers(1, &colorsVboId);
    if(!colorsVboId)
    {
        throw std::exception();
    }
    glBindBuffer(GL_ARRAY_BUFFER, colorsVboId);
    //upload copy of data from memory to VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    //creating Vertex Array Object (VAO) on GPU and binding it
    GLuint vaoId = 0;   //VAO
    glGenVertexArrays(1, &vaoId);
    if (!vaoId)
    {
        throw std::runtime_error("Failed to initialise VAO on GPU");
    }
    glBindVertexArray(vaoId);
    //binds VBO position, assigned as 0 on the bound VAO
    glBindBuffer(GL_ARRAY_BUFFER, positionsVboID);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
        3 * sizeof(GLfloat), (void*)0);

    glEnableVertexAttribArray(0);

    //binding color of VBO and assigning it to position 1 on the bound VBO, flagging it to be used
    glBindBuffer(GL_ARRAY_BUFFER, colorsVboId);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(1);

    //resets state
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //finding uniform location
    GLint modelLoc = glGetUniformLocation(programId, "u_Model");    //creating model matrix
    GLint projectionLoc = glGetUniformLocation(programId, "u_Projection");  //generating perspective projection matrix and assigning it

    bool quit = false;
    float angle = 0.0f;

    int width = 0;
    int height = 0;

    while (!quit)
    {
        SDL_Event ev = { 0 };
        while (SDL_PollEvent(&ev))
        {
            if (ev.type == SDL_QUIT)
            {
                quit = true;
            }
        }


        //basically get the width and height and updates the screen accordingly
        SDL_GetWindowSize(window, &width, &height);
        glViewport(0, 0, width, height);

        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);   // RBGA
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		world.render();

        //tells OpenGL to use our shader program and our VAO
        glUseProgram(programId);
        glBindVertexArray(cat.vao_id());   //might comment out 

        glm::mat4 projection = glm::perspective(glm::radians(120.0f),
            (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);

        //this is the model matrix for 
        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(0, 0, -2.0f));
        model = glm::rotate(model, glm::radians(angle), glm::vec3(0, 1, 0));

        // Increase the float angle so next frame the triangle rotates further (increases speed of rotation)
        angle += 0.1f;

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        // Upload the projection matrix
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE,
            glm::value_ptr(projection));


        // glActiveTexture(GL_TEXTURE0 + 1);
        glBindTexture(GL_TEXTURE_2D, catTex.id());

        glEnable(GL_DEPTH_TEST);
        //glCullFace(GL_FRONT);

        //glEnable(GL_CULL_FACE);
        glDrawArrays(GL_TRIANGLES, 0, cat.vertex_count());
        glDisable(GL_CULL_FACE);

        /*
        //ORTHOGRAPHIC PROJECTION
        // Prepare the orthographic projection matrix (reusing the variable)
        projection = glm::ortho(0.0f, (float)WINDOW_WIDTH, 0.0f,
            (float)WINDOW_HEIGHT, 0.0f, 1.0f);

        // Prepare model matrix. The scale is important because now our triangle
        // would be the size of a single pixel when mapped to an orthographic
        // projection.
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(100, WINDOW_HEIGHT - 100, 0));
        model = glm::scale(model, glm::vec3(100, 100, 1));

        // Upload the model matrix
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        // Upload the projection matrix
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE,
           glm::value_ptr(projection));

        // Draw 3 vertices (a triangle)
        glDrawArrays(GL_TRIANGLES, 0, 3);

        //binds the shader to change the uniform, currently set to green
        //glUniform4f(colorUniformId, 0, 1, 0, 1);
        //glUniform4f(colorUniformId, 1, 1, 0, 1); //This would be yellow

        // Reset the state
        glBindVertexArray(0);
        glUseProgram(0);
        glBindTexture(GL_TEXTURE_2D, 0);
        */

        SDL_GL_SwapWindow(window);

    }
    return 0;
}
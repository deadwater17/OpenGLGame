#include <iostream>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include "glm/glm.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Window.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "ShaderProgram.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#undef main

int main()
{
    {
        Window window;

        // Main loop
        bool running = true;
        while (running) {
            // Event handling
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    running = false;
                }
            }

            // Render
            glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            SDL_GL_SwapWindow(window.getWindow());
        }
        /*
        // Define vertex data
        const GLfloat positions[] = {
            0.0f, 0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f
        };



        // Create and bind VAO
        VertexArray vao;
        vao.bind();

        // Create and bind VBO
        VertexBuffer vbo(positions, sizeof(positions)); // Pass the array directly
        vbo.bind();

        // Enable vertex attribute array
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

        // Unbind VBO and VAO
        vbo.unbind();
        vao.unbind();

        // Create and use shader program
        VertexShader vertexShader;
        FragmentShader fragmentShader;
        ShaderProgram shaderProgram(vertexShader, fragmentShader);
        shaderProgram.use();

        while (window.isRunning())
        {
            // Event handling
            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                {
                    window.setRunning(false);
                }
            }

            // Render
            glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            // Instruct OpenGL to use our shader program and our VAO
            glUseProgram(shaderProgram.getID());
            glBindVertexArray(vao.getID());

            // Draw 3 vertices (a triangle)
            glDrawArrays(GL_TRIANGLES, 0, 3);

            // Reset the state
            glBindVertexArray(0);
            glUseProgram(0);

            // Update window
            SDL_GL_SwapWindow(window.getWindow());
        }
        */
    }
    return 0;
}

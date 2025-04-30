#include "GUI.h"

const GLchar* guiVertexShaderSrc =
"attribute vec3 a_Position;             " \
"attribute vec2 a_TexCoord;             " \
"uniform mat4 u_Projection;             " \
"uniform mat4 u_Model;                  " \
"                                       " \
"varying vec2 v_TexCoord;               " \
"                                       " \
"void main()                            " \
"{                                      " \
"gl_Position = u_Projection * u_Model * vec4(a_Position, 1.0); " \
"v_TexCoord = a_TexCoord;               " \
"}                                      ";

const GLchar * guiFragmentShaderSrc =
"uniform sampler2D u_Texture;           " \
"varying vec2 v_TexCoord;               " \
"                                       " \
"void main()                            " \
"{                                      " \
"gl_FragColor = texture2D(u_Texture, v_TexCoord); " \
"}                                      ";

GUI::GUI()
	:	m_vao(0)
	,	m_vbo(0)
{}

GUI::~GUI()
{
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
}

void GUI::init()
{
    float quadVertices[] = {
        // positions   // tex coords
        -0.9f, 0.9f,   0.0f, 1.0f,   // Top-left
        -0.7f, 0.9f,   1.0f, 1.0f,   // Top-right
        -0.7f, 0.7f,   1.0f, 0.0f,   // Bottom-right
        -0.9f, 0.7f,   0.0f, 0.0f    // Bottom-left
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);

    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

    // Position
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // TexCoord
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void GUI::draw(Shader& guiShader)
{
    glDisable(GL_DEPTH_TEST);  // Disable depth test so GUI renders over everything

    guiShader.use();

    // Set orthographic projection
    glm::mat4 ortho = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f); // NDC space
    glUniformMatrix4fv(glGetUniformLocation(guiShader.getID(), "u_Projection"), 1, GL_FALSE, glm::value_ptr(ortho));

    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glBindVertexArray(0);

    glEnable(GL_DEPTH_TEST);
}

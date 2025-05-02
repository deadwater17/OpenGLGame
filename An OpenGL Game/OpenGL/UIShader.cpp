#include "uiShader.h"

const GLchar* uivertexShaderSrc =
"attribute vec2 a_Position;             " \
"attribute vec2 a_TexCoord;             " \
"uniform mat4 u_Projection;             " \
"varying vec2 v_TexCoord;               " \
"                                       " \
"void main() {                          " \
"gl_Positions = u_Projection * vec4(a_Position,0.0,1.0);    " \
"v_TexCoord = a_TexCoord;               " \
"}                                      ";


const GLchar* uifragmentShaderSrc =
"uniform sampler2D u_Texture;           " \
"varying vec2 v_TexCoord;               " \
"                                       " \
"void main() {                          " \
"gl_FragColor = texture2D(u_Texture, v_TexCoord);           " \
"}                                      ";

uiShader::uiShader()
    : programId(0)
    , vertexShaderId(0)
    , fragmentShaderId(0)
{


    // Creating new vertex shader, attaching source code, compiling it and checking for errors
    GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderId, 1, &uivertexShaderSrc, NULL);
    glCompileShader(vertexShaderId);

    // Check if any error occur during vertex shader compilation
    GLint success = 0;
    glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        throw std::exception();
    }

    GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderId, 1, &uifragmentShaderSrc, NULL);
    glCompileShader(fragmentShaderId);

    GLint isCompiled = 0;
    glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE)
    {

        GLint maxLength = 0;
        glGetShaderiv(fragmentShaderId, GL_INFO_LOG_LENGTH, &maxLength);
        // get shader error length
        std::vector <GLchar> errorLog(maxLength);
        // basically gets the length of the error message and put it into text
        glGetShaderInfoLog(fragmentShaderId, maxLength, &maxLength, &errorLog[0]);

        std::cout << &errorLog[0] << std::endl;
        throw std::exception();
    }

    programId = glCreateProgram();
    glAttachShader(programId, vertexShaderId);
    glAttachShader(programId, fragmentShaderId);
    glLinkProgram(programId);

    glGetProgramiv(programId, GL_LINK_STATUS, &success);
    //checks success
    if (!success)
    {
        throw std::exception();
    }

}

void uiShader::compile(const GLchar* vertexSrc, const GLchar* fragmentSrc)
{
    vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderId, 1, &vertexSrc, NULL);
    glCompileShader(vertexShaderId);

    GLint success = 0;
    glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        throw std::runtime_error("Failed to compile vertex shader.");
    }

    fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderId, 1, &fragmentSrc, NULL);
    glCompileShader(fragmentShaderId);

    glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        GLint maxLength = 0;
        glGetShaderiv(fragmentShaderId, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(fragmentShaderId, maxLength, &maxLength, &errorLog[0]);
        std::cerr << &errorLog[0] << std::endl;
        throw std::runtime_error("Failed to compile fragment shader.");
    }

    programId = glCreateProgram();
    glAttachShader(programId, vertexShaderId);
    glAttachShader(programId, fragmentShaderId);
    glLinkProgram(programId);

    glGetProgramiv(programId, GL_LINK_STATUS, &success);
    if (!success)
    {
        throw std::runtime_error("Failed to link shader program.");
    }
}

uiShader::~uiShader()
{
    glDetachShader(programId, vertexShaderId);
    glDetachShader(programId, fragmentShaderId);
    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);
    glDeleteProgram(programId);
}

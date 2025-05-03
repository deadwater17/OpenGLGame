#include "Shader.h"

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
"gl_Position = u_Projection * u_View * u_Model * vec4(a_Position, 1.0); " \
"v_TexCoord = a_TexCoord;               " \
"                                       " \
"v_Normal = mat3(u_Model) * a_Normal;   " \
"v_FragPos = vec3(u_Model * vec4(a_Position, 1.0));" \
"}                                      ";

const GLchar* fragmentShaderSrc =
"uniform sampler2D u_Texture;       " \
"varying vec2 v_TexCoord;           " \
"uniform vec3 u_ViewPos;            " \
"uniform mat4 u_View;               " \
"                                   " \
"vec3 lightPos = vec3(10,5,10);    " \
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
"float diff = max(dot(N, lightDir), 0.0);           "     
"vec3 diffuse = diffuseColor * diff;                " \
"                                                   " \
"vec3 viewDir = normalize(u_ViewPos - v_FragPos);    " \
"vec3 reflectDir = reflect(-lightDir,N);         " \
"float spec = pow (max(dot(viewDir, reflectDir), 0.0),32);" \
"vec3 specular = spec * specularColor;              " \
"                                                   " \
"vec4 viewPos = inverse(u_View) * vec4 (0,0,0,1);   " \
"                                                   "\
"vec4 tex = texture2D (u_Texture, v_TexCoord);      " \
"vec3 lighting = diffuse + specular;                " \
"gl_FragColor = vec4(lighting,1)* tex;              " \
"}                                                  ";

// line 40: float diff = max(dot(N, lightDir), 0.0); 

Shader::Shader()
	: programId(0)
    , vertexShaderId(0)
    , fragmentShaderId(0)
{


    // Creating new vertex shader, attaching source code, compiling it and checking for errors
    GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderId, 1, &vertexShaderSrc, NULL);
    glCompileShader(vertexShaderId);

	// Check if any error occur during vertex shader compilation
    GLint success = 0;
    glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        throw std::exception();
    }

    GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderId, 1, &fragmentShaderSrc, NULL);
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

void Shader::compile(const GLchar* vertexSrc, const GLchar* fragmentSrc)
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

Shader::~Shader()
{
    glDetachShader(programId, vertexShaderId);
    glDetachShader(programId, fragmentShaderId);
    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);
    glDeleteProgram(programId);
}

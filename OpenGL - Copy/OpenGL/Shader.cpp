#include "Shader.h"

Shader::Shader(const char* vertexSrc, const char* fragmentSrc)
{
	programId = glCreateProgram();
	vertexShaderId = compileShader(vertexSrc, GL_VERTEX_SHADER);
	fragmentShaderId = compileShader(fragmentSrc, GL_FRAGMENT_SHADER);

	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);
	glBindAttribLocation(programId, 0, "a_Position");
	glBindAttribLocation(programId, 1, "a_TexCoord");
	glBindAttribLocation(programId, 2, "a_Normal");
	glLinkProgram(programId);

	GLint success = 0;

	glGetProgramiv(programId, GL_LINK_STATUS, &success);

	//checks success
	if (!success)
	{
		GLint logLength = 0;
		glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &logLength);
		std::vector<char> log(logLength);
		glGetProgramInfoLog(programId, logLength, &logLength, log.data());
		std::cerr << "Program linking failed: " << log.data() << std::endl;
		throw std::runtime_error("Program linking failed");
	}
}

Shader::~Shader()
{
	glDetachShader(programId, vertexShaderId);
	glDeleteShader(vertexShaderId);
	glDetachShader(programId, fragmentShaderId);
	glDeleteShader(fragmentShaderId);
}

GLuint Shader::compileShader(const char* src, GLenum type) {
	GLuint shaderId = glCreateShader(type);
	glShaderSource(shaderId, 1, &src, NULL);
	glCompileShader(shaderId);

	GLint success = 0;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLint logLength = 0;
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);
		std::vector<char> log(logLength);
		glGetShaderInfoLog(shaderId, logLength, &logLength, log.data());
		std::cerr << "Shader compilation failed: " << log.data() << std::endl;
		throw std::runtime_error("Shader compilation failed");
	}

	return shaderId;
}


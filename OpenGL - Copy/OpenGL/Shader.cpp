#include "Shader.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

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

void Shader::draw(const Model& model, const glm::vec3& position)
{
	std::cout << "Setting model matrix for position: ("
		<< position.x << ", " << position.y << ", " << position.z << ")" << std::endl;

	// Use the shader program for rendering the model
	glUseProgram(getID());

	glm::mat4 projectionMatrix = glm::perspective(glm::radians(120.0f),
		(float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);

	// Set up the model transformation matrix
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, position);

	// Set the uniform variables for the shader
	GLint modelLoc = glGetUniformLocation(getID(), "u_Model");
	if (modelLoc == -1) std::cerr << "ERROR: u_Model not found in shader!" << std::endl;
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	GLint projLoc = glGetUniformLocation(programId, "u_Projection");
	if (projLoc == -1) std::cerr << "ERROR: u_Projection not found!" << std::endl;
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));



	// Bind the model's VAO and draw it
	glBindVertexArray(const_cast<Model&>(model).vao_id());
	glDrawArrays(GL_TRIANGLES, 0, model.vertex_count());
	//glBindVertexArray(0);

	// Reset the shader program
	//glUseProgram(0);
}
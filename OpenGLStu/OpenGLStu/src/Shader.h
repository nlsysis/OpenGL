#pragma once

#include <string>
#include <unordered_map>
#include "glm/glm.hpp"
#include <GL/glew.h>

struct ShaderProgramShource
{
	std::string vertexSource;
	std::string fragmentSource;
};

class Shader
{
public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void UnBind() const;

	/// Set uniforms
	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float v0);
	void SetUniform2f(const std::string& name, const glm::vec2& value);
	void SetUniform3f(const std::string& name, const glm::vec3& value);
	void SetUniform4f(const std::string& name, const glm::vec4& value);

	void SetUniformMat4f(const std::string& name, const glm::mat3& matrix);
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
private:
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	ShaderProgramShource ParseShader(const std::string& filepath);
	GLint GetUniformLocation(const std::string& name) const;
private:
	unsigned int m_RendererID;
	//caching for uniforms
	std::string m_FilePath;
	mutable std::unordered_map<std::string, GLint> m_UniformLocationCache;
};
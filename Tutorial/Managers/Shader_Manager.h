#pragma once

#include "../Dependencies/glew/glew.h"
#include "../Dependencies/freeglut/freeglut.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

namespace Managers{
	class Shader_Manager{
	
	private:			
		std::string ReadShader(const std::string& filename);
		GLuint CreateShader(GLenum shaderType, 
							const std::string& source, 
							const std::string& shaderName);
		static std::map<std::string, GLuint> programs;

	public:
		Shader_Manager(void);
		~Shader_Manager(void);
		void CreateProgram(const std::string& shaderName,
							 const std::string& VertexShaderFilename,
							 const std::string& FragementShaderFilename);
		static const GLuint GetShader(const std::string&);
		static void DeleteShader(const std::string&);

	};
}
#ifndef Shad
#define Shad
#include "glew.h"
#include <iostream>
#include <fstream>
#include <cstring>

class ShaderDemo {
public:
	char bufferMsgBox[255];
	char *punt;
	unsigned int programa;
	GLuint vertShader;
	GLuint fragShader;
	GLuint programHandle;
	GLuint vaoHandle;
public:
	ShaderDemo(char *nombre, char *nombref)
	{
		const GLubyte *version = glGetString(GL_SHADING_LANGUAGE_VERSION);

		//////////////////////////////////////////////////////
		/////////// Vertex shader //////////////////////////
		//////////////////////////////////////////////////////

		GLchar * shaderCode;

		// Carga el shader
		std::ifstream inFile(nombre, std::ifstream::in);
		if (!inFile) {
			// ERROR STATUS
			sprintf_s(bufferMsgBox, "ShaderDemo() failed: can't open file:%s \n", nombre);
			MessageBox(NULL, bufferMsgBox, "Fatal Error", MB_OK);
		}

		//reservamos memoria para contenerlo
		shaderCode = (char *)malloc(10000);
		int i = 0;
		while (inFile.good()) {
			// NOTE: the last character read will be invalid
			int c = inFile.get();
			shaderCode[i++] = c;
		}
		inFile.close();
		shaderCode[--i] = '\0';     // NULL

		// Object 
		vertShader = glCreateShader(GL_VERTEX_SHADER);
		if (0 == vertShader) {
			MessageBox(NULL, "ShaderDemo() failed: vertShader = glCreateShader \n", "Fatal Error", MB_OK);
		}

		// Load the source code into the shader object
		const GLchar* codeArray[] = { shaderCode };
		glShaderSource(vertShader, 1, codeArray, NULL);
		free(shaderCode);

		glCompileShader(vertShader);

		GLint result;
		glGetShaderiv(vertShader, GL_COMPILE_STATUS, &result);
		if (GL_FALSE == result) {
			// print error
			GLint logLen;
			glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &logLen);

			if (logLen > 0) {
				char * log = (char *)malloc(logLen);

				GLsizei written;
				glGetShaderInfoLog(vertShader, logLen, &written, log);
				// log error
				free(log);
			}
		}

		//////////////////////////////////////////////////////
		/////////// Fragment shader //////////////////////////
		//////////////////////////////////////////////////////

		// Load Shader
		std::ifstream fragFile(nombref, std::ifstream::in);
		if (!fragFile) {
			sprintf_s(bufferMsgBox, "ShaderDemo() failed: can't open file f:%s \n", nombref);
			MessageBox(NULL, bufferMsgBox, "Fatal Error", MB_OK);
		}

		shaderCode = (char *)malloc(10000);
		i = 0;
		while (fragFile.good()) {
			int c = fragFile.get();
			shaderCode[i++] = c;
		}
		inFile.close();
		shaderCode[--i] = '\0';
		////////////////////////////////////////////
		// Create Object
		fragShader = glCreateShader(GL_FRAGMENT_SHADER);
		if (0 == fragShader) {
			MessageBox(NULL, "ShaderDemo() failed: fragShader = glCreateShader \n", "Fatal Error", MB_OK);
		}

		// Load Code	
		codeArray[0] = shaderCode;
		glShaderSource(fragShader, 1, codeArray, NULL);
		free(shaderCode);

		glCompileShader(fragShader);

		glGetShaderiv(fragShader, GL_COMPILE_STATUS, &result);
		if (GL_FALSE == result) {
			fprintf( stderr, "Fragment shader compilation failed!\n" );

			GLint logLen;
			glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &logLen);

			if (logLen > 0) {
				char * log = (char *)malloc(logLen);

				GLsizei written;
				glGetShaderInfoLog(fragShader, logLen, &written, log);

				fprintf(stderr, "Shader log: \n%s", log);

				free(log);
			}
		}


	}

	// 4x4 matrix in shader
	void PonValorM4x4(char *nombre, GLfloat valor[])
	{
		GLuint lugar = glGetUniformLocation(programHandle, nombre);
		if (lugar >= 0)
		{
			glUniformMatrix4fv(lugar, 1, GL_FALSE, valor);
		}
	}

	// Puts an array of 3 floating elements in the shader
	void PonValorV3(char *nombre, GLfloat valor[])
	{
		GLuint lugar = glGetUniformLocation(programHandle, nombre);
		if (lugar >= 0)
		{
			glUniform3fv(lugar, 1, valor);
		}

	}

	// Set Texture
	void PonTextura(char *Textura, GLint posicion) {
		GLuint lugar = glGetUniformLocation(programHandle, Textura);
		if (lugar >= 0) {
			glUniform1i(lugar, posicion);
		}
	}

	void use()
	{
		glUseProgram(programHandle);
	}

	void desuse()
	{
		glUseProgram(0);
	}

	void ligador(GLint vertShader, GLint fragShader)
	{
		programHandle = glCreateProgram();
		if (0 == programHandle) {
			MessageBox(NULL, "ShaderDemo() failed: ligador = programHandle \n", "Fatal Error", MB_OK);
		}

		//// Bind index 0 to the shader input variable "VertexPosition"
		glBindAttribLocation(programHandle, 0, "VertexPosition");
		//// Bind index 1 to the shader input variable "VertexColor"
		glBindAttribLocation(programHandle, 1, "VertexColor");

		// Attach the shaders to the program object
		glAttachShader(programHandle, vertShader);
		glAttachShader(programHandle, fragShader);

		// Link the program
		glLinkProgram(programHandle);

		// Check for successful linking
		GLint status;
		glGetProgramiv(programHandle, GL_LINK_STATUS, &status);
		if (GL_FALSE == status)
		{

			fprintf(stderr, "Failed to link shader program!\n");

			GLint logLen;
			glGetProgramiv(programHandle, GL_INFO_LOG_LENGTH, &logLen);

			if (logLen > 0)
			{
				char * log = (char *)malloc(logLen);

				GLsizei written;
				glGetProgramInfoLog(programHandle, logLen, &written, log);

				fprintf(stderr, "Program log: \n%s", log);

				free(log);
			}
		}


	}

	~ShaderDemo()
	{
		delete punt;
	}

};
#endif Shad
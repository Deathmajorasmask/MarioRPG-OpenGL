#ifndef Shad
#define Shad
#include "glew.h"
#include <iostream>
#include <fstream>
#include <cstring>

class ShaderDemo {
public:
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
			//adios, no se pudo
			exit(1);
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
		shaderCode[--i] = '\0';     // el ultimo debe de ser nulo a fuerza
									////////////////////////////////////////////

									// Crea el objeto
		vertShader = glCreateShader(GL_VERTEX_SHADER);
		if (0 == vertShader) {
			//si da cero no se pudo, adios
			exit(1);
		}

		// Load the source code into the shader object
		const GLchar* codeArray[] = { shaderCode };
		glShaderSource(vertShader, 1, codeArray, NULL);
		free(shaderCode); // libera la memoria usada.

						  // Compila al shader
		glCompileShader(vertShader);

		// Checa si se pudo
		GLint result;
		glGetShaderiv(vertShader, GL_COMPILE_STATUS, &result);
		if (GL_FALSE == result) {
			//no se pudo
			//checa por que
			GLint logLen;
			glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &logLen);

			if (logLen > 0) {
				char * log = (char *)malloc(logLen);

				GLsizei written;
				glGetShaderInfoLog(vertShader, logLen, &written, log);
				//es conveniente imprimir la razon
				free(log);
			}
		}

		//////////////////////////////////////////////////////
		/////////// Fragment shader //////////////////////////
		//////////////////////////////////////////////////////

		// carga al shader
		std::ifstream fragFile(nombref, std::ifstream::in);
		if (!fragFile) {
			//no se pudo
			exit(1);
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
		// Create al objeto
		fragShader = glCreateShader(GL_FRAGMENT_SHADER);
		if (0 == fragShader) {
			//no se pudo
			exit(1);
		}

		// carga al codigo		
		codeArray[0] = shaderCode;
		glShaderSource(fragShader, 1, codeArray, NULL);
		free(shaderCode); // se libera la memoria utilizada

						  // Compila al shader
		glCompileShader(fragShader);

		// Checa si se pudo	
		glGetShaderiv(fragShader, GL_COMPILE_STATUS, &result);
		if (GL_FALSE == result) {
			//fprintf( stderr, "Fragment shader compilation failed!\n" );

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

	//pone matrices de 4x4 en el sahder
	void PonValorM4x4(char *nombre, GLfloat valor[])
	{
		GLuint lugar = glGetUniformLocation(programHandle, nombre);
		if (lugar >= 0)
		{
			glUniformMatrix4fv(lugar, 1, GL_FALSE, valor);
		}
	}

	//pone un arreglo de 3 elementos flotantes en el shader
	void PonValorV3(char *nombre, GLfloat valor[])
	{
		GLuint lugar = glGetUniformLocation(programHandle, nombre);
		if (lugar >= 0)
		{
			glUniform3fv(lugar, 1, valor);
		}

	}

	//Milton
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
		// Crea al programa
		programHandle = glCreateProgram();
		if (0 == programHandle) {
			//no se pudo
			exit(1);
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
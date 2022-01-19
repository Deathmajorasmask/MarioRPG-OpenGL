#ifndef __Fog
#define __Fog

#include <gl\GLU.h>
#include <gl\GL.h>

class Fog
{
	 
	friend class Scene;

	GLuint filter;                      // Which Filter To Use
	
	GLuint fogfilter = 0;                    // Which Fog To Use
	
	GLfloat density= 0.04;

	void draw() {
		GLfloat fogColor[4] = { 0.5f, 0.5f, 0.5f, 1.0f };      // Fog Color
		GLuint fogMode[3] = { GL_EXP, GL_EXP2, GL_LINEAR };  // Storage For Three Types Of Foge:
		/*glEnable(GL_DEPTH_TEST);
		glEnable(GL_FOG); 
		glFogi(GL_FOG_MODE, GL_EXP2); 
		glFogfv(GL_FOG_COLOR, Color); 
		glFogf(GL_FOG_DENSITY, density);
		glHint(GL_FOG_HINT, GL_NICEST);*/
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);          // We'll Clear To The Color Of The Fog ( Modified 
		glFogi(GL_FOG_MODE, fogMode[fogfilter]);        // Fog Mode
		glFogfv(GL_FOG_COLOR, fogColor);            // Set Fog Color
		//glFogf(GL_FOG_DENSITY, 0.01f);  
		glFogf(GL_FOG_DENSITY, density);              // How Dense Will The Fog Be
		glHint(GL_FOG_HINT, GL_DONT_CARE);          // Fog Hint Value
		glFogf(GL_FOG_START, 1.0f);             // Fog Start Depth
		glFogf(GL_FOG_END, 5.0f);               // Fog End Depth
		glEnable(GL_FOG);                   // Enables GL_FOG

	}
};

#endif
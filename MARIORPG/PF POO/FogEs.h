#ifndef __FogEs
#define __FogEs

#include <gl\GLU.h>
#include <gl\GL.h>

class FogEs
{
public:
	GLfloat Color[4];
	GLfloat density;
	void drawing() {
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_FOG);
		//glEnable(GL_BLEND);
		glFogi(GL_FOG_MODE, GL_EXP2);
		glFogfv(GL_FOG_COLOR, Color);
		glFogf(GL_FOG_DENSITY, density);
		glHint(GL_FOG_HINT, GL_NICEST);

	}
};

#endif
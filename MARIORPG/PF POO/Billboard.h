#ifndef _billb
#define _billb
#include "Imagenes.h"
#include "VectorRR.h"


class Billboard : public Imagenes, public VectorRR
{

public:
	float ancho, alto;
	unsigned int billbTextura;
	VectorRR Up, derecha;
	float x, y, z;
	VectorRR BillCam;

	Billboard(HWND hWnd, WCHAR textura[], float ancho, float alto, float x, float y, float z)
	{
		this->ancho = ancho;
		this->alto = alto;
		this->x = x;
		this->y = y;
		this->z = z;
		Up = VectorRR(0, 1, 0);
		/*This vector is the one that will give us the width of the billboard every time we rotate it according to the camera*/

		Carga(textura);
		glGenTextures(1, &billbTextura);
		glBindTexture(GL_TEXTURE_2D, billbTextura);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, Ancho(), Alto(), GL_RGBA, GL_UNSIGNED_BYTE, Dir_Imagen());
		Descarga();
	}

	~Billboard()
	{
		glDeleteTextures(1, &billbTextura);
	}

	void Draw(GLdouble PX, GLdouble PY, GLdouble PZ)
	{
		glEnable(GL_DEPTH_TEST);
		/*We enable culling to reduce texture processing time. Textures are analyzed pixel by pixel to determine whether they are printed or not.*/
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		// Texture is enabled, you can mix colors and change the tone of the texture with glColorxf
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0);
		glEnable(GL_TEXTURE_2D);
		// We use modulate so that the texture is affected by the value of the normal in terms of light
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glBindTexture(GL_TEXTURE_2D, billbTextura);
		// the vector from the camera to the billboard is calculated
		BillCam = VectorRR(PX - x, PY - y, PZ - z);
		derecha = Normaliza(Cruz(Up, BillCam));
		derecha.X *= ancho / 2.0;
		derecha.Z *= ancho / 2.0;

		glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex3f(x - derecha.X, y + alto, z - derecha.Z);

		glTexCoord2f(1, 0);
		glVertex3f(x + derecha.X, y + alto, z + derecha.Z);

		glTexCoord2f(1, 1);
		glVertex3f(x + derecha.X, y, z + derecha.Z);

		glTexCoord2f(0, 1);
		glVertex3f(x - derecha.X, y, z - derecha.Z);
		glEnd();
		glDisable(GL_CULL_FACE);
		glDisable(GL_ALPHA);
		glDisable(GL_BLEND);
	}

};

#endif 
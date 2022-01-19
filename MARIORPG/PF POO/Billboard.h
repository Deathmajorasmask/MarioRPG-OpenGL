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
		//este vector es el que nos dara el ancho del billboard
		//cada vez que lo giremos segun la camara

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

		//habilitamos el culling para reducir tiempo de procesamiento de las texturas
		//las texturas se analizan pixel a pixel para determinar que se imprimen o no
		//por lo que aunque no la veamos nos costo, por eso la eliminamos.
		glEnable(GL_CULL_FACE);
		//hay dos tipos de cull el frontal y el trasero (back)
		glCullFace(GL_FRONT);
		//habilitamos la textura, podriamos mezclar colores y cambiar la tonalidad de la textura
		//con glColorxf
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0);
		glEnable(GL_TEXTURE_2D);
		//usamos modulate para que la textura sea afectada por el valor de la normal en cuanto
		//a luz
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glBindTexture(GL_TEXTURE_2D, billbTextura);
		//calculamos el vector de la camara al billboard
		BillCam = VectorRR(PX - x, PY - y, PZ - z);
		//obtenemos 
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
#ifndef _wata
#define _wata
#include "Geometrias.h"
#include "Imagenes.h"

class Water : public Primitivos, public Imagenes
{

private:
	float anchof;
	float proff;
	float deltax, deltaz;
	float desfase = 0;

public:

	Mesh wata;
	int verx, verz;
	unsigned int planoTextura;

	Water(HWND hWnd, WCHAR alturas[], WCHAR textura[], float ancho, float prof)
	{
		anchof = ancho;
		proff = prof;
		// We load the texture of the figure
		Carga(alturas);
		// If the image pointer is null, this option is created
		wata = Plano(Ancho(), Alto(), ancho, prof, Dir_Imagen(), 30);
		deltax = anchof / Ancho();
		deltaz = proff / Alto();
		verx = Ancho();
		verz = Alto();
		// The gdi texture.
		Descarga();

		Carga(textura);
		glGenTextures(1, &planoTextura);
		glBindTexture(GL_TEXTURE_2D, planoTextura);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, Ancho(), Alto(), GL_RGBA, GL_UNSIGNED_BYTE, Dir_Imagen());
		Descarga();
	}

	~Water()
	{
		delete wata.mesh;
		delete wata.indices;
		glDeleteTextures(1, &planoTextura);
	}

	void Draw()
	{
		desfase += 0.1;
		static float MovS = 0;
		float Altura = 2;
		float Y = Altura * sin(MovS);
		float Amplitud = 0.9;
		glPushAttrib(GL_CURRENT_BIT | GL_TEXTURE_BIT);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_DEPTH_TEST);
		glBindTexture(GL_TEXTURE_2D, planoTextura);

		static float water_factor_min = 0.0f;
		static float water_factor_max = 1.0f;
		static float water_size = 40;
		water_factor_min += .005f;
		water_factor_max += .005f;
		if (water_factor_min>300)
		{
			water_factor_min = 0;
			water_factor_max = 10;
		}

		for (int i = -50; i<50; i++)
		{
			MovS = 0 + desfase;
			Y = Altura * sin(MovS);

			for (int j = -50; j<50; j++)
			{
				glBegin(GL_QUADS);
				glTexCoord2f(water_factor_min, water_factor_min);
				glColor4f(0.1f, 0.3f, 0.6f, 0.2f);
				glVertex3f(j*water_size, Y, i*water_size);

				glTexCoord2f(water_factor_max, water_factor_min);
				glColor4f(0.1f, 0.3f, 0.6f, 0.2f);
				glVertex3f(j*water_size, Y, i*water_size + water_size);


				MovS += Amplitud;
				Y = Altura * sin(MovS);

				glTexCoord2f(water_factor_max, water_factor_max);
				glColor4f(0.1f, 0.3f, 0.6f, 0.2f);
				glVertex3f(j*water_size + water_size, Y, i*water_size + water_size);

				glTexCoord2f(water_factor_min, water_factor_max);
				glColor4f(0.1f, 0.3f, 0.6f, 0.2f);
				glVertex3f(j*water_size + water_size, Y, i*water_size);
				glEnd();
			}
		}

		glDisable(GL_TEXTURE_2D);
		glPopAttrib();
	}
};
#endif 
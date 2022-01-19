//#ifndef _wata
//#define _wata
//#include "Geometrias.h"
//#include "Imagenes.h"
////#include "ShaderDemo.h"
//
//class Water : public Primitivos, public Imagenes
//{
//
//private:
//	float anchof;
//	float proff;
//	float deltax, deltaz;
//	//ShaderDemo *gpuDemo;
//
//public:
//
//	Maya wata;
//	int verx, verz;
//	//el nombre numerico de la textura en cuestion, por lo pronto una
//	unsigned int planoTexturaA;
//
//	Water(HWND hWnd, WCHAR alturas[], WCHAR textura[], float ancho, float prof)
//	{
//		anchof = ancho;
//		proff = prof;
//		//cargamos la textura de la figura
//		Carga(alturas);
//		//en caso del puntero de la imagen sea nulo se brica esta opcion
//		wata = Plano(Ancho(), Alto(), ancho, prof, Dir_Imagen(), 30);
//		deltax = anchof / Ancho();
//		deltaz = proff / Alto();
//		verx = Ancho();
//		verz = Alto();
//		//disponemos la textura del gdi.
//		Descarga();
//
//		Carga(textura);
//		glGenTextures(1, &planoTexturaA);
//		glBindTexture(GL_TEXTURE_2D, planoTexturaA);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
//		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, Ancho(), Alto(), GL_RGBA, GL_UNSIGNED_BYTE, Dir_Imagen());
//		Descarga();
//
//		//gpuDemo = new ShaderDemo("basic.vert", "basic.frag");
//		//gpuDemo->ligador(gpuDemo->vertShader, gpuDemo->fragShader);
//	}
//
//	~Water()
//	{
//		//nos aseguramos de disponer de los recursos previamente reservados
//		delete wata.maya;
//		delete wata.indices;
//		glDeleteTextures(1, &planoTexturaA);
//	}
//
//	void Draw()
//	{
//
//		static float MovS = 0;
//		MovS += .01;
//		float A = sin(MovS) * 2;
//		//glPushAttrib(GL_CURRENT_BIT | GL_TEXTURE_BIT);
//		//glEnable(GL_DEPTH_TEST);
//		glEnable(GL_BLEND);
//		static float water_factor_min = 20.0f;
//		static float water_factor_max = 30.0f;
//		static float water_size = 200;
//		water_factor_min += .01f;
//		water_factor_max += .01f;
//		if (water_factor_min > 1)
//		{
//			water_factor_min = 20.0f;
//			water_factor_max = 30.0f;
//		}
//		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
//		glBindTexture(GL_TEXTURE_2D, planoTexturaA);
//
//		glBegin(GL_QUADS);
//		glTexCoord2f(water_factor_min, water_factor_min);
//		glColor4f(0.1f, 0.3f, 0.6f, 0.2f);
//		glVertex3f(-water_size, A, water_size);
//
//		glTexCoord2f(water_factor_max, water_factor_min);
//		glColor4f(0.1f, 0.3f, 0.6f, 0.2f);
//		glVertex3f(water_size, A, water_size);
//
//		glTexCoord2f(water_factor_max, water_factor_max);
//		glColor4f(0.1f, 0.3f, 0.6f, 0.2f);
//		glVertex3f(water_size, A, -water_size);
//
//		glTexCoord2f(water_factor_min, water_factor_max);
//		glColor4f(0.1f, 0.3f, 0.6f, 0.2f);
//		glVertex3f(-water_size, A, -water_size);
//		glEnd();
//		//glPopAttrib();
//		//glDisable(GL_DEPTH_TEST);
//	}
//};
//
//#endif 
#ifndef _wata
#define _wata
#include "Geometrias.h"
#include "Imagenes.h"
//#include "ShaderDemo.h"

class Water : public Primitivos, public Imagenes
{

private:
	float anchof;
	float proff;
	float deltax, deltaz;
	float desfase = 0;
	//ShaderDemo *gpuDemo;

public:

	Maya wata;
	int verx, verz;
	//el nombre numerico de la textura en cuestion, por lo pronto una
	unsigned int planoTextura;

	Water(HWND hWnd, WCHAR alturas[], WCHAR textura[], float ancho, float prof)
	{
		anchof = ancho;
		proff = prof;
		//cargamos la textura de la figura
		Carga(alturas);
		//en caso del puntero de la imagen sea nulo se brica esta opcion
		wata = Plano(Ancho(), Alto(), ancho, prof, Dir_Imagen(), 30);
		deltax = anchof / Ancho();
		deltaz = proff / Alto();
		verx = Ancho();
		verz = Alto();
		//disponemos la textura del gdi.
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

		//gpuDemo = new ShaderDemo("basic.vert", "basic.frag");
		//gpuDemo->ligador(gpuDemo->vertShader, gpuDemo->fragShader);
	}

	~Water()
	{
		//nos aseguramos de disponer de los recursos previamente reservados
		delete wata.maya;
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


		glPopAttrib();
	}
};
#endif 
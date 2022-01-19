#ifndef _Terrain
#define _Terrain
#include "Geometrias.h"
#include "Imagenes.h"
#include "ShaderDemo.h"
using namespace std;


class Terrain : public Primitivos, public Imagenes
{

private:
	float anchof;
	float proff;
	float deltax, deltaz;
	ShaderDemo *gpuDemo;

public:

	Maya terreno;
	int verx, verz;
	//el nombre numerico de la textura en cuestion, por lo pronto una
	unsigned int planoTextura0;
	unsigned int planoTextura1;
	unsigned int planoTextura2;

	Terrain(HWND hWnd, WCHAR alturas[], WCHAR textura[], WCHAR textura2[], WCHAR textura3[], float ancho, float prof)
	{
		anchof = ancho;
		proff = prof;
		//cargamos la textura de la figura
		Carga(alturas);
		//en caso del puntero de la imagen sea nulo se brica esta opcion
		//terreno = Plano( Ancho(), Alto(), ancho, prof, Dir_Imagen(), 30);	
		terreno = Plano3t(Ancho(), Alto(), ancho, prof, Dir_Imagen(), 30, 00.0, 85.0, 130.0);
		deltax = anchof / Ancho();
		deltaz = proff / Alto();
		verx = Ancho();
		verz = Alto();
		//disponemos la textura del gdi.
		Descarga();
		Carga(textura);
		glGenTextures(1, &planoTextura0);
		glBindTexture(GL_TEXTURE_2D, planoTextura0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, Ancho(), Alto(), GL_RGBA, GL_UNSIGNED_BYTE, Dir_Imagen());
		Descarga();
		Carga(textura2);
		glGenTextures(1, &planoTextura1);
		glBindTexture(GL_TEXTURE_2D, planoTextura1);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, Ancho(), Alto(), GL_RGBA, GL_UNSIGNED_BYTE, Dir_Imagen());
		Descarga();
		Carga(textura3);
		glGenTextures(1, &planoTextura2);
		glBindTexture(GL_TEXTURE_2D, planoTextura2);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, Ancho(), Alto(), GL_RGBA, GL_UNSIGNED_BYTE, Dir_Imagen());
		Descarga();

		gpuDemo = new ShaderDemo("basic.vert", "basic.frag");
		gpuDemo->ligador(gpuDemo->vertShader, gpuDemo->fragShader);
	}

	~Terrain()
	{
		//nos aseguramos de disponer de los recursos previamente reservados
		delete terreno.maya;
		delete terreno.indices;
		glDeleteTextures(1, &planoTextura0);
		glDeleteTextures(1, &planoTextura1);
		glDeleteTextures(1, &planoTextura2);
	}

	void Draw()
	{
		int ind = 0;
		int indice;

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glEnable(GL_TEXTURE_2D);

		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		gpuDemo->use();

		//habilitamos la posibilidad de guardar arreglos de procesamiento inmediato
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		//asignamos punteros de vertices, normales y texturas al buffer de conexiones que sigue
		glVertexPointer(3, GL_FLOAT, sizeof(Vertices), &terreno.maya[0].Posx);
		glNormalPointer(GL_FLOAT, sizeof(Vertices), &terreno.maya[0].Normx);
		glTexCoordPointer(2, GL_FLOAT, sizeof(Vertices), &terreno.maya[0].u);
		glColorPointer(4, GL_FLOAT, sizeof(Vertices), &terreno.maya[0].colorr);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, planoTextura0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, planoTextura1);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, planoTextura2);

		gpuDemo->PonTextura("text1", 0);
		gpuDemo->PonTextura("text2", 1);
		gpuDemo->PonTextura("text3", 2);

		//conectamos todos los vertices previamente cargados a traves de sus punteros para procesarse
		glDrawElements(GL_TRIANGLES, (verx - 1)*(verz - 1) * 6, GL_UNSIGNED_INT, terreno.indices);
		//desocupamos la asignacion para que podamos utilizarlo con un nuevo elemento

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisable(GL_CULL_FACE);
		glDisable(GL_BACK);

		gpuDemo->desuse();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, NULL);
		//glDisable(GL_TEXTURE_2D);

	}

	float Superficie(float x, float z)
	{
		//obtenemos el indice pero podria incluir una fraccion
		float indicefx = (x + anchof / 2) / deltax;
		float indicefz = (z + proff / 2) / deltaz;
		//nos quedamos con solo la parte entera del indice
		int indiceix = (int)indicefx;
		int indiceiz = (int)indicefz;
		//nos quedamos con solo la fraccion del indice
		float difx = indicefx - indiceix;
		float difz = indicefz - indiceiz;

		float altura;
		float D;

		//el cuadro del terreno esta formado por dos triangulos, si difx es mayor que dify 
		//entonces estamos en el triangulo de abajo en caso contrario arriba
		if (difx > difz)
		{
			//obtenemos el vector 1 de dos que se necesitan
			VectorRR v1(terreno.maya[indiceix + 1 + (indiceiz + 1) * verx].Posx - terreno.maya[indiceix + indiceiz * verx].Posx,
				terreno.maya[indiceix + 1 + (indiceiz + 1) * verx].Posy - terreno.maya[indiceix + indiceiz * verx].Posy,
				terreno.maya[indiceix + 1 + (indiceiz + 1) * verx].Posz - terreno.maya[indiceix + indiceiz * verx].Posz);
			//obtenemos el vector 2 de dos
			VectorRR v2(terreno.maya[indiceix + 1 + indiceiz * verx].Posx - terreno.maya[indiceix + indiceiz * verx].Posx,
				terreno.maya[indiceix + 1 + indiceiz * verx].Posy - terreno.maya[indiceix + indiceiz * verx].Posy,
				terreno.maya[indiceix + 1 + indiceiz * verx].Posz - terreno.maya[indiceix + indiceiz * verx].Posz);

			//con el producto punto obtenemos la normal y podremos obtener la ecuacion del plano
			//la parte x de la normal nos da A, la parte y nos da B y la parte z nos da C
			VectorRR normalPlano = Cruz(v1, v2);
			//entonces solo falta calcular D
			D = -1 * (normalPlano.X * terreno.maya[indiceix + indiceiz * verx].Posx +
				normalPlano.Y * terreno.maya[indiceix + indiceiz * verx].Posy +
				normalPlano.Z * terreno.maya[indiceix + indiceiz * verx].Posz);
			//sustituyendo obtenemos la altura de contacto en el terreno
			altura = ((-normalPlano.X * x - normalPlano.Z * z - D) / normalPlano.Y);
		}
		else
		{
			VectorRR v1(terreno.maya[indiceix + (indiceiz + 1) * verx].Posx - terreno.maya[indiceix + indiceiz * verx].Posx,
				terreno.maya[indiceix + (indiceiz + 1) * verx].Posy - terreno.maya[indiceix + indiceiz * verx].Posy,
				terreno.maya[indiceix + (indiceiz + 1) * verx].Posz - terreno.maya[indiceix + indiceiz * verx].Posz);

			VectorRR v2(terreno.maya[indiceix + 1 + (indiceiz + 1) * verx].Posx - terreno.maya[indiceix + indiceiz * verx].Posx,
				terreno.maya[indiceix + 1 + (indiceiz + 1)* verx].Posy - terreno.maya[indiceix + indiceiz * verx].Posy,
				terreno.maya[indiceix + 1 + (indiceiz + 1)* verx].Posz - terreno.maya[indiceix + indiceiz * verx].Posz);


			VectorRR normalPlano = Cruz(v1, v2);

			D = -1 * (normalPlano.X * terreno.maya[indiceix + indiceiz * verx].Posx +
				normalPlano.Y * terreno.maya[indiceix + indiceiz * verx].Posy +
				normalPlano.Z * terreno.maya[indiceix + indiceiz * verx].Posz);

			altura = ((-normalPlano.X * x - normalPlano.Z * z - D) / normalPlano.Y);
		}

		return altura;

	}
};

#endif 
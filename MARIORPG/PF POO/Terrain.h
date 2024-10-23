#ifndef _Terrain
#define _Terrain
#include "Geometrias.h"
#include "Imagenes.h"
#include "ShaderDemo.h"
using namespace std;

// Terraint Multi - Texture
class Terrain : public Primitivos, public Imagenes
{

private:
	float anchof;
	float proff;
	float deltax, deltaz;
	ShaderDemo *gpuDemo;

public:

	Mesh terreno;
	int verx, verz;
	unsigned int planoTextura0;
	unsigned int planoTextura1;
	unsigned int planoTextura2;

	Terrain(HWND hWnd, WCHAR alturas[], WCHAR textura[], WCHAR textura2[], WCHAR textura3[], float ancho, float prof)
	{
		anchof = ancho;
		proff = prof;
		// We load the texture of the figure
		Carga(alturas);
		// If the image pointer is null, this option is created
		//terreno = Plano( Ancho(), Alto(), ancho, prof, Dir_Imagen(), 30);	
		terreno = Plano3t(Ancho(), Alto(), ancho, prof, Dir_Imagen(), 30, 00.0, 85.0, 130.0);
		deltax = anchof / Ancho();
		deltaz = proff / Alto();
		verx = Ancho();
		verz = Alto();
		// The gdi texture.
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

		gpuDemo = new ShaderDemo("shaders//basic.vert", "shaders//basic.frag");
		gpuDemo->ligador(gpuDemo->vertShader, gpuDemo->fragShader);
	}

	~Terrain()
	{
		delete terreno.mesh;
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
		glEnable(GL_DEPTH_TEST);

		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		gpuDemo->use();

		// We enable the ability to save immediate processing arrangements
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		// Assign vertex, normal and texture pointers to the connection buffer
		glVertexPointer(3, GL_FLOAT, sizeof(Vertex), &terreno.mesh[0].Posx);
		glNormalPointer(GL_FLOAT, sizeof(Vertex), &terreno.mesh[0].Normx);
		glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), &terreno.mesh[0].u);
		glColorPointer(4, GL_FLOAT, sizeof(Vertex), &terreno.mesh[0].colorr);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, planoTextura0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, planoTextura1);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, planoTextura2);

		gpuDemo->PonTextura("text1", 0);
		gpuDemo->PonTextura("text2", 1);
		gpuDemo->PonTextura("text3", 2);

		// We connect all previously loaded vertices through their pointers to be processed
		glDrawElements(GL_TRIANGLES, (verx - 1)*(verz - 1) * 6, GL_UNSIGNED_INT, terreno.indices);
		// We clear the allocation so we can use it with a new element

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisable(GL_CULL_FACE);
		glDisable(GL_BACK);

		gpuDemo->desuse();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, NULL);
		glDisable(GL_TEXTURE_2D);

	}

	float Superficie(float x, float z)
	{
		//// We get the index but it could include a fraction
		float indicefx = (x + anchof / 2) / deltax;
		float indicefz = (z + proff / 2) / deltaz;
		// The entire index part.
		int indiceix = (int)indicefx;
		int indiceiz = (int)indicefz;
		// The index fraction
		float difx = indicefx - indiceix;
		float difz = indicefz - indiceiz;

		float altura;
		float D;

		/*The terrain square is made up of two triangles, if difx is greater than dify then we are in the bottom triangle, otherwise up.*/
		if (difx > difz)
		{
			// We obtain vector 1 of two that are needed
			VectorRR v1(terreno.mesh[indiceix + 1 + (indiceiz + 1) * verx].Posx - terreno.mesh[indiceix + indiceiz * verx].Posx,
				terreno.mesh[indiceix + 1 + (indiceiz + 1) * verx].Posy - terreno.mesh[indiceix + indiceiz * verx].Posy,
				terreno.mesh[indiceix + 1 + (indiceiz + 1) * verx].Posz - terreno.mesh[indiceix + indiceiz * verx].Posz);
			// We obtain vector 2 of two that are needed
			VectorRR v2(terreno.mesh[indiceix + 1 + indiceiz * verx].Posx - terreno.mesh[indiceix + indiceiz * verx].Posx,
				terreno.mesh[indiceix + 1 + indiceiz * verx].Posy - terreno.mesh[indiceix + indiceiz * verx].Posy,
				terreno.mesh[indiceix + 1 + indiceiz * verx].Posz - terreno.mesh[indiceix + indiceiz * verx].Posz);

			/*With the dot product we obtain the normal and we can obtain the equation of the plane, 
			the x part of the normal gives us A, the y part gives us B and the z part gives us C*/
			VectorRR normalPlano = Cruz(v1, v2);
			// Calculate D
			D = -1 * (normalPlano.X * terreno.mesh[indiceix + indiceiz * verx].Posx +
				normalPlano.Y * terreno.mesh[indiceix + indiceiz * verx].Posy +
				normalPlano.Z * terreno.mesh[indiceix + indiceiz * verx].Posz);
			// substituting we obtain the height of contact with the ground
			altura = ((-normalPlano.X * x - normalPlano.Z * z - D) / normalPlano.Y);
		}
		else
		{
			VectorRR v1(terreno.mesh[indiceix + (indiceiz + 1) * verx].Posx - terreno.mesh[indiceix + indiceiz * verx].Posx,
				terreno.mesh[indiceix + (indiceiz + 1) * verx].Posy - terreno.mesh[indiceix + indiceiz * verx].Posy,
				terreno.mesh[indiceix + (indiceiz + 1) * verx].Posz - terreno.mesh[indiceix + indiceiz * verx].Posz);

			VectorRR v2(terreno.mesh[indiceix + 1 + (indiceiz + 1) * verx].Posx - terreno.mesh[indiceix + indiceiz * verx].Posx,
				terreno.mesh[indiceix + 1 + (indiceiz + 1)* verx].Posy - terreno.mesh[indiceix + indiceiz * verx].Posy,
				terreno.mesh[indiceix + 1 + (indiceiz + 1)* verx].Posz - terreno.mesh[indiceix + indiceiz * verx].Posz);


			VectorRR normalPlano = Cruz(v1, v2);

			D = -1 * (normalPlano.X * terreno.mesh[indiceix + indiceiz * verx].Posx +
				normalPlano.Y * terreno.mesh[indiceix + indiceiz * verx].Posy +
				normalPlano.Z * terreno.mesh[indiceix + indiceiz * verx].Posz);

			altura = ((-normalPlano.X * x - normalPlano.Z * z - D) / normalPlano.Y);
		}

		return altura;

	}
};

#endif 
#ifndef _Sky
#define _Sky
#include "Geometrias.h"
#include "Imagenes.h"

class SkyDome:public Primitivos, public Imagenes
{
public:
	Mesh cuadro;
	int st, sl;
	unsigned int esferaTextura;	

	SkyDome(HWND hWnd, int stacks, int slices, float radio, WCHAR nombre[])
	{
		this->hWnd=hWnd;
		cuadro=Esfera(stacks, slices, radio, 0.5, 1);
		st=stacks;
		sl=slices;
		//We load the texture of the figure
		Carga(nombre);		
		//If the image pointer is null, this option is created
		if (Dir_Imagen())
		{
			glGenTextures(1, &esferaTextura);
			glBindTexture(GL_TEXTURE_2D, esferaTextura);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST_MIPMAP_LINEAR);
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST_MIPMAP_LINEAR);
			gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, Ancho(), Alto(), GL_RGBA, GL_UNSIGNED_BYTE, Dir_Imagen());
			//glDeleteTextures(1, &esferaTextura);
			//The gdi texture.
			Descarga();
		}
	}

	~SkyDome()
	{
		delete cuadro.mesh;
		delete cuadro.indices;
		glDeleteTextures(1, &esferaTextura);
	}

	void Draw()
	{
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glDisable(GL_DEPTH_TEST);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		glBindTexture(GL_TEXTURE_2D, esferaTextura);
		//We enable the ability to save immediate processing arrangements
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		
		//Assign vertex, normal and texture pointers to the connection buffer
		glVertexPointer(3, GL_FLOAT, sizeof(Vertex), &cuadro.mesh[0].Posx);		
		glNormalPointer(GL_FLOAT, sizeof(Vertex), &cuadro.mesh[0].Normx);		
		glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), &cuadro.mesh[0].u);
		
		//We connect all previously loaded vertices through their pointers to be processed
		glDrawElements(GL_TRIANGLES, (sl-1)*(st-1)*6, GL_UNSIGNED_INT, cuadro.indices);
		//We clear the allocation so we can use it with a new element
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);		
		glDisable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		//glDeleteTextures(1, &esferaTextura);
		glDisable(GL_TEXTURE_2D);
	}
};
#endif
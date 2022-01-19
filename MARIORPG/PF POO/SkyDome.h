#ifndef _Sky
#define _Sky
#include "Geometrias.h"
#include "Imagenes.h"

class SkyDome:public Primitivos, public Imagenes
{
public:
	Maya cuadro;
	int st, sl;
	unsigned int esferaTextura;	

	SkyDome(HWND hWnd, int stacks, int slices, float radio, WCHAR nombre[])
	{
		this->hWnd=hWnd;
		cuadro=Esfera(stacks, slices, radio, 0.5, 1);
		st=stacks;
		sl=slices;
		//cargamos la textura de la figura
		Carga(nombre);		
		//en caso del puntero de la imagen sea nulo se brica esta opcion
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
			//disponemos la textura del gdi.
			Descarga();
		}
	}

	~SkyDome()
	{
		//nos aseguramos de disponer de los recursos previamente reservados
		delete cuadro.maya;
		delete cuadro.indices;
		glDeleteTextures(1, &esferaTextura);
	}

	void Draw()
	{
		
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glDisable(GL_DEPTH_TEST);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		glBindTexture(GL_TEXTURE_2D, esferaTextura);
		//habilitamos la posibilidad de guardar arreglos de procesamiento inmediato
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		
		//asignamos punteros de vertices, normales y texturas al buffer de conexiones que sigue
		glVertexPointer(3, GL_FLOAT, sizeof(Vertices), &cuadro.maya[0].Posx);		
		glNormalPointer(GL_FLOAT, sizeof(Vertices), &cuadro.maya[0].Normx);		
		glTexCoordPointer(2, GL_FLOAT, sizeof(Vertices), &cuadro.maya[0].u);
		
		//conectamos todos los vertices previamente cargados a traves de sus punteros para procesarse
		glDrawElements(GL_TRIANGLES, (sl-1)*(st-1)*6, GL_UNSIGNED_INT, cuadro.indices);
		//desocupamos la asignacion para que podamos utilizarlo con un nuevo elemento
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);		
		glDisable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		//glDeleteTextures(1, &esferaTextura);

	}
};
#endif
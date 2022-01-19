#ifndef imageness
#define imageness
//Clase desarrollada por Rafael Rosas para los amazing LMADs
//POO C++
//carga imagenes y las asigna al OpenGL como texturas.

#include <gdiplus.h>
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <exception>
#pragma comment(lib,"gdiplus.lib")
using namespace Gdiplus;

class Imagenes {
public:

	HWND hWnd;

	Imagenes()
	{
	}

	~Imagenes()
	{
	}
private:
	unsigned char *dir_imagen, *primero;
	unsigned int ancho;
	unsigned int alto;

public:
	void Carga(WCHAR nombre[])
	{
		GdiplusStartupInput gdiplusStartupInput;
		ULONG_PTR     gdiplusToken;
		GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);


		Bitmap* bitmap = new Bitmap(nombre);
		BitmapData* bitmapData = new BitmapData;

		ancho = bitmap->GetWidth();
		alto = bitmap->GetHeight();

		Rect rect(0, 0, ancho, alto);

		bitmap->LockBits(&rect, ImageLockModeRead, PixelFormat32bppARGB, bitmapData);

		unsigned char* pixels = (unsigned char*)bitmapData->Scan0;

		int tamaño;
		tamaño = ancho*alto * 4;
		//hagamos un try de la reserva de memoria
		try
		{
			dir_imagen = new unsigned char[tamaño]; //[tamaño*1000000]; ponganle esto como prueba
			primero = dir_imagen;
		}
		//en caso de falla entonces
		catch (std::exception& e)
		{
			//nosotros sabemos donde se genero el error entonces le diremos al usuario
			int msgboxID = MessageBox(hWnd, "Insuficiente memoria para contener la textura",
				(LPCSTR)"Clase Imagenes", MB_ICONWARNING | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2);
			//interpretemos el message box y hagamos algo adecuado a la opcion seleccionada
			switch (msgboxID)
			{
				//de plano pa'juera o para afuera?, no me acuerdo!
			case IDCANCEL:
				exit(0);
				break;
				//un nuevo intento con una textura mas pequeño en todo caso
				//si no alcanza pa los tacos tonces pa la tortilla, que me pasa? ya comí?
			case IDTRYAGAIN:
				try {
					dir_imagen = new unsigned char[tamaño];
					primero = dir_imagen;
				}
				catch (std::bad_alloc &e)
				{
					//en caso de no existir ni la menor pues algo mas se podra hacer.
				}
				break;
			case IDCONTINUE:
				//indicamos que continue si la textura y lo indicamos con nulo en el puntero para
				//que se interprete despues
				dir_imagen = 0;
				primero = 0;
				break;
			}

		}

		//tenemos que invertir el blue por el red
		//el green se conserva en posicion
		for (unsigned int i = 0; i<(alto*ancho * 4); i += 4)
		{
			dir_imagen[i + 2] = pixels[i];
			dir_imagen[i + 1] = pixels[i + 1];
			dir_imagen[i] = pixels[i + 2];
			dir_imagen[i + 3] = pixels[i + 3];
		}

		bitmap->UnlockBits(bitmapData);

		delete bitmapData;
		delete bitmap;

		GdiplusShutdown(gdiplusToken);
	}

	void Descarga()
	{
		//se deshace de la memoria asignada para contener la imagen
		delete[] dir_imagen;
	}

	unsigned char *Dir_Imagen()
	{
		//devuelve el puntero
		return primero;
	}

	unsigned int Ancho()
	{
		//devuelve el ancho
		return ancho;
	}

	unsigned int Alto()
	{
		//devuelve el alto
		return alto;
	}
};
#endif
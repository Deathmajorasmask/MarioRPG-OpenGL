#ifndef imageness
#define imageness

#include <gdiplus.h>
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <exception>
#pragma comment(lib,"gdiplus.lib")
using namespace Gdiplus;

// Loads images and assigns them to OpenGL as textures.

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
		try
		{
			dir_imagen = new unsigned char[tamaño]; //[tamaño*1000000];
			primero = dir_imagen;
		}
		//Error catch
		catch (std::exception& e)
		{
			int msgboxID = MessageBox(hWnd, "Insufficient memory to hold the texture",
				(LPCSTR)"Imagenes Class", MB_ICONWARNING | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2);
			//Read Message Box result
			switch (msgboxID)
			{
			case IDCANCEL:
				exit(0);
				break;
				// Try small texture
			case IDTRYAGAIN:
				try {
					dir_imagen = new unsigned char[tamaño];
					primero = dir_imagen;
				}
				catch (std::bad_alloc &e)
				{

				}
				break;
			case IDCONTINUE:
				dir_imagen = 0;
				primero = 0;
				break;
			}

		}

		// Invert the blue for the red, green remains in position
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
		delete[] dir_imagen;
	}

	unsigned char *Dir_Imagen()
	{
		return primero;
	}

	unsigned int Ancho()
	{
		return ancho;
	}

	unsigned int Alto()
	{
		return alto;
	}
};
#endif
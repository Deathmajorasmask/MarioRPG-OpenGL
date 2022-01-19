#include<Windows.h>
#include "glew.h"
#include <gl\GLU.h>
#include <gl\GL.h>
#include "Scene.h"
#include <time.h>
#include "GamePadRR.h"
#include "Animations.h"
#include "resources.h"
#pragma comment (lib, "glew32.lib") 
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib") 

#define Timer1 100

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void DefPixelFormat(HDC hDC);

HDC hContextoVentana;
Scene *scene;
GamePadRR *gamPad;
bool renderiza = false;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hwndVentana;
	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX); //Tamaño en bytes de la estructura.
	wc.style = CS_HREDRAW | CS_VREDRAW; //Entero de 16 bits que codifica el estilo de la clase de ventana.
	wc.lpfnWndProc = WindowProc;//Apunta al procedimiento de ventana.
	wc.hInstance = hInstance;//Identifica la instancia de la ventana a la que esta clase pertenece.
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);//Identificador del curso de la clase. Debe ser un manipulador de un recurso de tipo icono. Si es Null, la aplicación mostrará un icono cuando el usuario minice la ventana de la aplicación.
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW; //Identificador del pincel para la clase.
	wc.lpszClassName = "ProjectRPG"; //Especifica el nombre de la clase ventana.
	RegisterClassEx(&wc);//Registra una clase de ventana para su uso subsecuente en llamadas a las funciones CreateWindow o CreateWindowEx
	RECT wr = { 0, 0, 1080, 720 };
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);//Calcula el tamaño necesario del rectángulo de la ventana.

	//Se crea la ventana definida previamente.
	hwndVentana = CreateWindowEx(NULL,//estilo extendido de ventana
		"ProjectRPG",//puntero al nombre de la clase registrada *visto arriba*
		"Mario RPG C++ OpenGL",//puntero al nombre de la ventana
		WS_OVERLAPPEDWINDOW,//estilo de ventana
		100,//posición horizontal de la ventana
		100,//posición vertical de la ventana
		wr.right - wr.left,//ancho de la ventana
		wr.bottom - wr.top,//alto de la ventana
		NULL,//manejador de la ventana padre o propietaria
		NULL,//manejador del menu o identificador de ventana hija
		hInstance,//manejador de la instancia de la aplicación
		NULL);//puntero a los datos de creación de la ventana

	ShowWindow(hwndVentana, nCmdShow);//Muestra la ventana creada
	
	glewInit();//Inicializa glew

	//Instancia de la escena
	scene = new Scene(hwndVentana);
	gamPad = new GamePadRR(1);
	

	//Crear un timer con el valor especificado de time-out
	SetTimer(hwndVentana,//Manejador de ventana que recibirá los mensajes del timer
		Timer1,//identificador del timer
		30,//valor de time-out
		NULL);//dirección del procedimiento de timer

	MSG msg = { 0 };
	while (TRUE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
				break;
		}
		else
		{
			if (renderiza)
			{
			
				scene->render(hContextoVentana,hwndVentana);
				renderiza = false;

				if (gamPad->IsConnected()) {

					if (gamPad->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_A) {
						//MessageBox(hwndVentana, "Presiono A", "Mensaje", MB_OK);
					}
					if (gamPad->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_B) {
						//MessageBox(hwndVentana, "Presiono A", "Mensaje", MB_OK);
						if (scene->battlereturn()) {
							scene->pressB();
						}
					}
					if (gamPad->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_X) {
						//MessageBox(hwndVentana, "Presiono A", "Mensaje", MB_OK);
						
					}
					if (gamPad->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_Y) {
						//MessageBox(hwndVentana, "Presiono A", "Mensaje", MB_OK);
					}
					if (gamPad->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) {
						//MessageBox(hwndVentana, "Presiono A", "Mensaje", MB_OK);
						if (scene->battlereturn()) {
							scene->pressUp();
						}
						else {
							scene->moveBackward();
						}
						
					}
					if (gamPad->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) {
						//MessageBox(hwndVentana, "Presiono A", "Mensaje", MB_OK);
						if (scene->battlereturn()) {
							scene->pressDown();
						}
						else {
							scene->moveForward();
						}
						
					}
					if (gamPad->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) {
						//MessageBox(hwndVentana, "Presiono A", "Mensaje", MB_OK);
						if (scene->battlereturn()) {

						}
						else {
							scene->moveRight();
						}
						
					}
					if (gamPad->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) {
						//MessageBox(hwndVentana, "Presiono A", "Mensaje", MB_OK);
						if (scene->battlereturn()) {

						}
						else {
							scene->moveLeft();
						}
						
					}
					
				}
				else{
				//	//aqui ponemos un messgaebox para decir que se perdio la conexion con el gamepad
				}

			}
		}
	}

	return msg.wParam;

}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HGLRC hContextoGL;
	static HDC hContextoAux;
	int ancho, alto;
	char epx[6] = "";
	char epz[6] = "";
	char epy[6] = "";
	char edx[6] = "";
	char edz[6] = "";
	char edy[6] = "";
	char ec[80] = "";

	switch (message)
	{
	case WM_CREATE:
		hContextoAux = GetDC(hWnd);
		hContextoVentana = hContextoAux;
		DefPixelFormat(hContextoVentana);
		hContextoGL = wglCreateContext(hContextoVentana);
		wglMakeCurrent(hContextoVentana, hContextoGL);
		srand(time(NULL));

		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_RETURN:
			MessageBox(hWnd, "Mensaje", "Titulo", MB_OK);
			return 0;
		case VK_UP:
			scene->turnUp();
			renderiza = true;
			return 0;
		case VK_DOWN:
			scene->turnDown();
			renderiza = true;
			return 0;
		case VK_LEFT:
			scene->turnLeft();
			renderiza = true;
			return 0;
		case VK_RIGHT:
			scene->turnRight();
			renderiza = true;
			return 0;
		case 0x44: //D
			if (scene->battlereturn()) {

			}
			else {
				scene->moveRight();
				scene->manageAnimationMario(1);
			}
			renderiza = true;
			return 0;
		case 0x41: //A
			if (scene->battlereturn()) {

			}
			else {
				scene->moveLeft();
				scene->manageAnimationMario(1);
			}
			renderiza = true;
			return 0;
		case 0x53: //S
			if (scene->battlereturn()) {
				scene->pressDown();
			}
			else {
				scene->moveForward();
				scene->manageAnimationMario(1);
			}
			renderiza = true;
			return 0;
		case 0x57: //W
			if (scene->battlereturn()) {
				scene->pressUp();
			}
			else {
				scene->moveBackward();
				scene->manageAnimationMario(1);
			}
			renderiza = true;
			return 0;
		case 69: //E
			scene->moveUp();
			renderiza = true;
			return 0;
		case 81: //Q
			scene->moveDown();
			renderiza = true;
			return 0;
		case 74: //J
			if (scene->victoriaAbsurda()) {
				MessageBox(hWnd, "Deberias sentirte sucio al pasar la beta con trucos", "Tramposo", MB_OK);
			}

			return 0;
		case 75: //k
			scene->switrenderMulti();
			return 0;
		case 76://L
			if (scene->battlereturn()) {
				if (scene->turnMarioReturn()) {
					scene->pressB();
				}
			}
			return 0;
		case 79: //O
			scene->switCamareO(); //regresar Camara normal
			return 0;

		case 80: //P
			scene->switCamareC(); //regresar Camara normal
			return 0;




		}
	case WM_TIMER:
	/*	if (animatic == true) {
			scale_anim += .01;
			if (scale_anim >= 1.5) {
				animatic = false;
			}
		}
		if (animatic == false) {
			scale_anim -= .01;
			if (scale_anim <= 0) {
				animatic = true;
			}
		}
*/

		renderiza = true;
		break;
	case WM_DESTROY:
	{
		KillTimer(hWnd, Timer1);
		delete scene->skyDay;
		delete scene->terrain;
		
		wglMakeCurrent(hContextoVentana, NULL);
		wglDeleteContext(hContextoGL);
		PostQuitMessage(0);
		return 0;
	} break;

	case WM_SIZE:
	{
		alto = HIWORD(lParam);
		ancho = LOWORD(lParam);
		if (alto == 0)
			alto = 1;
		glViewport(0, 0, ancho, alto);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0f, (GLfloat)ancho / (GLfloat)alto, 1.0f, 10000.0f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
	break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

void DefPixelFormat(HDC hDC)
{
	int bestmatch;

	static PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR), //tamaño de la estructura
		1, //numero de version
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, //soporta la ventana, el opengl y manejara doble buffer
		PFD_TYPE_RGBA, //formato de 32 bits rgba
		32, //tamaño del color en 32 bits
		0, 0, 0, 0, 0, 0, //bits de color, no se usan
		0, //no hay buffer para el alfa
		0, //ignore el bit de corrimiento
		0, //no hay buffer de acumulacion
		0, 0, 0, 0, //no hay bits de acumulacion
		16, //tamaño del flotante para el buffer z
		0, //no hay buffers de stencil
		0, //no hay buffers auxiliares
		PFD_MAIN_PLANE, //plano principal para dibujo
		0, //reservado
		0, 0, 0 //mascaras de capas ignoradas
	};

	bestmatch = ChoosePixelFormat(hDC, &pfd);
	SetPixelFormat(hDC, bestmatch, &pfd);
}

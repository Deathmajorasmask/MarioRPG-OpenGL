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
	wc.cbSize = sizeof(WNDCLASSEX); // Size in bytes of the structure.
	wc.style = CS_HREDRAW | CS_VREDRAW; // 16-bit integer that encodes the style of the window class.
	wc.lpfnWndProc = WindowProc;// Windows Procedure
	wc.hInstance = hInstance;// Identifies the window instance to which this class belongs.
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);// Class course identifier. It must be a handler of an icon type resource. If Null, the application will display an icon when the user minimizes the application window.
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW; // Brush identifier for the class.
	wc.lpszClassName = "ProjectRPG"; // Specifies the name of the window class.
	RegisterClassEx(&wc);// Registers a window class for subsequent use in calls to the CreateWindow or CreateWindowEx functions
	RECT wr = { 0, 0, 1080, 720 }; // Size Windows Default 1080 x 720
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);// Calculate the necessary size of the window rectangle.

	// The previously defined window is created.
	hwndVentana = CreateWindowEx(NULL, // extended window style
		"ProjectRPG",// Specifies the name of the window class.
		"Mario RPG C++ OpenGL",// Specifies the name of the window class.
		WS_OVERLAPPEDWINDOW,// Window style
		100,// horizontal window position
		100,// Vertical window position
		wr.right - wr.left,// window width
		wr.bottom - wr.top,// window height
		NULL,// parent window handler
		NULL,// menu handle or child window identifier
		hInstance,// application instance handler
		NULL);// pointer to window creation data

	ShowWindow(hwndVentana, nCmdShow);// Show windows created
	
	glewInit();//Init glew

	// Scene instance
	scene = new Scene(hwndVentana);
	gamPad = new GamePadRR(1);
	

	// Create a timer with the specified time-out value
	SetTimer(hwndVentana,// Window handler that will receive timer messages
		Timer1,// timer identifier
		30,// timeout value
		NULL);// direction of timer procedure

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
				MessageBox(hWnd, "You should feel dirty passing the beta with cheats", "Cheating", MB_OK);
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
		sizeof(PIXELFORMATDESCRIPTOR), // structure size
		1, // version number
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, // supports window, opengl and will handle double buffering
		PFD_TYPE_RGBA, // 32 bit rgba format
		32, // color size in 32 bits
		0, 0, 0, 0, 0, 0, // color bits (not used)
		0, // no buffer for alpha
		0, // ignore the shift bit
		0, //no accumulation buffer
		0, 0, 0, 0, // no accumulation bits
		16, // float size for z buffer
		0, // no stencil buffers
		0, // no auxiliary buffers
		PFD_MAIN_PLANE, //plano principal para dibujo
		0, //reserved
		0, 0, 0 //ignored layer masks
	};

	bestmatch = ChoosePixelFormat(hDC, &pfd);
	SetPixelFormat(hDC, bestmatch, &pfd);
}

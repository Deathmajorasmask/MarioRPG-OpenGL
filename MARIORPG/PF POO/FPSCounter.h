#pragma once

#include <windows.h>
#include <chrono>  // Para medir tiempo

class FPSCounter
{
private:
	int frame = 0;         // Contador de cuadros
	double fps = 0.0;        // Almacenar los FPS
	DWORD lastTime = 0;  // Último tiempo en milisegundos
public:
	FPSCounter();
	~FPSCounter();

	double FPS_WM_TIMER();
};
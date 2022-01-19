#ifndef _XBOX_CONTROLLER_H_
#define _XBOX_CONTROLLER_H_

//no agrega en la compilada drivers de comunicaciones y otras cosas
#define WIN32_LEAN_AND_MEAN

// Incluimos estas librerias para avanzar
#include <windows.h>
#include <XInput.h> //libreria del Xbox solo gamepads o joysticks compatibles
#pragma comment(lib, "XInput.lib")
// XBOX Controller Class Definition
class GamePadRR
{

private:
    XINPUT_STATE estadoControlador;
    int numeroControlador;

public:
    GamePadRR(int jugadorNumero)
	{
		// establece el numero de jugador
		numeroControlador = jugadorNumero - 1;
	}

    XINPUT_STATE GetState()
	{
		// limpia la estructura del estado del gamepad
		ZeroMemory(&estadoControlador, sizeof(XINPUT_STATE));

		// obtiene el estado del gamepad
		XInputGetState(numeroControlador, &estadoControlador);

		return estadoControlador;
	}

    bool IsConnected()
	{
		// limpia la estructura de estado
		ZeroMemory(&estadoControlador, sizeof(XINPUT_STATE));

		// obtiene el estado
		DWORD Resultado = XInputGetState(numeroControlador, &estadoControlador);

		if(Resultado == ERROR_SUCCESS)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

    void Vibrate(int leftVal = 0, int rightVal = 0)
	{
    // Createl estado de vibracion
    XINPUT_VIBRATION Vibracion;

    // limpia los valores previos de la estructura
    ZeroMemory(&Vibracion, sizeof(XINPUT_VIBRATION));

    // establece los valores de vibracion
    Vibracion.wLeftMotorSpeed = leftVal;
    Vibracion.wRightMotorSpeed = rightVal;

    // Vibra el controlador
    XInputSetState(numeroControlador, &Vibracion);
	}
	//estas son las equivalencias a los botonazos mas comunes
	/*XINPUT_GAMEPAD_DPAD_UP          0x00000001
	XINPUT_GAMEPAD_DPAD_DOWN        0x00000002
	XINPUT_GAMEPAD_DPAD_LEFT        0x00000004
	XINPUT_GAMEPAD_DPAD_RIGHT       0x00000008
	XINPUT_GAMEPAD_START            0x00000010
	XINPUT_GAMEPAD_BACK             0x00000020
	XINPUT_GAMEPAD_LEFT_THUMB       0x00000040
	XINPUT_GAMEPAD_RIGHT_THUMB      0x00000080
	XINPUT_GAMEPAD_LEFT_SHOULDER    0x0100
	XINPUT_GAMEPAD_RIGHT_SHOULDER   0x0200
	XINPUT_GAMEPAD_A                0x1000
	XINPUT_GAMEPAD_B                0x2000
	XINPUT_GAMEPAD_X                0x4000
	XINPUT_GAMEPAD_Y                0x8000*/
};

#endif
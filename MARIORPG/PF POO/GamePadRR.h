#ifndef _XBOX_CONTROLLER_H_
#define _XBOX_CONTROLLER_H_

// Reduces the size of the Win32 header files by excluding some of the less frequently used APIs
// #define WIN32_LEAN_AND_MEAN

#include <windows.h>
// Xbox library only compatible gamepads or joysticks
#include <XInput.h>
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
		// Player number
		numeroControlador = jugadorNumero - 1;
	}

	XINPUT_STATE GetState()
	{
		// Clear gamepad state structure
		ZeroMemory(&estadoControlador, sizeof(XINPUT_STATE));

		// Get gamepad status
		XInputGetState(numeroControlador, &estadoControlador);

		return estadoControlador;
	}

	bool IsConnected()
	{
		// Clear the state structure
		ZeroMemory(&estadoControlador, sizeof(XINPUT_STATE));

		// Get gamepad status
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
	// Create vibration state
	XINPUT_VIBRATION Vibracion;

	// Clears the previous values ​​of the structure
	ZeroMemory(&Vibracion, sizeof(XINPUT_VIBRATION));

	// Set vibration values
	Vibracion.wLeftMotorSpeed = leftVal;
	Vibracion.wRightMotorSpeed = rightVal;

	// Vibrates the controller
	XInputSetState(numeroControlador, &Vibracion);
	}

};

	// LIST BUTTONS COMMONS
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

#endif
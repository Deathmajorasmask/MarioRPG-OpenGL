#ifndef __Camera
#define __Camera

#include "VectorRR.h"
#include "Animations.h"

//Aqui colocar las fisicas y colisiones
class Camera: public VectorRR, public Animatic
{

public:

	GLdouble px,py, pz, dx, dy, dz,
	ux, uy, uz;
	
	int camind = 0;

	Camera()
	{
	}

	/*void CamaraUpdate()
	{
		gluLookAt(posc.X, posc.Y + 10, posc.Z - 10,
			dirc.X, dirc.Y + 10, dirc.Z,
			0, 1, 0);
	}*/

	void cameraInitialize()
	{

		// dx = -1, dy = 102.5, dz = 42;
		//COMPARACIÓN AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
		//px = 0, py = 23, pz = 0, dx = 0, dy = 30, dz = -25;
		//dx -25 dy104 dz34
		//float mx = -1, mz = 42, my = 102.5
		px = -12, py = 112, pz = 51, dx = 3, dy = 102, dz = 38;
		ux = 0, uy = 1, uz = 0;
		gluLookAt(px, py, pz, dx, dy, dz, ux, uy, uz);
	}
	//Las coordenadas 'P' son el Eye (position), Coordenadas 'D' (observation)

	void cameraUpdate()
	{
		gluLookAt(px, py, pz, dx, dy, dz, ux, uy, uz);
	}

	//-6, 129, 17
	void cameraBattle() {
		px = -12, py = 66, pz = 51, dx = -24, dy = 61, dz = 38;
		ux = 0, uy = 1, uz = 0;
	}

	void cameraWin() {
		px = -12;
		py = 112;
		pz = 51;
		dx = 3;
		dy = 102;
		dz = 38;
	}

	void cameraFirst(double mx, double my, double mz) {
		px = mx;
		py = my;
		pz = mz;
		dx = -1;
		dy = 104;
		dz = 34;
	}

	void cameraNormal() {
		px = px - 11;
		py = py + 9.5;
		pz = pz + 9;
		dx = 3, dy = 102, dz = 38;
	}
	

	/*
	void moveLeft()
	{
		

	}

	void moveRight()
	{
		
	}

	void moveForward()
	{
		
	}

	void moveBackward()
	{
		
	}

	void turnRight()
	{
		
	}

	void turnLeft()
	{
		
	}

	void turnUp()
	{
		
	}

	void turnDown()
	{
		
	}


	*/


	void moveUp() {
		py += 1;
		dy += 1;

	}
	void moveDown() {
		py -= 1;
		dy -= 1;
	}

	void moveLeft()
	{
		if (!battlereturn()) {
			MovMario(4);
			if (banMov == false) {
				px -= 1;
				dx -= 1;
			}
		}

	}

	void moveRight()
	{
		if (!battlereturn()) {
			MovMario(3);
			if (banMov == false) {
				px += 1;
				dx += 1;
			}
		}

	}

	void moveForward()
	{
		if (!battlereturn()) {
			MovMario(1);
			if (banMov == false) {
				pz += 1;
				dz += 1;
			}
		}
		
	}

	void moveBackward()
	{
		if (!battlereturn()) {
			MovMario(2);
			if (banMov == false) {
				pz -= 1;
				dz -= 1;
			}
		}
	}

	void turnRight()
	{
		//debe empezar viendo a z negativa, si no gira al reves
		if (dx < 15 + px && camind == 0)
			dx += 1;
		if (dx == 15 + px && camind == 0)
			camind = 1;
		if (dz < 15 + pz && camind == 1)
			dz += 1;
		if (dz == 15 + pz && camind == 1)
			camind = 2;
		if (dx > -15 + px && camind == 2)
			dx -= 1;
		if (dx == -15 + px && camind == 2)
			camind = 3;
		if (dz > -15 + pz && camind == 3)
			dz -= 1;
		if (dz == -15 + pz && camind == 3)
			camind = 0;
		
	}

	void turnLeft()
	{
		
		//debe empezar viendo a z negativa, si no gira al reves
		if (dx > -15 + px && camind == 0)
			dx -= 1;
		if (dx == -15 + px && camind == 0)
			camind = 1;
		if (dz < 15 + pz && camind == 1)
			dz += 1;
		if (dz == 15 + pz && camind == 1)
			camind = 2;
		if (dx < 15 + px && camind == 2)
			dx += 1;
		if (dx == 15 + px && camind == 2)
			camind = 3;
		if (dz > -15 + pz && camind == 3)
			dz -= 1;
		if (dz == -15 + pz && camind == 3)
			camind = 0;
			
	}

	void turnUp()
	{
		
		if (dy < 50 + py)
		{
			dy += 1;
		}
		
	}

	void turnDown()
	{
		
		if (dy > -50 + py)
		{
			dy -= 1;
		}
		
	}
};
#endif
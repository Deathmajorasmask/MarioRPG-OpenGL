#include "OpenMove.h"
#include <gl/glew.h>
#include <math.h>


OpenMove::OpenMove() {
	//nohagonada
}

OpenMove::~OpenMove()
{
}

void OpenMove::traslate(float x, float y, float z) {
	float traslate_mat[] = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		x, y, z, 1
	};

	float world_mat[16];

	glGetFloatv(GL_MODELVIEW_MATRIX, world_mat);
	multMat(traslate_mat, world_mat);
	glLoadMatrixf(world_mat);
}

void OpenMove::scale(float x, float y, float z) {
	float scale_mat[] = {
		x, 0, 0, 0,
		0, y, 0, 0,
		0, 0, z, 0,
		0, 0, 0, 1
	};

	float world_mat[16];

	glGetFloatv(GL_MODELVIEW_MATRIX, world_mat);
	multMat(scale_mat, world_mat);
	glLoadMatrixf(world_mat);
}

void OpenMove::rotate(float deg, int x, int y, int z) {
	float rad = deg / 57.3;

	float rotateX_mat[] = {
		1,        0,        0,  0,
		0,  cos(rad), sin(rad), 0,
		0, -sin(rad), cos(rad), 0,
		0,         0,        0, 1
	};

	float rotateY_mat[] = {
		cos(rad), 0, -sin(rad), 0,
		0, 1,         0, 0,
		sin(rad), 0,  cos(rad), 0,
		0, 0,         0, 1
	};

	float rotateZ_mat[] = {
		cos(rad), sin(rad), 0, 0,
		-sin(rad), cos(rad), 0, 0,
		0,        0, 1, 0,
		0,        0, 0, 1
	};

	float world_mat[16];

	glGetFloatv(GL_MODELVIEW_MATRIX, world_mat);

	if (x != 0) {
		multMat(rotateX_mat, world_mat);
	}
	if (y != 0) {
		multMat(rotateY_mat, world_mat);
	}
	if (z != 0) {
		multMat(rotateZ_mat, world_mat);
	}

	glLoadMatrixf(world_mat);
}

void OpenMove::multMat(float* tranformacion, float* mundo) {
	float c[16];
	for (int i = 0; i < 16; i += 4) {
		c[i] = (
			tranformacion[i] * mundo[0] +
			tranformacion[i + 1] * mundo[4] +
			tranformacion[i + 2] * mundo[8] +
			tranformacion[i + 3] * mundo[12]);

		c[i + 1] = (
			tranformacion[i] * mundo[1] +
			tranformacion[i + 1] * mundo[5] +
			tranformacion[i + 2] * mundo[9] +
			tranformacion[i + 3] * mundo[13]);

		c[i + 2] = (
			tranformacion[i] * mundo[2] +
			tranformacion[i + 1] * mundo[6] +
			tranformacion[i + 2] * mundo[10] +
			tranformacion[i + 3] * mundo[14]);

		c[i + 3] = (
			tranformacion[i] * mundo[3] +
			tranformacion[i + 1] * mundo[7] +
			tranformacion[i + 2] * mundo[11] +
			tranformacion[i + 3] * mundo[15]);
	}

	for (int i = 0; i < 16; i++) {
		mundo[i] = c[i];
	}

}
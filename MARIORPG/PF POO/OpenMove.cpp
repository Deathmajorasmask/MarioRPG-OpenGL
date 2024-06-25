#include "OpenMove.h"
#include <gl/glew.h>
#include <math.h>


OpenMove::OpenMove() {

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

void OpenMove::multMat(float* transformate, float* world) {
	float c[16];
	for (int i = 0; i < 16; i += 4) {
		c[i] = (
			transformate[i] * world[0] +
			transformate[i + 1] * world[4] +
			transformate[i + 2] * world[8] +
			transformate[i + 3] * world[12]);

		c[i + 1] = (
			transformate[i] * world[1] +
			transformate[i + 1] * world[5] +
			transformate[i + 2] * world[9] +
			transformate[i + 3] * world[13]);

		c[i + 2] = (
			transformate[i] * world[2] +
			transformate[i + 1] * world[6] +
			transformate[i + 2] * world[10] +
			transformate[i + 3] * world[14]);

		c[i + 3] = (
			transformate[i] * world[3] +
			transformate[i + 1] * world[7] +
			transformate[i + 2] * world[11] +
			transformate[i + 3] * world[15]);
	}

	for (int i = 0; i < 16; i++) {
		world[i] = c[i];
	}

}
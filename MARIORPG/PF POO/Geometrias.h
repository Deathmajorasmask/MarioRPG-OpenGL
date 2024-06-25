#ifndef _Geom
#define _Geom
#define _USE_MATH_DEFINES
#include <math.h>
#include "VectorRR.h"
#include <cmath>

//structure to handle primitives with position, normal and uv's
struct Vertex {
	float Posx, Posy, Posz;
	float Normx, Normy, Normz;
	float u, v;
	float colorr, colorg, colorb, colora;
};

//structure containing data of the vertices and their indices
struct Mesh {
	Vertex *mesh;
	unsigned int *indices;
};

class Primitivos : public VectorRR
{
public:
	Primitivos()
	{
	}

	//We generate the vertices through spherical coordinates
	Mesh Esfera(int stacks, int slices, float radio, float inicio, float final)
	{
		//We load the structure with the necessary memory spaces
		Vertex *verticesxyzSD = new Vertex[stacks*slices * 3];
		unsigned int *indices = new unsigned int[stacks*slices * 6];
		//We generate an object to be able to transport the pointers
		Mesh output;

		for (int i = 0; i<slices; i++)
		{
			for (int j = 0; j<stacks; j++)
			{
				int indice = (i * stacks + j);
				verticesxyzSD[indice].Posx = radio*cos(((double)j / (stacks - 1))*(M_PI*(final - inicio)) + M_PI*inicio - M_PI / 2.0)*
					cos(2.0*M_PI*(double)i / (slices - 1));
				verticesxyzSD[indice].Posy = radio*sin(((double)j / (stacks - 1))*(M_PI*(final - inicio)) + M_PI*inicio - M_PI / 2.0);
				verticesxyzSD[indice].Posz = radio*cos(((double)j / (stacks - 1))*(M_PI*(final - inicio)) + M_PI*inicio - M_PI / 2.0)*
					sin(2.0*M_PI*(double)i / (slices - 1));

				//Multi-texture
				//verticesxyzSD[indice].colorr = Clampea(1.0, 0, 1);
				//verticesxyzSD[indice].colorg = Clampea(1.0, 0, 1);
				//verticesxyzSD[indice].colorb = Clampea(1.0, 0, 1);
				//verticesxyzSD[indice].colora = 0.0;
				//glColor4f(1.0,1.0,1.0,0.0);
				//Multi-texture

				verticesxyzSD[indice].Normx = cos(((double)j / (stacks - 1))*(M_PI*(final - inicio)) + M_PI*inicio - M_PI / 2.0)*
					cos(2.0*M_PI*(double)i / (slices - 1));
				verticesxyzSD[indice].Normy = sin(((double)j / (stacks - 1))*(M_PI*(final - inicio)) + M_PI*inicio - M_PI / 2.0);
				verticesxyzSD[indice].Normz = cos(((double)j / (stacks - 1))*(M_PI*(final - inicio)) + M_PI*inicio - M_PI / 2.0)*
					sin(2.0*M_PI*(double)i / (slices - 1));

				verticesxyzSD[indice].u = (float)1 * (1 - (float)i / (stacks - 1));
				verticesxyzSD[indice].v = (float)1 * (1 - (float)j / (slices - 1));
			}
		}

		//Indeces
		int indice = 0;
		for (int i = 0; i<slices - 1; i++)
		{
			for (int j = 0; j<stacks - 1; j++)
			{
				indices[indice++] = i * stacks + j;
				indices[indice++] = (i + 1) * stacks + j + 1;
				indices[indice++] = i * stacks + j + 1;

				indices[indice++] = i * stacks + j;
				indices[indice++] = (i + 1) * stacks + j;
				indices[indice++] = (i + 1) * stacks + j + 1;
			}
		}

		//Output
		output.mesh = verticesxyzSD;
		output.indices = indices;

		return output;
	}

	Mesh Plano(int vertx, int vertz, float anchof, float profz)
	{
		//We load the structure with the necessary memory spaces
		Vertex *verticesxyzSD = new Vertex[vertx*vertz * 3];
		unsigned int *indices = new unsigned int[vertx*vertz * 6];

		/*The separation between vertices, subtract 1 to make the correct side, imagine that the width is 10 and 
		it has 10 vertices, then it would give a 'deltax' of 1, if the vertices go from 0 to 9 then the position of 
		the last vertex would be 9, if you divide it by vertx - 1 it will give you 1.1111 
		and the last vertex will be 10.*/
		float deltax = anchof / (vertx - 1);
		float deltaz = profz / (vertz - 1);

		// Create Vertex
		for (int z = 0; z < vertz; z++)
		{
			for (int x = 0; x < vertx; x++)
			{
				verticesxyzSD[z*vertx + x].Posx = (float)x*deltax;
				verticesxyzSD[z*vertx + x].Posy = 0.0;
				verticesxyzSD[z*vertx + x].Posz = (float)z*deltaz;

				//Normal Vertex Map
				verticesxyzSD[z*vertx + x].Normx = 0.0;
				verticesxyzSD[z*vertx + x].Normy = 0.0;
				verticesxyzSD[z*vertx + x].Normz = 0.0;
			}
		}

		//uv's
		for (int z = 0; z < vertz; z++)
		{
			for (int x = 0; x < vertx; x++)
			{
				verticesxyzSD[z*vertx + x].u = (float)x / (vertx - 1);
				verticesxyzSD[z*vertx + x].v = (float)z / (vertz - 1);
			}
		}

		VectorRR aux;
		//Create Normals
		for (int z = 0; z < (vertz - 1); z++)
		{
			for (int x = 0; x < (vertx - 1); x++)
			{
				aux = GenNormal(&verticesxyzSD[z*vertx + x].Posx, &verticesxyzSD[(z + 1)*vertx + (x + 1)].Posx,
					&verticesxyzSD[z*vertx + (x + 1)].Posx);

				SumaNormal(&verticesxyzSD[z*vertx + x].Normx, &aux.X);
				SumaNormal(&verticesxyzSD[(z + 1)*vertx + (x + 1)].Normx, &aux.X);
				SumaNormal(&verticesxyzSD[z*vertx + (x + 1)].Normx, &aux.X);

				aux = GenNormal(&verticesxyzSD[z*vertx + x].Posx, &verticesxyzSD[(z + 1)*vertx + x].Posx,
					&verticesxyzSD[(z + 1)*vertx + (x + 1)].Posx);

				SumaNormal(&verticesxyzSD[z*vertx + x].Normx, &aux.X);
				SumaNormal(&verticesxyzSD[(z + 1)*vertx + x].Normx, &aux.X);
				SumaNormal(&verticesxyzSD[(z + 1)*vertx + (x + 1)].Normx, &aux.X);
			}
		}

		//Normalize the normals
		for (int z = 0; z < vertz; z++)
		{
			for (int x = 0; x < vertx; x++)
			{
				Normaliza(&verticesxyzSD[z*vertx + x].Normx);
			}
		}

		// Indeces
		int indice = 0;
		for (int i = 0; i<vertz - 1; i++)
		{
			for (int j = 0; j<vertx - 1; j++)
			{
				indices[indice++] = i * vertz + j;
				indices[indice++] = (i + 1) * vertz + j + 1;
				indices[indice++] = i * vertz + j + 1;

				indices[indice++] = i * vertz + j;
				indices[indice++] = (i + 1) * vertz + j;
				indices[indice++] = (i + 1) * vertz + j + 1;
			}
		}

		//Output

		Mesh output;

		output.mesh = verticesxyzSD;
		output.indices = indices;

		return output;
	}

	Mesh Plano(int vertx, int vertz, float anchof, float profz, unsigned char *altura, float tile = 1)
	{
		//We load the structure with the necessary memory spaces
		Vertex *verticesxyzSD = new Vertex[vertx*vertz * 3];
		unsigned int *indices = new unsigned int[vertx*vertz * 6];

		/*The separation between vertices, subtract 1 to make the correct side, imagine that the width is 10 and
		it has 10 vertices, then it would give a 'deltax' of 1, if the vertices go from 0 to 9 then the position of
		the last vertex would be 9, if you divide it by vertx - 1 it will give you 1.1111
		and the last vertex will be 10.*/
		float deltax = anchof / (vertx - 1);
		float deltaz = profz / (vertz - 1);

		//Vertex
		for (int z = 0; z < vertz; z++)
		{
			for (int x = 0; x < vertx; x++)
			{
				verticesxyzSD[z*vertx + x].Posx = (float)x*deltax - anchof / 2.0;
				verticesxyzSD[z*vertx + x].Posy = (float)altura[z*vertx * 4 + x * 4] / 10.0;
				verticesxyzSD[z*vertx + x].Posz = (float)z*deltaz - profz / 2.0;

				//Normal Vertex Map
				verticesxyzSD[z*vertx + x].Normx = 0.0;
				verticesxyzSD[z*vertx + x].Normy = 1.0;
				verticesxyzSD[z*vertx + x].Normz = 0.0;
			}
		}

		//uv's
		for (int z = 0; z < vertz; z++)
		{
			for (int x = 0; x < vertx; x++)
			{
				verticesxyzSD[z*vertx + x].u = (float)(x*tile) / (vertx - 1);
				verticesxyzSD[z*vertx + x].v = (float)(z*tile) / (vertz - 1);
			}
		}

		VectorRR aux;
		//Create Normals
		for (int z = 0; z < (vertz - 1); z++)
		{
			for (int x = 0; x < (vertx - 1); x++)
			{
				aux = GenNormal(&verticesxyzSD[z*vertx + x].Posx, &verticesxyzSD[z*vertx + (x + 1)].Posx,
					&verticesxyzSD[(z + 1)*vertx + (x + 1)].Posx);

				SumaNormal(&verticesxyzSD[z*vertx + x].Normx, &aux.X);
				SumaNormal(&verticesxyzSD[(z + 1)*vertx + (x + 1)].Normx, &aux.X);
				SumaNormal(&verticesxyzSD[z*vertx + (x + 1)].Normx, &aux.X);

				aux = GenNormal(&verticesxyzSD[z*vertx + x].Posx, &verticesxyzSD[(z + 1)*vertx + x + 1].Posx,
					&verticesxyzSD[(z + 1)*vertx + x].Posx);

				SumaNormal(&verticesxyzSD[z*vertx + x].Normx, &aux.X);
				SumaNormal(&verticesxyzSD[(z + 1)*vertx + x].Normx, &aux.X);
				SumaNormal(&verticesxyzSD[(z + 1)*vertx + (x + 1)].Normx, &aux.X);
			}
		}

		//Normalize the normals
		for (int z = 0; z < vertz; z++)
		{
			for (int x = 0; x < vertx; x++)
			{
				Normaliza(&verticesxyzSD[z*vertx + x].Normx);

			}
		}

		// Indeces
		int indice = 0;
		for (int i = 0; i<vertz - 1; i++)
		{
			for (int j = 0; j<vertx - 1; j++)
			{
				indices[indice++] = i * vertz + j;
				indices[indice++] = (i + 1) * vertz + j + 1;
				indices[indice++] = i * vertz + j + 1;

				indices[indice++] = i * vertz + j;
				indices[indice++] = (i + 1) * vertz + j;
				indices[indice++] = (i + 1) * vertz + j + 1;
			}
		}

		// Output

		Mesh output;

		output.mesh = verticesxyzSD;
		output.indices = indices;

		return output;
	}

	Mesh Plano3t(int vertx, int vertz, float anchof, float profz, unsigned char *altura, float tile,
		float alt1, float alt2, float alt3)
	{
		//We load the structure with the necessary memory spaces
		Vertex *verticesxyzSD = new Vertex[vertx*vertz * 3];
		unsigned int *indices = new unsigned int[vertx*vertz * 6];

		/*The separation between vertices, subtract 1 to make the correct side, imagine that the width is 10 and
		it has 10 vertices, then it would give a 'deltax' of 1, if the vertices go from 0 to 9 then the position of
		the last vertex would be 9, if you divide it by vertx - 1 it will give you 1.1111
		and the last vertex will be 10.*/
		float deltax = anchof / (vertx - 1);
		float deltaz = profz / (vertz - 1);

		// Create Vertex
		for (int z = 0; z < vertz; z++)
		{
			for (int x = 0; x < vertx; x++)
			{
				verticesxyzSD[z*vertx + x].Posx = (float)x*deltax - anchof / 2.0;
				verticesxyzSD[z*vertx + x].Posy = (float)altura[z*vertx * 4 + x * 4] / 10.0;
				verticesxyzSD[z*vertx + x].Posz = (float)z*deltaz - profz / 2.0;

				//Normal Vertex Map
				verticesxyzSD[z*vertx + x].Normx = 0.0;
				verticesxyzSD[z*vertx + x].Normy = 1.0;
				verticesxyzSD[z*vertx + x].Normz = 0.0;

				int alturaTerr = altura[z*vertx * 4 + x * 4];

				float valrelalt = (float)alturaTerr - alt1;
				verticesxyzSD[z*vertx + x].colorr = Clampea(1.0 - abs(valrelalt) / 86.0, 0, 1);
				verticesxyzSD[z*vertx + x].colorg = Clampea(1.0 - abs((float)alturaTerr - alt2) / 76.0, 0, 1);
				verticesxyzSD[z*vertx + x].colorb = Clampea(1.0 - abs((float)alturaTerr - alt3) / 76.0, 0, 1);

				float total = verticesxyzSD[z*vertx + x].colorr;
				total += verticesxyzSD[z*vertx + x].colorg;
				total += verticesxyzSD[z*vertx + x].colorb;

				verticesxyzSD[z*vertx + x].colorr /= total;
				verticesxyzSD[z*vertx + x].colorg /= total;
				verticesxyzSD[z*vertx + x].colorb /= total;

				if ((verticesxyzSD[z*vertx + x].colorr + verticesxyzSD[z*vertx + x].colorg + verticesxyzSD[z*vertx + x].colorb)<0.9)
				{
					float u = verticesxyzSD[z*vertx + x].colorr + verticesxyzSD[z*vertx + x].colorg + verticesxyzSD[z*vertx + x].colorb;
					int h = 0;
				}
			}
		}

		//uv's
		for (int z = 0; z < vertz; z++)
		{
			for (int x = 0; x < vertx; x++)
			{
				verticesxyzSD[z*vertx + x].u = (float)(x*tile) / (vertx - 1);
				verticesxyzSD[z*vertx + x].v = (float)(z*tile) / (vertz - 1);
			}
		}

		VectorRR aux;
		//Create Normals
		for (int z = 0; z < (vertz - 1); z++)
		{
			for (int x = 0; x < (vertx - 1); x++)
			{
				aux = GenNormal(&verticesxyzSD[z*vertx + x].Posx, &verticesxyzSD[z*vertx + (x + 1)].Posx,
					&verticesxyzSD[(z + 1)*vertx + (x + 1)].Posx);

				SumaNormal(&verticesxyzSD[z*vertx + x].Normx, &aux.X);
				SumaNormal(&verticesxyzSD[(z + 1)*vertx + (x + 1)].Normx, &aux.X);
				SumaNormal(&verticesxyzSD[z*vertx + (x + 1)].Normx, &aux.X);

				aux = GenNormal(&verticesxyzSD[z*vertx + x].Posx, &verticesxyzSD[(z + 1)*vertx + x + 1].Posx,
					&verticesxyzSD[(z + 1)*vertx + x].Posx);

				SumaNormal(&verticesxyzSD[z*vertx + x].Normx, &aux.X);
				SumaNormal(&verticesxyzSD[(z + 1)*vertx + x].Normx, &aux.X);
				SumaNormal(&verticesxyzSD[(z + 1)*vertx + (x + 1)].Normx, &aux.X);
			}
		}

		//Normalize the normals
		for (int z = 0; z < vertz; z++)
		{
			for (int x = 0; x < vertx; x++)
			{
				Normaliza(&verticesxyzSD[z*vertx + x].Normx);

			}
		}

		
		// Indices
		int indice = 0;
		for (int i = 0; i<vertz - 1; i++)
		{
			for (int j = 0; j<vertx - 1; j++)
			{
				indices[indice++] = i * vertz + j;
				indices[indice++] = (i + 1) * vertz + j + 1;
				indices[indice++] = i * vertz + j + 1;

				indices[indice++] = i * vertz + j;
				indices[indice++] = (i + 1) * vertz + j;
				indices[indice++] = (i + 1) * vertz + j + 1;
			}
		}

		// Output

		Mesh output;

		output.mesh = verticesxyzSD;
		output.indices = indices;

		return output;
	}
};
#endif
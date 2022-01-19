#ifndef _vect
#define _vect
#include <math.h>

//ejemplo de uso de enumeracion para definir cual eje se utilizara
enum Ejes { EjeX, EjeY, EjeZ };
//clase VectorRR desarrollada por Rafael Rosas para los UltraLMADs
class VectorRR {
	//propiedades del vector, sus componentes
public:
	float X;
	float Y;
	float Z;

	//el constructor por naturaleza (vacio)
	VectorRR()
	{
		X = 0;
		Y = 0;
		Z = 0;
	}

	//la sobrecarga del constructor, con los componentes
	VectorRR(float Vx, float Vy, float Vz)
	{
		X = Vx;
		Y = Vy;
		Z = Vz;
	}

	//esto es de Graficas Computacionales no ocupan aprenderselo para la revision
	void Identidad(float Mat[4][4])
	{
		for (int i = 0; i<4; i++)
		{
			for (int j = 0; j<4; j++)
			{
				Mat[i][j] = 0;
				if (i == j)
					Mat[i][j] = 1;
			}
		}
	}

	//esto es de Graficas Computacionales no ocupan aprenderselo para la revision
	void Transforma(VectorRR &v, float grados2, int eje = 0)
	{
		float Matriz[4][4];
		float grados = grados2 * 3.141516 / 180.0;

		Identidad(Matriz);

		if (eje == Ejes::EjeX)
		{
			Matriz[1][1] = cos(grados);
			Matriz[2][2] = Matriz[1][1];
			Matriz[1][2] = -sin(grados);
			Matriz[2][1] = sin(grados);
		}

		if (eje == Ejes::EjeY)
		{
			Matriz[0][0] = cos(grados);
			Matriz[2][2] = Matriz[0][0];
			Matriz[0][2] = -sin(grados);
			Matriz[2][0] = sin(grados);
		}

		if (eje == Ejes::EjeZ)
		{
			Matriz[0][0] = cos(grados);
			Matriz[1][1] = Matriz[0][0];
			Matriz[0][1] = -sin(grados);
			Matriz[1][0] = sin(grados);
		}

		VectorRR aux;

		aux.X = v.X * Matriz[0][0] + v.Y * Matriz[0][1] + v.Z * Matriz[0][2];
		aux.Y = v.X * Matriz[1][0] + v.Y * Matriz[1][1] + v.Z * Matriz[1][2];
		aux.Z = v.X * Matriz[2][0] + v.Y * Matriz[2][1] + v.Z * Matriz[2][2];

		v = aux;
	}

	//generamos las normales a traves de punteros del vector, es una forma comun de manejarlos
	VectorRR GenNormal(float *v1, float *v2, float *v3)
	{
		VectorRR vec1, vec2;

		vec1.X = *v2 - *v1;
		vec1.Y = *(v2 + 1) - *(v1 + 1);
		vec1.Z = *(v2 + 2) - *(v1 + 2);

		vec2.X = *v3 - *v1;
		vec2.Y = *(v3 + 1) - *(v1 + 1);
		vec2.Z = *(v3 + 2) - *(v1 + 2);

		return Cruz(vec1, vec2);
	}

	//la suma de vectores es el pan nuestro de cada dia
	//componente a componente
	VectorRR operator +(VectorRR& v2)
	{
		VectorRR tempo;

		tempo.X = X + v2.X;
		tempo.Y = Y + v2.Y;
		tempo.Z = Z + v2.Z;

		return tempo;
	}

	//otra forma de suma de vectores para ahora para la normal
	void SumaNormal(float *v1, float *v2)
	{
		*v1 += *v2;
		*(v1 + 1) += *(v2 + 1);
		*(v1 + 2) += *(v2 + 2);
	}

	//si se hace la suma de vectores entonces esta
	//obligada la igualdad
	VectorRR& operator =(VectorRR& v2)
	{
		X = v2.X;
		Y = v2.Y;
		Z = v2.Z;

		return *this;
	}

	//cuando queremos cargar un vector a traves de la clase y no de un
	//objeto podemos hacer esto
	VectorRR operator ()(float Vx, float Vy, float Vz)
	{
		VectorRR tempo;

		tempo.X = Vx;
		tempo.Y = Vy;
		tempo.Z = Vz;

		return tempo;
	}

	//una clase Vector sin el producto cruz es pecado
	VectorRR Cruz(VectorRR v1, VectorRR v2)
	{
		VectorRR tempo;

		tempo.X = v1.Y * v2.Z - v1.Z * v2.Y;
		tempo.Y = v1.Z * v2.X - v1.X * v2.Z;
		tempo.Z = v1.X * v2.Y - v1.Y * v2.X;

		return tempo;
	}

	//sin el producto punto es condena total
	float Punto(VectorRR v1, VectorRR v2)
	{
		//No hay mucho que explicar
		return v1.X * v2.X + v1.Y * v2.Y + v1.Z * v2.Z;
	}

	//la normalizacion nos ahorra operaciones (esta es por vector)
	VectorRR Normaliza(VectorRR v1)
	{
		//no hay mucho que explicar
		float magnitud = sqrt(v1.X * v1.X + v1.Y * v1.Y + v1.Z * v1.Z);
		v1.X /= magnitud;
		v1.Y /= magnitud;
		v1.Z /= magnitud;
		return v1;
	}

	//esta es por punteros
	void Normaliza(float *v1)
	{
		float magnitud = sqrt((*v1)*(*v1) + (*(v1 + 1))*(*(v1 + 1)) + (*(v1 + 2))*(*(v1 + 2)));
		*v1 /= magnitud;
		*(v1 + 1) /= magnitud;
		*(v1 + 2) /= magnitud;
	}

	//función Ademir
	float Clampea(float valor, float min, float max)
	{
		if (valor<min)
		{
			valor = min;
		}
		else
		{
			if (valor>max)
			{
				valor = max;
			}
		}

		return valor;
	}

};
#endif
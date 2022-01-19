#ifndef _PARTICLE
#define _PARTICLE

#include <gl\glew.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <cstdlib>
#include <time.h>
#include "VectorRR.h"

#define MAX_NUM_PARTICULAS 10000

namespace Particles
{
	class Ambiente
	{
	public:
		VectorRR gravedad;
		VectorRR viento;

	public:
		Ambiente(VectorRR gravedad, VectorRR viento)
		{
			this->gravedad = gravedad;
			this->viento = viento;
		}
		~Ambiente()
		{
		}
	};

	class Particle
	{
	public:
		VectorRR posicion;
		VectorRR direccion;
		VectorRR direccionInicial;
		VectorRR color;
		int vida;
		bool activa;

	public:
		Particle(VectorRR posicion, VectorRR direccion, VectorRR color, int vida, bool activa)
		{
			this->activa = activa;
			this->color = color;
			this->direccion = direccion;
			this->posicion = posicion;
			this->vida = vida;
			this->direccionInicial = direccion;
		}

		~Particle()
		{
		}

		bool Update(Ambiente ambiente)
		{
			if (activa)
			{
				direccion.X += ambiente.gravedad.X + ambiente.viento.X;
				direccion.Y += ambiente.gravedad.Y + ambiente.viento.Y;
				direccion.Z += ambiente.gravedad.Z + ambiente.viento.Z;
				posicion.X += direccion.X / 4;
				posicion.Y += direccion.Y / 4;
				posicion.Z += direccion.Z / 4;
				if (vida > 0)
					vida--;
				else
				{
					activa = false;
					return false;
				}
				return true;
			}
		}

		void Draw(float tamaño)
		{
			glBegin(GL_QUADS);
			glColor3f(color.X, color.Y, 0);
			glVertex3f(posicion.X - tamaño, posicion.Y - tamaño, posicion.Z);
			glVertex3f(posicion.X + tamaño, posicion.Y - tamaño, posicion.Z);
			glVertex3f(posicion.X + tamaño, posicion.Y + tamaño, posicion.Z);
			glVertex3f(posicion.X - tamaño, posicion.Y + tamaño, posicion.Z);
			glEnd();
		}
	};

	class Systema
	{
	public:
		Particle *particulas[MAX_NUM_PARTICULAS];
		VectorRR posicion;
		VectorRR color;
		bool generar;
		int total_particulas;
		int s_vida;

	public:
		Systema(VectorRR posicion, VectorRR color, bool generar, int partVida)
		{
			this->color = color;
			this->generar = generar;
			this->posicion = posicion;
			total_particulas = 0;
			s_vida = partVida;
		}

		~Systema()
		{
			delete particulas;
		}

		void generarParticula(VectorRR direccion, VectorRR color, int vida, bool activa)
		{
			particulas[total_particulas] = new Particle(posicion, direccion, color, vida, activa);
			total_particulas++;
		}

		void reiniciarParticula(Particle *particula)
		{
			particula->activa = true;
			particula->posicion = posicion;
			particula->vida = s_vida;
			particula->direccion = particula->direccionInicial;
		}

		void update(Ambiente ambiente)
		{

			for (int i = 0; i<total_particulas; i++)
			{
				if (!particulas[i]->Update(ambiente))
				{
					if (generar)
					{
						reiniciarParticula(particulas[i]);
					}
				}
			}
		}

		void draw(float tamañoParticula)
		{
			for (int i = 0; i<total_particulas; i++)
			{
				if (particulas[i]->activa)
				{
					particulas[i]->Draw(tamañoParticula);
				}
			}
		}
	};

	class fuente
	{
	public:
		Systema *sistema;
		Ambiente *amb;
		int partnum;
		int duracion;

	public:
		fuente(VectorRR pos, VectorRR col, bool gen, int numpart, int duracionPart)
		{
			amb = new Ambiente(VectorRR(0, 0, 0), VectorRR(0, 0, 0));
			sistema = new Systema(pos, col, gen, duracionPart);
			duracion = duracionPart;
			if (numpart <= MAX_NUM_PARTICULAS)
				partnum = numpart;
			else
				partnum = MAX_NUM_PARTICULAS;
		}
		~fuente()
		{
		}

		void draw()
		{
			if (sistema->total_particulas < partnum)
			{
				float x = (float)(rand() % 20 + (-10)) / 1000;
				float y = (float)(rand() % 20 + (-10)) / 1000;
				float z = (float)(rand() % 8 + 5) / 100;
				VectorRR col = VectorRR((float)(rand() % 100 + 50) / 100, (float)(rand() % 100 + 50) / 100, (float)(rand() % 100 + 50) / 100);
				sistema->generarParticula(VectorRR(x, y, z), col, duracion, true);
			}
			sistema->update(*amb);
			sistema->draw(0.01);
		}
	};
};

#endif
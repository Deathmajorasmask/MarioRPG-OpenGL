#ifndef __Escena
#define __Escena

#include <gl\GLU.h>
#include <gl\GL.h>
#include "SkyDome.h"
#include "Terrain.h"
#include "TerrainEx.h"
#include "Model.h"
#include "Billboard.h"
#include "Fog.h"
#include "FogEs.h"
#include "Camera.h"
#include "Water.h"
#include "Animations.h"
#include <time.h>
#include <stdlib.h>     //srand, rand
#include "Particle.h"
#include "OpenMove.h"

using namespace Particles;


class Scene : public Camera , public Fog, public FogEs
{
public:
	SkyDome *skyDay;
	TerrainEx *terrainEx;
	Terrain *terrain;
	Water *lago;
	Fog *niebla;
	FogEs * foges;
	float dens = 0.000;
	int numSecret = 0;
	bool CtrlAnims[5],Huevoshi, panel, CtrlAnimsAux[5];
	Particles::fuente *hojas[2];
	Billboard *billBoard[40];
	//Billboard *billBoard[100];
	//Niebla niebla;

	EDXFramework::Model *marprin, *marprinO, *marprinT,  *castle, *castle_windows,*castle_grass,*castle_tree,*botonB, *botonX, *coin,*boo,*piranha2, *billboardBoo, *billboardYoshi;
	EDXFramework::Model *arrow,*piranha,*thwomp, *bowser,*ojBowser, *brBowser, *cursor,*billboardRed, *egg, *muss, *flower, *star;
	Scene(HWND hWnd)
	{
		
		GLfloat AmbMat[] = { 1, 1, 1, 1 };
		GLfloat AmbPos[] = { 0, 400, 400, 1 };

		GLfloat diffuse[] = { 1.0f, 0.5f, 0.0f, 0.5f };
		GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		
		glShadeModel(GL_SMOOTH);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);
		glMaterialfv(GL_FRONT, GL_AMBIENT, AmbMat);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular);

		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
		glEnable(GL_NORMALIZE);
		glEnable(GL_LIGHT0);
		glLightfv(GL_LIGHT0, GL_POSITION, AmbPos);
		//habilitamos la forma de reflejar la luz
		//glEnable(GL_COLOR_MATERIAL);

		hojas[0] = new Particles::fuente(VectorRR(1, 1, 1), VectorRR(1, 1, 1), true, 40, 200);

		//512
		niebla = new Fog;
		foges = new FogEs;
		skyDay = new SkyDome(hWnd, 32, 32, 500, L"Imagenes//Skymario.jpg");
		terrainEx = new TerrainEx(hWnd, L"Imagenes//terrenoplano.bmp", L"Imagenes//cuadricula.jpg", L"Imagenes//texterr.jpg", 400, 400);
		terrain = new Terrain(hWnd, L"Imagenes//Altura2.bmp", L"Imagenes//Arenatex1.jpg", L"Imagenes//TierraTex2.jpg", L"Imagenes//MarioGrass.jpg", 900, 900);
		boo = new EDXFramework::Model("Modelos//Boo//Boo.obj", "Modelos//Boo//boo1.bmp", 1);
		star = new EDXFramework::Model("Modelos//Star//Star.obj", "Modelos//Star//tex_0x2680.bmp", 1);
		coin = new EDXFramework::Model("Modelos//Coin//coin.obj", "Modelos//Coin//dl_itembell_alb.bmp", 1);
		flower = new EDXFramework::Model("Modelos//Flower//Flower.obj", "Modelos//Flower//tex_0x4f00.bmp", 1);
		muss = new EDXFramework::Model("Modelos//Muss//Hongo.obj", "Modelos//Muss//t0081_0.bmp", 1);
		egg = new EDXFramework::Model("Modelos//Egg//egg.obj", "Modelos//Egg//YoshSS00.bmp", 1);
		billboardRed = new EDXFramework::Model("Modelos//Billboards//BillboardRed.obj", "Modelos//Billboards//billboardRed.bmp", 1);
		billboardBoo = new EDXFramework::Model("Modelos//Billboards//BillboardRed.obj", "Modelos//Billboards//billboardBoo.bmp", 1);
		billboardYoshi = new EDXFramework::Model("Modelos//Billboards//BillboardRed.obj", "Modelos//Billboards//billboardYoshi.bmp", 1);
		cursor = new EDXFramework::Model("Modelos//Cursor//Cursor.obj", "Modelos//Cursor//Cursor_texture.bmp", 1);
		botonB = new EDXFramework::Model("Modelos//Botones//Boton.obj", "Modelos//Botones//botonB.bmp", 1);
		botonX = new EDXFramework::Model("Modelos//Botones//Boton.obj", "Modelos//Botones//botonX.bmp", 1);
		lago = new Water(hWnd, L"Imagenes//Water_texture1.bmp", L"Imagenes//Water_texture1.jpg", 200, 1200);
		castle = new EDXFramework::Model("Modelos//Scene_Castle//Castle.obj", "Modelos//Scene_Castle//CastleAtlas_lit.bmp", 1);
		castle_windows = new EDXFramework::Model("Modelos//Scene_Castle//Castle_Windows.obj", "Modelos//Scene_Castle//Windows.bmp", 1);
		castle_grass = new EDXFramework::Model("Modelos//Scene_Castle//Castle_Grass.obj", "Modelos//Scene_Castle//GardenAtlasEDIT.bmp", 1);
		castle_tree = new EDXFramework::Model("Modelos//Scene_Castle//Castle_Tree.obj", "Modelos//Scene_Castle//TreeAtlas_lit.bmp", 1);
		piranha = new EDXFramework::Model("Modelos//Piranha_Plant//piranhaplant.obj", "Modelos//Piranha_Plant//t0048_0.bmp", 1);
		piranha2 = new EDXFramework::Model("Modelos//Piranha_Plant//piranhaplantmouth.obj", "Modelos//Piranha_Plant//t0048_0.bmp", 1);
		thwomp = new EDXFramework::Model("Modelos//Thwomp//Thwomp.obj", "Modelos//Thwomp//11AAB7D7_c.bmp", 1);
		brBowser = new EDXFramework::Model("Modelos//Bowser//BrazosBowser.obj", "Modelos//Bowser//BowsSS00.bmp", 1);
		ojBowser = new EDXFramework::Model("Modelos//Bowser//OjosBowser.obj", "Modelos//Bowser//BowsSS01.bmp", 1);
		bowser = new EDXFramework::Model("Modelos//Bowser//Bowser.obj", "Modelos//Bowser//BowsSS00.bmp", 1);
		arrow = new EDXFramework::Model("Modelos//Arrow//Arrow.obj", "Modelos//Arrow//ArrowMAP.bmp", 1);
		marprin = new EDXFramework::Model("Modelos//Characters//MarioPrin1.obj", "Modelos//Characters//mario_main.bmp",1);
		marprinO = new EDXFramework::Model("Modelos//Characters//MarioPrin2.obj", "Modelos//Characters//mario_main.bmp", 1);
		marprinT = new EDXFramework::Model("Modelos//Characters//MarioPrin3.obj", "Modelos//Characters//mario_main.bmp", 1);
		cameraInitialize();
		CtrlAnims[0] = true;
		CtrlAnimsAux[0] = true;
		Billboards(billBoard, hWnd);
	}
	

	void Billboards(Billboard *bills[], HWND hWnd)
	{
		int bx, by, bz;
		for (int i = 0; i <= 39; i++)
		{
			do
			{
				bx = rand() % 500 + 1;
				bx -= 250;
				bz = rand() % 500 + 1;
				bz -= 250;
				by = terrain->Superficie(bx, bz) * 4;
			} while (by > 70 || by < 15);
			bills[i] = new Billboard(hWnd, L"Imagenes//Alga1.png", 5, 3, bx, by, bz);
		}

	}
	
	void render(HDC hDC, HWND hWnd)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0, 0, 0, 0);
		glLoadIdentity();

			GLfloat AmbInt[] = { 0.1, 0.1, 0.1, 1 };
			glLightfv(GL_LIGHT0, GL_AMBIENT, AmbInt);
		
			//	py = terrain->Superficie(px, pz) * 4 + 4;
			
		cameraUpdate();
		//CamaraUpdate();
		//Billboards(billBoard);
		//Skydome
		glPushMatrix();
		OpenMove::traslate(0, 40, 0);
		OpenMove::rotate(90, 0, 1, 0);
		//OpenMove::scale(.3, .3, .3);
		OpenMove::scale(.3, .3, .3);
		skyDay->Draw();
		glPopMatrix();

		if (battleGet) {
			//Terreno
			glPushMatrix();
			OpenMove::traslate(0, 50, 0);
			//OpenMove::scale(.5, .5, .5);
			terrainEx->Draw();
			glPopMatrix();
		}
		else {
			//terreno multitextura
			glPushMatrix();
			OpenMove::traslate(0, 60, 0);
			terrain->Draw();
			glPopMatrix();

		}

		if (ganarFinal == true && renderMultimapa == true) {
			ganarFinal = false;
			//MessageBox(hWnd, "No puedes ganar, tiene el level inferior activo (usas trampas)", "Aviso", MB_OK);
		}
		if (ganarFinal) {
			glEnable(GL_COLOR_MATERIAL);
			cameraWin();
			
			niebla->draw();
			mx = -1;
			my = 102.5;
			mz = 42;
			battleGet = false;
			ganarFinal = false;
			nuevoMapa = true;
		}
		if (renderMultimapa){
			//LO MAS IMPORTANTE
			glPushMatrix();
			foges->density = dens;
			foges->drawing();
			
			glPopMatrix();
		}

		if (vistaCamare == 0) {
			cameraNormal();
			vistaCamare = 2;
		}
		if (vistaCamare == 1) {
			cameraFirst(mx, my+.5, mz);
			vistaCamare = 2;
		}

		if (battleGet) { //Batalla
			if (gameOver) {
				MessageBox(hWnd, "Te han matado", "Aviso", MB_OK);
				exit(1);
			}

			//Si ya gano
			if (ganarFinal) {
				MessageBox(hWnd, "Haz vencido, felicidades", "Aviso", MB_OK);
				battleGet = false;
			}

			//Acomodo de la camara
			if (nuevaCamera == true) {
				cameraBattle();
				cameraUpdate();
				nuevaCamera = false;
			}

			//Batalla turno de mario
			if (turnMario) {

				//Bowser aparecera estatico
				glPushMatrix();
				OpenMove::traslate(-20, 62, 35);
				OpenMove::scale(.4, .4, .4);
				ojBowser->Draw();
				brBowser->Draw();
				bowser->Draw();
				glPopMatrix();

				//Auxiliar de mario estatico (Animar)
				glPushMatrix();
				OpenMove::traslate(-20, 60, 45);
				//OpenMove::scale(10,10,1);
				marprin->Draw();
				glPopMatrix();

				if (pulsB) {
					if (attMario4==false && attMario1 == false && attMario2 == false && attMario3 == false) {
						glPushMatrix();
						OpenMove::traslate(-14, 65.5, 49);
						OpenMove::rotate(205, 0, 1, 0);
						OpenMove::scale(.15, .15, .15);
						billboardRed->Draw();
						glPopMatrix();

						//Primera posición 65.5
						//Ultima posición 65.2
						glPushMatrix();
						OpenMove::traslate(-14, cury, 49);
						OpenMove::rotate(205, 0, 1, 0);
						OpenMove::scale(.15, .15, .15);
						cursor->Draw();
						glPopMatrix();

						//Imprime el menu y B
						glPushMatrix();
						OpenMove::traslate(-14, 65, 49);
						OpenMove::rotate(205, 0, 1, 0);
						OpenMove::scale(.1, .1, .1);
						botonB->Draw();
						glPopMatrix();
					}
					else {
						
						if (attMario1) {
							if (verificar) {
								MarioAttack(1);
								verificar = false;
							}
							if (failDrop == false) { //No ha fallado el ataque
								lan -= .12;
								glPushMatrix();
								OpenMove::traslate(-20, 61, lan);
								OpenMove::scale(3, 3, 3);
								egg->Draw();
								glPopMatrix();
								if (lan <= 35) { //Se efectuo el ataque con seguridad
									lan = 45;
									turnMario = false;
									attMario1 = false;
									verificar = true;
									pulsB = false;
								}
							}
							else {
								attMario1 = false;
								verificar = true;
								MessageBox(hWnd, "Hacen falta Flower Points para lanzar", "Aviso", MB_OK);
							}


						}
						if (attMario2) {
							
							if (verificar) {
								MarioAttack(2);
								verificar = false;
							}
							if (failDrop == false) {
								starRotated--;
								starCaid -= .1;
								glPushMatrix();
								OpenMove::traslate(-20, starCaid, 35);
								OpenMove::rotate(starRotated + 10, 0, 1, 0);
								star->Draw();
								glPopMatrix();

								glPushMatrix();
								OpenMove::traslate(-15, starCaid + 5, 40);
								OpenMove::rotate(starRotated + 2, 0, 1, 0);
								star->Draw();
								glPopMatrix();

								glPushMatrix();
								OpenMove::traslate(-15, starCaid, 30);
								OpenMove::rotate(starRotated, 0, 1, 0);
								star->Draw();
								glPopMatrix();

								glPushMatrix();
								OpenMove::traslate(-22, starCaid + 3, 36);
								OpenMove::rotate(starRotated + 6, 0, 1, 0);
								OpenMove::scale(1.5, 1.5, 1.5);
								star->Draw();
								glPopMatrix();

								glPushMatrix();
								OpenMove::traslate(-19, starCaid - 2, 34);
								OpenMove::rotate(starRotated + 20, 0, 1, 0);
								OpenMove::scale(2, 2, 2);
								star->Draw();
								glPopMatrix();

								glPushMatrix();
								OpenMove::traslate(-19, starCaid + 2, 31);
								OpenMove::rotate(starRotated + 50, 0, 1, 0);
								OpenMove::scale(2, 2, 2);
								star->Draw();
								glPopMatrix();

								glPushMatrix();
								OpenMove::traslate(-20, starCaid - 4, 29);
								OpenMove::rotate(starRotated, 0, 1, 0);
								OpenMove::scale(.5, .5, .5);
								star->Draw();
								glPopMatrix();

								if (starCaid <=49) {
									starRotated = 360;
									starCaid = 70;
									turnMario = false;
									attMario2 = false;
									verificar = true;
									pulsB = false;
								}
							}
							else {
								attMario2 = false;
								verificar = true;
								MessageBox(hWnd, "Hacen falta Flower Points para rezar a las estrellas", "Aviso", MB_OK);
							}



						}
						//Fin de Estrella gigante
						if (attMario3) {
							if (verificar) {
								MarioAttack(3);
								verificar = false;
							}
								flowerSpan += .04;
								glPushMatrix();
								OpenMove::traslate(-20, 62, 45);
								OpenMove::scale(flowerSpan, flowerSpan, flowerSpan);
								flower->Draw();
								glPopMatrix();
								if (flowerSpan >= 3) {
									flowerSpan = 0;
									turnMario = false;
									attMario3 = false;
									verificar = true;
									pulsB = false;
								}
						}
						//Fin de recargar Flower Points 
						if (attMario4) {
							if (verificar){
								MarioAttack(4);
								verificar = false;
							}
							if (failDrop == false) {
								egmy += .02;
								glPushMatrix();
								OpenMove::traslate(-20, egmy, 45);
								OpenMove::scale(3, 3, 3);
								muss->Draw();
								glPopMatrix();
								if (egmy >= 63) {
									egmy = 61;
									turnMario = false;
									attMario4 = false;
									verificar = true;
									pulsB = false;
								}
							}
							else {
								attMario4 = false;
								verificar = true;
								MessageBox(hWnd, "Hacen falta Flower Points para Sanarse", "Aviso", MB_OK);
							}

						}//Fin de ataque vida

					}
					//---Eliminación de Billboards
				}
				/*
				glPushMatrix();
				OpenMove::traslate(-14.5, 65, 49.3);
				OpenMove::rotate(205, 0, 1, 0);
				OpenMove::scale(.1, .1, .1);
				botonX->Draw();
				glPopMatrix();
				*/
			}
			else {
				//Mario aparecera estatico
				glPushMatrix();
				OpenMove::traslate(-20, 60, 45);
				//OpenMove::scale(10,10,1);
				marprin->Draw();
				glPopMatrix();

				if (AnimBowser) {
					srand(time(NULL));
					numSecret = rand() % 6; //del 0 al 5
					BowserAttack(numSecret);
					AnimBowser = false;
				}

				//Animaciones para la batalla
				if (numSecret == 1) { //Golpe basico
					glPushMatrix();
					OpenMove::traslate(-20, bowY, 35);
					OpenMove::scale(.4, .4, .4);
					ojBowser->Draw();
					brBowser->Draw();
					bowser->Draw();
					glPopMatrix();

					(backBowser == true) ? bowY -= .7 : bowY += .7;
					if (bowY >= 70) {
						backBowser = true;
					}

					if (bowY <=62) {
						backBowser = false;
						turnMario = true;
						AnimBowser = true;
					}

				}
				else if (numSecret == 2) { //Thwromp
					//bowser 
					glPushMatrix();
					OpenMove::traslate(-20, 62, 35);
					OpenMove::scale(.4, .4, .4);
					ojBowser->Draw();
					bowser->Draw();
					glPopMatrix();

					glPushMatrix();
					OpenMove::traslate(-20, 62.6, 37.6);
					OpenMove::rotate(270, 1, 0, 0);
					OpenMove::scale(.4, .4, .4);
					brBowser->Draw();
					glPopMatrix();

					if (!twompMovBool) {
						twompMovY--;
					}
					else {
						twompMovY+=.3;
					}
					glPushMatrix();
					OpenMove::traslate(-20, twompMovY, 45);
					OpenMove::scale(.1, .1, .1);
					thwomp->Draw();
					glPopMatrix();
					if (twompMovBool==true && twompMovY>=70) {
						twompMovY = 70;
						twompMovBool = false;
						turnMario = true;
						AnimBowser = true;
					}

					if (twompMovY <= 61) {
						twompMovBool = true;
					}

				}
				else if (numSecret == 3) { //pulg
					//Bowser
					glPushMatrix();
					OpenMove::traslate(-20, 62, 35);
					OpenMove::scale(.4, .4, .4);
					ojBowser->Draw();
					bowser->Draw();
					glPopMatrix();

					glPushMatrix();
					OpenMove::traslate(-20, 62.6, 37.6);
					OpenMove::rotate(270, 1, 0, 0);
					OpenMove::scale(.4, .4, .4);
					brBowser->Draw();
					glPopMatrix();

					if (!piraMovOp) {
						piraMovY += .2;
						glPushMatrix();
						OpenMove::traslate(-20, piraMovY, 45);
						OpenMove::scale(.5, .5, .5);
						piranha->Draw();
						glPopMatrix();
					}

					if (piraMovY>=55) {
						piraMovOp = true;
						if (piraMovOp) {
							if (!pirswitch) {
								glPushMatrix();
								OpenMove::traslate(-20, 55, 45);
								OpenMove::scale(.5, .5, .5);
								piranha->Draw();
								glPopMatrix();
								pirswitch = true;
							}
							else {
								glPushMatrix();
								OpenMove::traslate(-20, 55, 45);
								OpenMove::scale(.5, .5, .5);
								piranha2->Draw();
								glPopMatrix();
								pirswitch = false;
							}
							pirCont++;
							if (pirCont>=30) {
								piraMovY = 50;
								turnMario = true;
								AnimBowser = true;
								pirCont = 0;
								piraMovOp = false;
								pirswitch = false;
							}
						}
					}

				}
				else if (numSecret == 4) { //Maxima llamas Boo
					//Bowser
					glPushMatrix();
					OpenMove::traslate(-20, 62, 35);
					OpenMove::scale(.4, .4, .4);
					ojBowser->Draw();
					bowser->Draw();
					glPopMatrix();

					glPushMatrix();
					OpenMove::traslate(-20, 62.6, 37.6);
					OpenMove::rotate(270, 1, 0, 0);
					OpenMove::scale(.4, .4, .4);
					brBowser->Draw();
					glPopMatrix();

					//Fantasmas
					glPushMatrix();
						glPushMatrix();
						OpenMove::traslate(-25,60,45);
						OpenMove::rotate(50,0,1,0);
						OpenMove::scale(phantomScale, phantomScale, phantomScale);
						boo->Draw();
						glPopMatrix();

						glPushMatrix();
						OpenMove::traslate(-25, 65, 40);
						OpenMove::rotate(50, 0, 1, 0);
						OpenMove::scale(phantomScale+.2, phantomScale+.2, phantomScale+.2);
						boo->Draw();
						glPopMatrix();

						glPushMatrix();
						OpenMove::traslate(-15, 60, 40);
						OpenMove::rotate(-140, 0, 1, 0);
						OpenMove::scale(phantomScale+.25, phantomScale + .25, phantomScale + .25);
						boo->Draw();
						glPopMatrix();

						glPushMatrix();
						OpenMove::traslate(-15, 60, 42);
						OpenMove::rotate(-140, 0, 1, 0);
						OpenMove::scale(phantomScale, phantomScale, phantomScale);
						boo->Draw();
						glPopMatrix();

						glPushMatrix();
						OpenMove::traslate(-15, 65, 42);
						OpenMove::rotate(-140, 0, 1, 0);
						OpenMove::scale(phantomScale, phantomScale, phantomScale);
						boo->Draw();
						glPopMatrix();

						glPushMatrix();
						OpenMove::traslate(-30, 65, 38);
						OpenMove::rotate(50, 0, 1, 0);
						OpenMove::scale(phantomScale, phantomScale, phantomScale);
						boo->Draw();
						glPopMatrix();

						glPushMatrix();
						OpenMove::traslate(-25, 65, 45);
						OpenMove::rotate(50, 0, 1, 0);
						OpenMove::scale(phantomScale, phantomScale, phantomScale);
						boo->Draw();
						glPopMatrix();

						if (phantomSecMov[0] == false) {
							phantomScale += .03;
						}
						if (phantomScale >= 2) {
							phantomSecMov[0]=true;
						}
						if (phantomSecMov[0]==true) {
							clocking+=.03;
							if (clocking>=1) {
								clocking = 0;
								AnimBowser = true;
								turnMario = true;
								phantomScale = 0;
								phantomSecMov[0] = false;
							}
						}

					glPopMatrix();

				}
				else { //Golpe mediocre
					clocking += .01;
					glPushMatrix();
					OpenMove::traslate(-20, 62, 35);
					OpenMove::scale(.4, .4, .4);
					ojBowser->Draw();
					bowser->Draw();
					glPopMatrix();

					glPushMatrix();
					OpenMove::traslate(-20, 62.6, 37.6);
					OpenMove::rotate(270, 1, 0, 0);
					OpenMove::scale(.4, .4, .4);
					brBowser->Draw();
					glPopMatrix();
					if (clocking >= 1) {
						turnMario = true;
						clocking = 0;
						AnimBowser = true;
					}

				}
			}
		}
		else {
			
			//water
			glPushMatrix();
			OpenMove::traslate(0, 100, 0);
			//OpenMove::rotate(-90, 1, 0, 0);
			//OpenMove::scale(50, 50, 50);
			GLfloat LightAmb3[] = { 0,0,0,0.0 };
			glEnable(GL_BLEND);
			glMateriali(GL_FRONT, GL_SHININESS, 20);
			glBlendFunc(GL_DST_ALPHA, GL_SRC_ALPHA);
			lago->Draw();
			glDisable(GL_BLEND);
			glPopMatrix();

			//Mario 
			glPushMatrix();
			OpenMove::traslate(mx, my, mz);
			OpenMove::rotate(dircc, 0, 1, 0);
			if (animationMario >= 0 && animationMario < 1) {
				marprin->Draw();
			}
			if (animationMario >= 1 && animationMario < 2) {
				marprinO->Draw();
			}
			if (animationMario >= 2) {
				marprinT->Draw();
				animationMario = 0;
			}
			
			glPopMatrix();

			//captura de monedas y conteo 
			if (coinRandom) {
				srand(time(NULL));
				secretcoin = rand() % 3; //del 0 al 2
				coinRandom = false;
			}

			coinMarioRecc(secretcoin);

			glPushMatrix();
				if (!coinDelete[0]) {
					glPushMatrix();
					OpenMove::traslate(coinPosx1[secretcoin], 102.5, coinPosz1[secretcoin]);
					OpenMove::rotate(animCoin, 0, 1, 0);
					coin->Draw();
					glPopMatrix();
				}
				if (!coinDelete[1]) {
					glPushMatrix();
					OpenMove::traslate(coinPosx2[secretcoin], 102.5, coinPosz2[secretcoin]);
					OpenMove::rotate(animCoin, 0, 1, 0);
					coin->Draw();
					glPopMatrix();
				}
				if (!coinDelete[2]) {
					glPushMatrix();
					OpenMove::traslate(coinPosx3[secretcoin], 102.5, coinPosz3[secretcoin]);
					OpenMove::rotate(animCoin, 0, 1, 0);
					coin->Draw();
					glPopMatrix();
				}
				if (!coinDelete[3]) {
					glPushMatrix();
					OpenMove::traslate(coinPosx4[secretcoin], 102.5, coinPosz4[secretcoin]);
					OpenMove::rotate(animCoin, 0, 1, 0);
					coin->Draw();
					glPopMatrix();
				}
				if (!coinDelete[4]) {
					glPushMatrix();
					OpenMove::traslate(coinPosx5[secretcoin], 102.5, coinPosz5[secretcoin]);
					OpenMove::rotate(animCoin, 0, 1, 0);
					coin->Draw();
					glPopMatrix();
				}
			glPopMatrix();


			//Castillo 
			glPushMatrix();
			//	OpenMove::scale(.014, .014, .014);
				//-Z es hacia abajo de la camara inicial,z es hacia arriba
				//-x es hacia la derecha y x es hacia la izquierda
			OpenMove::traslate(-0, 100, -0);
			castle_grass->Draw();
			castle_tree->Draw();
			castle_windows->Draw();
			castle->Draw();
			glPopMatrix();

			static float MovS = 0;
			MovS += .03;
			float A = sin(MovS) * 2;
			float B = cos(MovS) * 2;

			//Stars
			if (coinRecc >= 5) {
				glPushMatrix();
				//OpenMove::traslate(-1, 104, 42);
				OpenMove::traslate(-13, 106, 20);
				OpenMove::traslate(0, A, 0);
				OpenMove::rotate(animCoin + 2, 0, 1, 0);
				OpenMove::scale(2, 2, 2);
				star->Draw();
				glPopMatrix();
			}

			if (nuevoMapa) {
				glPushMatrix();
				OpenMove::traslate(-1, 106, 20);
				OpenMove::traslate(A, A, B);
				//OpenMove::traslate(-13, 106, 20);
				OpenMove::rotate(140, 0, 1, 0);
				OpenMove::scale(2, 2, 2);
				boo->Draw();
				glPopMatrix();

				glPushMatrix();
				OpenMove::traslate(-20, 106, 10);
				OpenMove::traslate(A - .1, A, B + .2);
				//OpenMove::traslate(-13, 106, 20);
				OpenMove::rotate(140, 0, 1, 0);
				OpenMove::scale(2, 2, 2);
				boo->Draw();
				glPopMatrix();

				glPushMatrix();
				OpenMove::traslate(-39, 106, 26);
				OpenMove::traslate(A - .1, A, B - .2);
				//OpenMove::traslate(-13, 106, 20);
				OpenMove::rotate(140, 0, 1, 0);
				OpenMove::scale(2, 2, 2);
				boo->Draw();
				glPopMatrix();

			}

			//Thwomp
			glPushMatrix();
			OpenMove::traslate(-36, 103.5 + (twompMovAnim), 8);
			OpenMove::scale(.1, .1, .1);
			thwomp->Draw();
			glPopMatrix();

			if (!twompMovBoolAux) {
				twompMovAnim -= .5;
			}
			else {
				twompMovAnim += .3;
			}
			if (twompMovAnim >= 2) {
				twompMovBoolAux = false;
			}
			if (twompMovAnim <= 0) {
				twompMovBoolAux = true;
			}
			
			//Estrella
			if (!Huevoshi) {
				glPushMatrix();
				OpenMove::traslate(-3, 102.5, 35);
				OpenMove::rotate(animCoin + 2, 0, 1, 0);
				OpenMove::scale(2, 2, 2);
				flower->Draw();
				glPopMatrix();
			}
			if (mx == -3 && mz == 35 && my == 102.5) {
				Huevoshi = true;
			}

			//Huevo
			glPushMatrix();
			OpenMove::traslate(-40, 102.5, -3);
			OpenMove::rotate(animCoin + 2, 0, 1, 0);
			OpenMove::scale(2, 2, 2);
			egg->Draw();
			glPopMatrix();

			if (mx == -40 && mz == -3 && my == 102.5) {
				glPushMatrix();
				OpenMove::traslate(-40, 107, -3);
				OpenMove::rotate(-205, 0, 1, 0);
				OpenMove::scale(.50, .50, .50);
				billboardYoshi->Draw();
				glPopMatrix();
			}

			//Hongo protegido
			glPushMatrix();
			OpenMove::traslate(-8, 102.5, 13);
			OpenMove::rotate(animCoin + 2, 0, 1, 0);
			OpenMove::scale(3, 3, 3);
			muss->Draw();
			glPopMatrix();
			if (PanelBoo) {
				glPushMatrix();
				OpenMove::traslate(-8, 107, 13);
				OpenMove::rotate(-205, 0, 1, 0);
				OpenMove::scale(.75, .75, .75);
				billboardBoo->Draw();
				glPopMatrix();
			}

			//Particulas
			glPushMatrix();
			//glTranslated(-1, 10, 42);
			OpenMove::traslate(-50, 80, -200);
			//	miOGL::traslate(0, 100, 15);
			//glRotated(90, 1, 0, 0);
			//glScaled(200, 200, 200);
			OpenMove::scale(50, 50, 50);
			glDisable(GL_LIGHTING);
			hojas[0]->draw();
			glEnable(GL_LIGHTING);
			glPopMatrix();

			//Particulas
			glPushMatrix();
			//glTranslated(-1, 10, 42);
			OpenMove::traslate(-20, 80, -200);
			//	miOGL::traslate(0, 100, 15);
			//glRotated(90, 1, 0, 0);
			//glScaled(200, 200, 200);
			OpenMove::scale(50, 50, 50);
			//glEnable(GL_LIGHTING);
			glDisable(GL_LIGHTING);
			hojas[0]->draw();
			glEnable(GL_LIGHTING);
			//glDisable(GL_LIGHTING);
			glPopMatrix();
			


			//Hongo
			glPushMatrix();
			
			if ((mx == (-44 + booContadorX) && mz ==(21 + booContadorZ))) {
				CtrlAnims[4] = true;
				
			}
			if (!(CtrlAnims[4])) {
				OpenMove::traslate(-44 + (booContadorX), 103.5, 21 + (booContadorZ));
				OpenMove::scale(3, 3, 3);
				muss->Draw();
				if (CtrlAnims[0]) {
					booContadorZ += 1;
					if (booContadorZ >= 5) {
						CtrlAnims[0] = false;
						CtrlAnims[1] = true;
					}
				}
				if (CtrlAnims[1]) {
					booContadorX += 1;
					if (booContadorX >= 12) {
						CtrlAnims[1] = false;
						CtrlAnims[2] = true;
					}
				}
				if (CtrlAnims[2]) {
					booContadorZ -= 1;
					if (booContadorZ <= 0) {
						CtrlAnims[2] = false;
						CtrlAnims[3] = true;
					}
				}
				if (CtrlAnims[3]) {
					booContadorX -= 1;
					if (booContadorX <= 0) {
						CtrlAnims[3] = false;
						CtrlAnims[0] = true;
					}
				}
			}
			glPopMatrix();

			//Fantasma Protector
			glPushMatrix();

			if ((mx == (-44 + ProtectBooX) && mz == (21 + ProtectBooZ))) {
				CtrlAnimsAux[4] = true;

			}
			if (!(CtrlAnimsAux[4])) {
				OpenMove::traslate(-11 + (ProtectBooX), 103.5, 10 + (ProtectBooZ));
				OpenMove::scale(3, 3, 3);
				OpenMove::rotate(140, 0, 1, 0);
				boo->Draw();
				if (CtrlAnimsAux[0]) {
					ProtectBooZ += .5;
					if (ProtectBooZ >= 5) {
						CtrlAnimsAux[0] = false;
						CtrlAnimsAux[1] = true;
					}
				}
				if (CtrlAnimsAux[1]) {
					ProtectBooX += .5;
					if (ProtectBooX >= 6) {
						CtrlAnimsAux[1] = false;
						CtrlAnimsAux[2] = true;
					}
				}
				if (CtrlAnimsAux[2]) {
					ProtectBooZ -= .5;
					if (ProtectBooZ <= 0) {
						CtrlAnimsAux[2] = false;
						CtrlAnimsAux[3] = true;
					}
				}
				if (CtrlAnimsAux[3]) {
					ProtectBooX -= .5;
					if (ProtectBooX <= 0) {
						CtrlAnimsAux[3] = false;
						CtrlAnimsAux[0] = true;
					}
				}
			}

			glPopMatrix();

			

			glPushMatrix();
			for (int i = 0; i < 40; i++) {
				//billboards
				glPushMatrix();
				glTranslatef(0, 45, 0);
				billBoard[i]->Draw(-12, 112, 51);
				glPopMatrix();
			}
			glPopMatrix();

		}
		
		//No tocar
		SwapBuffers(hDC);
	}

};
#endif

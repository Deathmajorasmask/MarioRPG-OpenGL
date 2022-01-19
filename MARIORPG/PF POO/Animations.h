#ifndef __Animations
#define __Animations

//void MovMario(int dirMov);
//Menor de MZ- es hacia arriba, Mz+ es hacia abajo del mapa
//MX- es hacía la izquierda, Mx+ es hacia la derecha 


class Animatic {
	friend class Scene;
private:
	float mx = -1, mz = 42, my = 102.5, cury= 65.5;
	int dircc = 360, contA=0, animationMario=0;
	bool battleGet = false, nuevoMapa=false, renderMultimapa=false,ganarFinal=false, gameOver=false, failDrop=false, pulsB=false, pulsX=false, AnimBowser=true, PanelBoo = false;
	int vistaCamare = 2;
	//Manejo de batalla
	bool attMario0 = false, attMario1 = false, attMario2 = false, attMario3 = false, attMario4 = false, verificar=true, backBowser=false;
	bool nuevaCamera = true, turnMario = true, phantomSecMov[2], twompMovBool=false, piraMovOp=false, pirswitch=false, twompMovBoolAux = false;
	int vidaBowser = 100, vidaMario=50, FlowerPoint=20, pirCont=0;
	float egmy = 61, flowerSpan = 0, starCaid=70, lan=45, clocking=0, bowY=62, phantomScale=0,starRotated=360, twompMovY = 70, piraMovY=50, booContadorX = 0, booContadorZ = 0;
	float twompMovAnim = 0, ProtectBooX = 0, ProtectBooZ = 0;
	//Manejo de la moneditas
	bool coinRandom = true, coinDelete[5], coinVerRecc[5];
	int animCoin = 360, coinRecc = 0, secretcoin;

	static int coinPosx1[3], coinPosz1[3], coinPosx2[3], coinPosz2[3], coinPosx3[3], coinPosz3[3] , coinPosx4[3] , coinPosz4[3],
		coinPosx5[3] , coinPosz5[3];

	//Puente mx0 mz13 , 10 mz13 ||mx0 mz8- mx-16 mz8 || mx-16 mz8 - mz7||mx-21mz7 - mz6||mx-21/mz6
	//mx-24 mz4/mx-26 mz4 || mx-26 mz1/mx-29 mz1 || mx-29 mz-19||mx-42 mz-19||mx-42 mz-9||mx-44 mz-9
	//mx-44 mz-2||mx-45 mz-2||mx-45 mz2||mx-47 mz2||mx-47 mz29
	//mx-45 mz29||mx-45 mz33||mx-43 mz33||mx-43 mz36||mx-39 mz36||mx-34 mz36||mx-34 mz42||mx-28 mz42
	//mx-28 mz44||mx-15 mz44||mx-15 mz46||mx4 mz46||mx4 mz30||mx15 mz30||mx15 mz14||mx22 mz14||mx22 mz7
	//mx7 mz-11||mx3 mz-11||mx3 mz8
	//Aumento del puente mx7-mz7||mx3-mz7||||mx7 mz-11/mx3

public:


	void manageAnimationMario(int stateAnimation) {
		if (stateAnimation = 1) {
			animationMario++;
		}
		if (stateAnimation = 0){
			animationMario = 0;
		}
	}

	void switrenderMulti() {
		renderMultimapa = !renderMultimapa;
	}

	void switCamareO() {
		vistaCamare = 1;
	}

	void switCamareC() { //Cambiar a camara normal
		vistaCamare = 0;
	}
	void switCamareT() {
		vistaCamare = 2;
	}

	bool banMov = false;
	void MovMario(int dirMov) {	
		
		if (dirMov == 1){ //S
			//Movimientos
			dircc = 180;
			//Total de colisiones
			if (mz == 13 && mx >= 0 && mx <= 10) { //Baja del puente
				my-=.5;
				mz++;
			}
			else if(mz == 7 && mx >= 3 && mx <= 7) {
				my -= .5;
				mz++;
			}
			else if (mz==29 && mx<=-45 && mx>=-47||mz==33 &&mx<=-43 && mx>=-45||mz==36 &&mx<=-39 &&mx>=-43||
				mz==39 && mx<=-34 &&mx>=-39||mz==42 && mx<=-28 && mz>=-34||mz==44 &&mx<=-15 &&mx>=-28||
				mz==46 && mx<=4 &&mx>=-15) {
				banMov = true;
			}
			else if (mz==30 &&mx<=15 &&mx>=4||mz==14 && mx<=22 &&mx>=15) {
				banMov = true;
			}
			else if (mz == 7 && mx <= -35  && mx >= -37) { //twomp colission
				banMov = true;
			}
			else if (mz == 10 && mx <= -5 && mx >= -12) {
				PanelBoo = true;
				banMov = true;
			}
			else {
				PanelBoo = false;
				banMov = false;
				mz++;
			}

		}
		else if (dirMov == 2) { //W
			//Movimientos
			dircc = 360;
			//Total de colisiones
			if (mz == 13 && mx >= 0 && mx <= 10) { //sube del puente
				my+=.5;
				mz--;
			}
			else if (mz == 7 && mx >= 3 && mx <= 7) {
				my += .5;
				mz--;
			}
			else if (mz==-11 && mx<=7 && mx>=3) {//Llego a la puerta
				banMov = true;
				battleGet = true;
			}
			else if (mz==8 && mx <=2 && mx >= -16) {
				banMov = true;
				/*pz += 1;
				dz += 1;*/
			}
			else if (mz==7 && mx>=-21 && mx<=-16 || mz==6 && mx <=-21 && mx>=-24 ||mz==4 && mx<=-24 &&mx>=-26||
				mz==1 &&mx<=-26 && mx>=-29||mz==-19 && mx<=-29 && mx>=-42||mz==7 && mx<=22 && mx>=7) {
				banMov = true;
			}
			else if (mz==-9 && mx<=-42 && mx>=-44 || mz==-2 && mx<=-44 && mx>=-45 ||mz==2 && mx<=-45 && mx >=-47||
				mz==-11 &&mx<=7 &&mx>=3) {
				banMov = true;
			}
			else if (mz == 9 && mx <= -35 && mx >= -37) { //Twomp
				banMov = true;
			}
			else if (mz== 14 && mx <= -5 && mx >= -12) {
				PanelBoo = true;
				banMov = true;
			}
			else {
				PanelBoo = false;
				banMov = false;
				mz--;
			}
			
		} 
		else if (dirMov == 3) { //D
			//Movimientos
			dircc = 270;
			//Total de colisiones
			if (mx==0 && mz>=8 && mz<=13) { //Sube al puente
				//my++;
				my += .5;
				mx++;
			} else if (mx == 10 && mz>=7 && mz <=13) { //Baja del puente
				my-=.5;
				mx++;
			}
			else if (mx==-16 && mz<8 && mz>=7) { 
				banMov = true;
			}
			else if (mx==-21 && mz<7 && mz>=6 || mx==-24 && mz<6 && mz>=4 ||mx == -26 && mz<4 && mz>=1||
				mx==-29 && mz<1 && mz>=-19) {
				banMov = true;
			}
			else if (mx==4 &&mz<=46 &&mz>=30||mx==15&&mz<=30 &&mz>=14||mx==22 && mz<=14 &&mz>=7||mx==7 &&mz<=7 &&mz>=-11) {
				banMov = true;
			}
			else if (mx == -37 && mz <= 9 && mz >= 7) { //Twomp
				banMov = true;
			}
			else if (mx == -13 && mz<= 14 && mz>=10) {
				PanelBoo = true;
				banMov = true;
			}
			else {
				PanelBoo = false;
				banMov = false;
				mx++;
			}

		} 
		else if(dirMov == 4) { //A
			//Movimientos
			dircc = 90;
			//Total de colisiones
			if (mx == 0 && mz >= 8 && mz <= 13) { //Baja del puente
				//my--;
				my += .5;
				mx--;
			}
			else if(mx == 10 && mz >= 7 && mz <= 13) { //Sube del puente
				mx--;
				//my++;
				my += .5;
			}
			else if (mx==-42 && mz<=-9 && mz>=-19 ||mx==-44 && mz<=-2 && mz>=-9|| mx==-45 &&mz<=2 && mz>=-2||
				mx==-47 && mz<=29 && mz>=2) {
				banMov = true;
			}
			else if (mx==-45 && mz<=33 &&mz>=29||mx==-43 && mz<=36 && mz>=33||mx==-39 && mz<=39 &&mz>=36||
				mx==-34 && mz<=42 && mz>=36||mx==-28 &&mz<=44 &&mz>=42||mx==-15 &&mz<=46 && mz>=44||mx==3 &&mz<=8 &&mz>=-11) {
				banMov = true;
			}
			else if (mx == -35 && mz <= 9 && mz >= 7) { //twomp
				banMov = true;
			}
			else if (mx == -5 && mz <= 14 && mz >= 10) {
				PanelBoo = true;
				banMov = true;
			}
			else {
				PanelBoo = false;
				banMov = false;
				mx--;
			}


		} 
		else{

		}

	}
	
	void BowserAttack(int attck) {

		if (vidaBowser <= 0) {
			ganarFinal = true;
		}

		if (attck==1) { //Golpe basico
			vidaMario -= 10;
		}
		else if (attck == 2) { //Explosión
			vidaMario -= 15;
		}
		else if (attck == 3) { //
			vidaMario -= 25;
		}
		else if (attck == 4) { //Maxima llamas
			vidaMario -= 35;
		}
		else { //Golpe mediocre
			vidaMario -= 5;
		}
	}

	void MarioAttack(int attck) {
		if (vidaMario <= 0) {
			gameOver = true;
		}

		if (attck == 1 ) { //Golpe avanzado egg
			if (FlowerPoint >= 4) {
				FlowerPoint -= 4;
				vidaBowser -= 15;
			}
			else {
				failDrop = true;
			}
		}
		if (attck == 2 ) { //flamitas
			if (FlowerPoint >= 7) {
				vidaBowser -= 20;
			}
			else{
				failDrop = true;
			}
		}
		if (attck == 3 ) { //recarga de flower point
			FlowerPoint += 5;
		}
		if (attck == 4 ) { //Vida
			if (FlowerPoint >= 7) {
				vidaMario += 20;
			}
			else {
				failDrop = true;
			}
		}
		if(attck ==0) { //Golpe mediocre
			vidaBowser -= 7;
		}

	}

	bool battlereturn() {
		return battleGet;
	}

	bool turnMarioReturn() {
		return turnMario;
	}

	void pressB() {
		if (pulsB) {
			if (contA == 0) { //Usa golpe avanzado
				attMario1 = true;
			}
			else if (contA == 1) { //EspEstrellas
				attMario2 = true;
			}
			else if (contA == 2) { //Recarga FF
				attMario3 = true;
			}
			else { //Sube su vida
				attMario4 = true;
			}
		}
		pulsB = true;
		//pulso de marcadores (mostrar tablas)

	}

	void pressUp() {
		if (pulsB) {
			contA--;
			cury += .1;
			if (contA<0) {
				cury = 65.2;
				contA = 3;
			}
		}
		else {

		}

	}

	void pressDown() {
		if (pulsB) {
			contA++;
			cury -= .1;
			if (contA>3) {
				cury = 65.5;
				contA = 0;
			}
		}
		else {

		}
	}

	void coinMarioRecc(int random) {
		
		//Animación de la monedas
		animCoin--;
		if (animCoin <= 1) {
			animCoin = 360;
		}

		//Saber si las ha tocado
		if (!coinVerRecc[0]) {
			if (mx == coinPosx1[random] && mz == coinPosz1[random]) {
				coinDelete[0] = true;
				coinRecc++;
				coinVerRecc[0] = true;
			}
		}
		if (!coinVerRecc[1]) {
			if (mx == coinPosx2[random] && mz == coinPosz2[random]) {
				coinDelete[1] = true;
				coinRecc++;
				coinVerRecc[1] = true;
			}
		}
		if (!coinVerRecc[2]) {
			if (mx == coinPosx3[random] && mz == coinPosz3[random]) {
				coinDelete[2] = true;
				coinRecc++;
				coinVerRecc[2] = true;
			}
		}
		if (!coinVerRecc[3]) {
			if (mx == coinPosx4[random] && mz == coinPosz4[random]) {
				coinDelete[3] = true;
				coinRecc++;
				coinVerRecc[3] = true;
			}
		}
		if (!coinVerRecc[4]) {
			if (mx == coinPosx5[random] && mz == coinPosz5[random]) {
				coinDelete[4] = true;
				coinRecc++;
				coinVerRecc[4] = true;
			}
		}
		

	}

	bool victoriaAbsurda() {
		if (coinRecc >= 5) {
			ganarFinal = true;
			return true;
		}
		return false;
	}
};

#endif 

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "math.h"
#include "fctMoment.h"
#include "myBmpCouleur.h"



//prédefinie
int NumImageBD = 0;
int N = 20; //ordre defaut pour image entree
int Nbd = 20; // ordre defaut pour image BD
int OrdreA = 20;
int lengthName = 11;
double  seuil = 0.0;
char nameImage[11];
int flagTrouver =0;
double distanceM=0; // distance entre 2 programme
double seuilM = 5;
// moments principal
int main(){
	printf("entrez l'ordre pécision (exemple 20) : ");
	scanf("%d",&N);
	printf("l'ordre pécision est %d\n",N);
	Nbd = N ;
	//initiation
	printf("programme en initalisation....\n");
	char **ANameBD = malloc(26*sizeof(char*));
	double **tabA=tabCoeffA(N);
	double **tabMIT ; //creer tabMIT pour creertabMLeg
	double **tabMleg ;
	double **imageBin; 
	double dimX,dimY;
	printf(".read file..\n");
		//read text
	FILE *file ;
	if((file = fopen("BD.txt","r")) != NULL){
		fscanf(file,"%d\n",&NumImageBD);
		char **NameBD=malloc(NumImageBD*sizeof(char*));//"A.bmp"
		for(int i=0;i<NumImageBD;i++){
		NameBD[i] = (char*)calloc(lengthName,sizeof(char));
		}
		for(int i=0;i<NumImageBD;i++){
				fscanf(file,"%s\n",NameBD[i]);
				ANameBD[i] = NameBD[i];
		}
		fclose(file);
		printf("finir de lire les noms photos\n");
	}
	else {
		printf("the file is opeaned error\n");
		//char NameBD[NumImageBD][lengthName];//"A.bmp" 
		return 1;
	}

	//lire les image dans BD
	printf("commencer à lire et creer moments pour les photos\n");
	double ***AMleg = malloc(NumImageBD*sizeof(double**));
	for(int i =0; i<NumImageBD;i++){
		BmpImg imageChar = readBmpImage(ANameBD[i]);
		dimX = imageChar.dimX;
		dimY = imageChar.dimY;
		imageBin = creerTableau(dimX,dimY);
		for(int i =0; i<dimX;i++){
			for(int j=0; j<dimY;j++){
					{
						if(getPixelS( imageChar,i,j )!=0){
							imageBin[i][j] = 1;
						}
					}
			}
		}
		if(imageBin !=NULL){
			tabMIT = tabMomentIT(imageBin,dimX,dimY,Nbd); //creer tabMIT pour creertabMLeg
			tabMleg = tabMomentLeg(tabMIT,tabA,Nbd);
			AMleg[i] = tabMleg ;
			freeTableau(imageBin,dimX);
			freeTableau(tabMIT,N+1);//optimise espace memoire
			printf("....%d / %d .....\n",i+1,NumImageBD );
		}
		else{printf("erreur d'initailisation..."); return -1;}
	}
	printf("finir initailisation\n");
	//fin init



	// read image 
	printf("entrez le nom de limage(example : A.bmp) :  ");
	scanf("%s",nameImage);
	printf("%s\n",nameImage);
	BmpImg imageChar = readBmpImage(nameImage);
	dimX = imageChar.dimX;
	dimY = imageChar.dimY;
	imageBin = creerTableau(dimX,dimY);
	for(int i =0; i<dimX;i++){
		for(int j=0; j<dimY;j++){
				{
					if(getPixelS( imageChar,i,j )!=0){
						imageBin[i][j] = 1;
					}
				}
		}
	}
	//reconnaitre la forme
	tabMIT = tabMomentIT(imageBin,dimX,dimY,N); //creer tabMIT pour creertabMLeg
	tabMleg = tabMomentLeg(tabMIT,tabA,N);
	printf("mleg reussir\n");
	for(int i=0;i< NumImageBD;i++){
		printf("comparer %d / %d..",i+1,NumImageBD);
		distanceM = distanceMoment(tabMleg,AMleg[i],N);
		printf("distance = %lf \n",distanceM);
		if(distanceM < seuilM){
			seuilM = distanceM;
			flagTrouver =i+1;
		}
		freeTableau(AMleg[i],N+1);
	}
		if(flagTrouver != 0 ){printf("image retrouver ! --> %s \n",ANameBD[flagTrouver -1]);}
		else{printf("image inconnu\n");}
	//suppimer AMLeg
	freeTableau(imageBin,dimX);
	freeTableau(tabMIT,N+1);//optimise espace memoire
	
}//fin main








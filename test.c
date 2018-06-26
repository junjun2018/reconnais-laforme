#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "math.h"
#include "myBmpCouleur.h"
#include "fctMoment.h"
//prédefinie
int NumImageBD = 0;
int N = 30; //ordre defaut pour image entree
int Nbd = 10; // ordre defaut pour image BD
int OrdreA = 10;
int lengthName = 5;
double  seuil = 0.1;
char nameImage[11];
int flagTrouver =0;
double distanceM; // distance entre 2 programme
double seuilM = 40;

//test moment legendre
int main(){

double **imageBin;
int dimX,dimY ;
double** tabA=tabCoeffA(N);
double ***AMleg = malloc(2*sizeof(double**));

printf("entrez le nom de limage(example : A.bmp) :  ");
scanf("%s",nameImage);
printf("%s\n",nameImage);

BmpImg imageChar = readBmpImage(nameImage);
dimX = imageChar.dimX;
dimY = imageChar.dimY;
printf("tabA\n");
for(int i =0; i<=N;i++){
	for(int j=0; j<=N;j++){
			if(tabA[i][j] != 0){
				printf("%lf/",tabA[i][j]);
			}
			else{printf("%lf/",tabA[i][j]);}
	}
	printf("..\n");
}

printf("imageBin\n");
imageBin = creerTableau(dimX,dimY);
for(int i =0; i<dimX;i++){
	for(int j=0; j<dimY;j++){
			{
				if(getPixelS( imageChar,i,j )!=0){
				imageBin[i][j] = 1;}
			}	
	}
}

for(int i =0; i<dimX;i++){
	for(int j=0; j<dimY;j++){
			{
				printf("%d",(int)imageBin[i][j] );
			}
	}
	printf("..\n");
}

printf("mit\n");
double** tabMIT = tabMomentIT(imageBin,dimX,dimY,N);

for(int i =0; i<=N;i++){
	for(int j=0; j<=N;j++){
			if(tabMIT[i][j] != 0){
				printf("%lf/",tabMIT[i][j]);
			}
			else{printf("%lf/",tabMIT[i][j]);}
	}
	printf("..\n");
}
printf("mleg\n");
double** tabMleg = tabMomentLeg(tabMIT,tabA,N);
AMleg[0] = tabMleg;
for(int i =0; i<=N;i++){
	for(int j=0; j<=N;j++){
			if(tabMleg[i][j] != 0){
				printf("%lf/",AMleg[0][i][j]);
			}
			else{printf("%lf/",AMleg[0][i][j]);}
	}
	printf("..\n");
}



double ** res1 = tabCalculRebuild(N, dimX, dimY, AMleg[0], tabA);
for(int i = 0; i<dimX;i++){
	for(int j=0;j<dimY;j++){
		//if(res1[i][j]>5||res1[i][j]<-5){
		printf("%d",(int)res1[i][j]);
	}
	printf("..\n");
}

printf("...freetab...\n");
freeTableau(imageBin,dimX);
freeTableau(tabMIT,N+1);
freeTableau(res1,dimX);
freeTableau(tabA,N+1);
freeTableau(tabMleg,N+1);
printf("......\n");



return 0;
}


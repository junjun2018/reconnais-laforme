#include <stdlib.h>
#include <stdio.h>
#include "math.h"
#include "fctMoment.h" 
/**
* ce fonction est pour calculer les moment geometirque 
* @para image limage a utiliser
* @para x dimantion image
*	@para y dimansion 
* @para p
*	@para q
* @returen un moment geometrique
*/
double momentGeo(double **image,int x, int y,int p, int q){
	int rows,cols;
	double newX , newY;
	double res =0;
//	double pasX ; //la divise marche pas
//	double pasY ;
	for(rows =0 ;rows<x;rows++){
		for(cols = 0; cols<y;cols++){
			//newX = -1.0 + 2.0*rows/(x-1.0); newY =-1.0 + 2.0*cols/(y-1.0);
			if (image[rows][cols]!= 0){    // pour ameliorer
				
				res += pow(rows,p) * pow(cols,q) ;
			}
//			printf("newx = %lf, newy =%lf \n",newX,newY);
//printf("res = %lf, p = %d, q = %d\n",res,p,q);
		}
	}
//printf("res = %lf, p = %d, q = %d\n",res,p,q);
//if(res<0.000001 && res>-0.000001){res=0;}
return res;
}
/**
* ce fonction est pour creer un tableau de 2 dimention
* @para x 
* @para y
* @return un tableau de 2 dimention
*/
double **creerTableau(int x, int y){
	double **tab = (double**)malloc(x*sizeof(double*));
	for(int i=0;i<x;i++){
		tab[i] = (double*)calloc(y,sizeof(double));
		
	}
	return tab;
}
/**
* ce fonction est pour supprimer un tableau
* @para adrees du tableau 
* @para length
*/
void freeTableau(double **Tab, int length){
	for(int i=0 ;i<length ; i++){
		free(Tab[i]);
	} 
	free(Tab);
}

/**
* ce fonction est pour creer un tableau des moment geometirque 
* @para image limage a utiliser
* @para x
*	@para y
* @para n
* @returen un tableau des moment geometrique
*/
double **tabMomentGeo(double **image, int x, int y, int n){
	double **res = creerTableau (n+1,n+1); 
	int p, q;
	for(p = 0; p<=n;p++){
		for(q=0; q<=n-p;q++){
			res[p][q] = momentGeo(image,x,y,p,q);
		}
	}
return res;
}

/**
* ce fonction est pour calculer les moment translater et normalise attention x et y varie entre -1 et 1
* @para image limage a utiliser
* @para x
*	@para y
* @para p
*	@para q
* @returen un moment translater et invariant
*/
double momentIT(double **image,int x, int y,int p, int q){
	int rows,cols;
	double newX= -1.0,newY= -1.0;
	double puissance = (p+q+2.0)/2.0;
	double res =0.0;
	double omega = momentGeo(image,x,y,0,0);
	double xM = momentGeo(image,x,y,1,0)/omega;
	double yM = momentGeo(image,x,y,0,1)/omega;
	for(rows =0 ;rows<x;rows++){
		for(cols = 0; cols<y;cols++){
	//		newX = (rows-xM)/(x); newY =(cols-yM)/(y);
			if(image[rows][cols]!=0){res += (pow((rows-xM),p) * pow((cols-yM),q))/pow(omega,puissance);}//car img[x][y] =1;
	//printf("res = %.25lf\n",res)
		//	printf("omega=%lf,xm=%lf,ym=%lf,newx =%lf ,newy =%lf ,p = %d,q = %d, res = %.16lf\n",omega,xM,yM,newX,newY,p,q,res);
		}
	}
//	printf("omega=%lf,xm=%lf,ym=%lf,newx =%lf ,newy =%lf ,",omega,xM,yM,newX,newY);
//  printf("res = %lf \n", res);
//if(res<0.000001 && res>-0.000001){res=0;}
return res;
}
/**
* ce fonction est pour creer un tableau des moment centre et norme
* @para image limage a utiliser
* @para x
*	@para y
* @para n
* @returen un tableau des moment geometrique
*/
double **tabMomentIT(double **image, int x, int y, int n){
	double **res = creerTableau (n+1,n+1); 
	int p, q;
	for(p = 0; p<=n;p++){
		for(q=0; q<=n-p;q++){
			res[p][q] = momentIT(image,x,y,p,q);
		}
	}
return res;
}

/**
* ce fonction est pour calculer les coefficient A(ni)
* @para k ordre
* @returen un tableau de coefficient
*/
double **tabCoeffA(int k){
	double **res = creerTableau(k+1,k+1);
	res[0][0] = 1;
	res[1][0] =0;
	res[1][1]=1;
	for(int i = 2; i<=k; i++){
		for(int j = 0 ; j<=i; j++ ){
			if(j == 0) {res[i][j] = -(i-1.0)* res[i-2][0]/i;}
			if(j == i) {res[i][j] = (2.0*i-1.0)*res[i-1][i-1]/i;}
			else{res[i][j] = ((2.0*i-1.0)*res[i-1][j-1]-(i-1.0)*res[i-2][j])/i;}
			if(res[i][j]<0.000001 && res[i][j]>-0.000001){res[i][j]=0.0;}
		}
	}
return res;
}

/**
* ce fonction est pour calculer le moment legendre
* @para **tabMomentIT
* @para **A //coefficiant A
* @para k ordre
* @para p
* @para q
* @returen un moment legendre
*/
double momentLeg(double **tabMIT, double **A, int p, int q){
	double Cpq = (2*p+1) *(2*q+1)*0.25;
	double res  =0;
	for(int i = 0; i<=p; i++){
		for(int j = 0 ; j<=q; j++){
			if(tabMIT[i][j] != 0){
				res += A[p][i]*A[q][j]*tabMIT[i][j];
			}
		}
	} 
	res = res *Cpq;
//printf("res = %lf \n", res);
return res;
}

/**
* ce fonction est pour creer un tableau des moment legendre 
* @para **tabMIT
* @para n ordre
* @returen un tableau des moment 
*/
double **tabMomentLeg(double **tabMIT, double **A ,int n){
	double **res = creerTableau (n+1,n+1); 
	int p, q;
	for(p = 0; p<=n;p++){
		for(q=0; q<=n-p;q++){
			res[p][q] = momentLeg(tabMIT,A,p,q);
		}
	}
return res;
}

/**
* ce fonction est pour calculer pn(x)
* @para **tabcoefA
*	@para x
* @para n
* @return Pn(x) 
*/

double calculPn (double **tabCoeffA, int n, double x){
	double res =0;	
	for(int i=0;i<=n;i++){
		if(tabCoeffA[n][i] != 0){
			res += tabCoeffA[n][i] *pow(x,i);
			//if(c == 't'){printf("c = %c, coeffA = %lf, n= %d, i = %d x=%lf\n",c,res,n,i,x);}
		}	
	}
return res;
}

/**
* ce fonction est pour calculer f(x,y)
* @para N
*	@para x
* @para y
* @para **tabMomentLeg
* @para **tabcoefA
return f(x,y)
*/

double calculRebuild(int N, double x, double y, double **tabMomentLeg, double **tabCoeffA){
	double res =0;	
	for (int p=0;p<=N;p++){
		for (int q=0;q<=N-p;q++){
			res += tabMomentLeg[p][q]*calculPn(tabCoeffA,p,x)*calculPn(tabCoeffA,q,y);
	//	printf(" tabM = %lf, pnp = %lf, pnq = %lf \n",tabMomentLeg[p][q],calculPn(tabCoeffA,'p',p,x),calculPn(tabCoeffA,'q',q,y));
		}
	}
//	if(res<0.000001 && res>-0.000001){res=0;}
return res;
}

/**
* ce fonction est pour calculer tab f(x,y)
* @para N
*	@para x
* @para y
* @para **tabMomentLeg
* @para **tabcoefA
return f(x,y)
*/
double** tabCalculRebuild(int N, int xMax, int yMax, double **tabMomentLeg, double**tabCoeffA){
	double **res = creerTableau (xMax,yMax); 
	double newX, newY;
	for (int x=0;x<xMax;x++){
		for (int y=0;y<yMax;y++){
			newX = -1.0 + 2.0*x/(xMax); newY =-1.0 + 2.0*y/(yMax);
			res[x][y] = calculRebuild(N, newX, newY, tabMomentLeg, tabCoeffA);
//		if(res[x][y]==0){res[x][y] =0;}
//		else{res[x][y] = 1;}
//			printf("x= %d,y=%d,newx = %lf, newy = %lf\n",x,y,newX, newY);
		}
	}
return res;
}


/**
* ce fonction est pour calculer l'erreur
* @para N ordre
*	@para ** image
* @para xMax
* @para yMax
return erreur
*/

double errorRebuild (int N, double **imageBin,double**tabA, int dimX, int dimY){
	double **tabMIT = tabMomentIT(imageBin,dimX,dimY,N); //creer tabMIT pour creertabMLeg
	double **tabMleg = tabMomentLeg(tabMIT,tabA,N);
	double **tabRebuild = tabCalculRebuild(N, dimX, dimY,tabMleg,tabA);
	double res1=0;
	double res2=0;
	for (int x = 0; x < dimX; x++){
		for (int y=0; y < dimY; y++){
			res1 += (tabRebuild[x][y]-imageBin[x][y])*(tabRebuild[x][y]-imageBin[x][y]);
			res2 += imageBin[x][y] * imageBin[x][y];
		}
	}
return res1/res2;
}

/**
* ce fonction est pour la distance
* @para **lambda1
* @para **lambda2
*	@para N
* @return distance 
*/

double distanceMoment(double **tabMleg1, double **tabMleg2,int N){
	double res = 0;
	for(int p=0;p<=N;p++){
		for(int q=0;q<=N;q++){
			res += (tabMleg1[p][q]-tabMleg2[p][q])*(tabMleg1[p][q]-tabMleg2[p][q]);
//			printf("tab1 = %lf, tab2 = %lf\n",tabMleg1[p][q],tabMleg2[p][q]);
//			printf("res = %lf, p = %d, q= %d  \n",res,p,q);
		}
	}
return sqrt(res);
}








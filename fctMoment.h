#ifndef _fctMoment_h_
#define _fctMoment_h_


#include <stdlib.h>
#include <stdio.h>
#include "math.h"

/**
* ce fonction est pour calculer les moment geometirque 
* @para image limage a utiliser
* @para x
*	@para y
* @para p
*	@para q
* @returen un moment geometrique
*/
double momentGeo(double **image,int x, int y,int p, int q);

/**
* ce fonction est pour creer un tableau de 2 dimention
* @para x 
* @para y
* @return un tableau de 2 dimention
*/
double **creerTableau(int x, int y);

/**
* ce fonction est pour creer un tableau des moment geometirque 
* @para image limage a utiliser
* @para x
*	@para y
* @para n
* @returen un tableau des moment geometrique
*/
double **tabMomentGeo(double **image, int x, int y, int n);

/**
* ce fonction est pour calculer les moment translater et normalise 
* @para image limage a utiliser
* @para x
*	@para y
* @para p
*	@para q
* @returen un moment translater et invariant
*/
double momentIT(double **image,int x, int y,int p, int q);

/**
* ce fonction est pour creer un tableau des moment centre et norme 
* @para image limage a utiliser
* @para x
*	@para y
* @para n
* @returen un tableau des moment geometrique
*/
double **tabMomentIT(double **image, int x, int y, int n);

/**
* ce fonction est pour calculer les coefficient A(ni)
* @para k ordre
* @returen un tableau de coefficient
*/
double **tabCoeffA(int k);

/**
* ce fonction est pour supprimer un tableau
* @para adrees du tableau 
* @para length
*/
void freeTableau(double **Tab, int length);

/**
* ce fonction est pour calculer le moment legendre
* @para **tabMomentIT
* @para coeff A
* @para p
* @para q
* @returen un moment legendre
*/
double momentLeg(double **tabMIT , double **A, int p, int q);

/**
* ce fonction est pour creer un tableau des moment legendre 
* @para **tabMIT
* @para coeff A
* @para n
* @returen un tableau des moment 
*/
double **tabMomentLeg(double **tabMIT, double**A, int n);

/**
* ce fonction est pour calculer pn(x)
* @para **tabcoefA
*	@para x
* @para n
* @return Pn(x) 
*/
double calculPn (double **tabCoeffA, int n, double x);

/**
* ce fonction est pour calculer f(x,y)
* @para N
*	@para x
* @para y
* @para **tabMomentLeg
* @para **tabcoefA
return f(x,y)
*/
double calculRebuild(int N, double x, double y, double **tabMomentLeg, double **tabCoeffA);

/**
* ce fonction est pour calculer tab f(x,y)
* @para N
*	@para x
* @para y
* @para **tabMomentLeg
* @para **tabcoefA
return f(x,y)
*/
double** tabCalculRebuild(int N, int xMax, int yMax, double **tabMomentLeg, double **tabCoeffA);

/**
* ce fonction est pour calculer l'erreur
* @para N ordre
*	@para ** image
* @para **tabA
* @para xMax
* @para yMax
return erreur
*/
double errorRebuild (int N, double **image,double**tabA, int xMax, int yMax);

/**
* ce fonction est pour la distance
* @para **lambda1
* @para **lambda2
*	@para N
* @return distance 
*/
double distanceMoment(double **lambda1, double **lambda2,int N);

#endif

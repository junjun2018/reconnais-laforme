///*****auther*****//
///***yingjun HE***//
///******24/12/2017**********//

cette programme a un grand probleme avec myBmpCouleur.c car il ne sort pas un bon tableau valeur pixel...si votre image bmp n'est pas en 24 bits


il y a deux fichier pour essayer soit main.c , soit test.c
main.c il comparer l'image entree avec les images Base de donnee
test.c il vous montre que notre programme il a bien fait les calculs (reconstuiction)

attention pour entrer les noms de l'image , respecter la taille (ici c'est 11 caractere) par exemple B24bits.bmp


pour compile : gcc myBmpCouleur.c fctMoment.c -lm main.c -o main
ou : gcc myBmpCouleur.c fctMoment.c -lm test.c -o main

merci pour lire ce document.

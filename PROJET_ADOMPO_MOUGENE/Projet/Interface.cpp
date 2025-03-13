#include "Interface.h"

using namespace Geom2D;

// Definission de la taille de l'image
void tailleImage(int *hauteur, int *largeur, float *ratio_hauteur, float *ratio_largeur, int etat) {
	int ancienne_hauteur = *hauteur;
	int ancienne_largeur = *largeur;

	do {
		if (!(*largeur > 10 && *hauteur > 10)) {
			printf("Erreur avec les tailles saisies.\n");
		}
		printf("\nRentrez la largeur de l'image : ");
		scanf("%d", largeur);
		printf("Rentrez la hauteur de l'image : ");
		scanf("%d", hauteur);
	} 
	while (!(*largeur > 10 && *hauteur > 10));

	if (etat == 1) {
		ancienne_hauteur = *hauteur;
		ancienne_largeur = *largeur;
	}
	*ratio_hauteur = static_cast<float>(*hauteur) / static_cast<float>(ancienne_hauteur);
	*ratio_largeur = static_cast<float>(*largeur) / static_cast<float>(ancienne_largeur);
}

// Transforme la chaine de caracteres en majuscules
void transformationMaj(char *str) {
	for (int i = 0; str[i]!='\0'; i++) {
      if(str[i] >= 'a' && str[i] <= 'z') {
    	str[i] = static_cast<char>(str[i] - 32);
      }
   }
}

//Trouve le maximum entre deux valeurs
float max(float a, float b) {
    return (a > b) ? a : b;
}

void choixCouleur(Color *couleur) {
	char color[32] = "";
	int continuer = 0;
	do {
		printf("\nChoisissez la couleur:\n - Rouge\n - Blanc\n - Jaune\n - Orange\n - Turquoise\n - Violet\n - Rose\n - Vert\n - Gris\n - Cyan\n - Bleu\n - Marron\n - Noir\n - Vide\n\nVotre choix : ");
		scanf("%s", color);
		transformationMaj(color);
		continuer = 1;

		//Rouge
		if(strcmp("ROUGE", color) == 0) {
			*couleur=Color::red;
		}

		//Blanc
		else if(strcmp("BLANC", color) == 0) {
			*couleur=Color::white;
		}

		//Jaune
		else if(strcmp("JAUNE", color) == 0) {
			*couleur=Color::yellow;
		}

		//Orange
		else if(strcmp("ORANGE", color) == 0) {
			*couleur=Color::orange;
		}

		//Turquoise
		else if(strcmp("TURQUOISE", color) == 0) {
			*couleur=Color::turquoise;
		}

		//Violet
		else if(strcmp("VIOLET", color) == 0) {
			*couleur=Color::violet;
		}

		//Rose
		else if(strcmp("ROSE", color) == 0) {
			*couleur=Color::pink;
		}

		//Vert
		else if(strcmp("VERT", color) == 0) {
			*couleur=Color::green;
		}

		//Gris
		else if(strcmp("GRIS", color) == 0) {
			*couleur=Color::grey;
		}

		//Cyan
		else if(strcmp("CYAN", color) == 0) {
			*couleur=Color::cyan;
		}

		//Bleu
		else if(strcmp("BLEU", color) == 0) {
			*couleur=Color::blue;
		}

		//Marron
		else if(strcmp("MARRON", color) == 0) {
			*couleur=Color::brown;
		}

		//Noir
		else if(strcmp("NOIR", color) == 0) {
			*couleur=Color::black;
		}

		//Vide
		else if(strcmp("VIDE", color) == 0) {
			*couleur=Color::none;
		}

		//Erreur
		else {
			continuer = 0;
			printf("\n/!\\ Erreur, ceci n'est pas une couleur possible.\n");
		}

	} while (continuer == 0);
}

//Sauvegarde de la forme ajoutée
void sauvegardeForme(Figure* fig, Figure*** tab_fig, int* taille_tab) {
	fig->GrawEditor::Add(*fig, *(*tab_fig)[*taille_tab - 1]);

	(*taille_tab)++;
				
	// Allouer un nouveau tableau avec une case supplémentaire
	Figure** nouveau_tab_fig = new Figure*[*taille_tab];

	// Copier tous les éléments de l'ancien tableau dans le nouveau
	for (int i = 0; i < (*taille_tab - 1); i++) {
		nouveau_tab_fig[i] = (*tab_fig)[i];
	}

	// Ajouter la nouvelle forme au nouveau tableau
	nouveau_tab_fig[*taille_tab - 1] = fig;

	// Libérer la mémoire de l'ancien tableau
	delete[] *tab_fig;

	// Mettre à jour le pointeur vers le nouveau tableau
	*tab_fig = nouveau_tab_fig;
}


//Saisir les coordoonees du centre, avec verification par rapport a l'image
void choixCentre(float* x, float* y, int* hauteur, int* largeur) {
	int erreur = 0;
	do {
		if (erreur == 0) printf("\nRentrez la coordonnee x du centre : ");
		else printf("\nErreur, rentrez de nouveau la coordonnee x du centre : ");

		scanf("%f", x);
		erreur = 1;
	} while(*x <= 0.0 || *x >= (*largeur)*1.0);

	erreur = 0;

	do {
		if (erreur == 0) printf("\nRentrez la coordonnee y du centre : ");
		else printf("\nErreur, rentrez de nouveau la coordonnee y du centre : ");

		scanf("%f", y);
		erreur = 1;
	} while(*y <= 0.0 || *y >= (*hauteur)*1.0);
}

//Saisir les coordoonees du coin, avec verification du centre par rapport a l'image
void choixCoin(float* x, float* y, int* hauteur, int* largeur, float* longueur_x, float* longueur_y) {
	int erreur = 0;
	float milieu_x, milieu_y;

	do {
		if (erreur == 0) printf("\nRentrez la coordonnee x du coin superieur gauche : ");
		else printf("\nErreur, rentrez de nouveau la coordonnee x du coin superieur gauche : ");
		
		scanf("%f", x);
		milieu_x =  static_cast<float>((*x) + (*longueur_x)/2.0);
		erreur = 1;
	} while(milieu_x <= 0.0 || milieu_x >= (*largeur)*1.0);

	erreur = 0;

	do {
		if (erreur == 0) printf("\nRentrez la coordonnee y du coin superieur gauche : ");
		else printf("\nErreur, rentrez de nouveau la coordonnee y du coin superieur gauche : ");

		scanf("%f", y);
		milieu_y =  static_cast<float>((*y) + (*longueur_y)/2.0);
		erreur = 1;
	} while(milieu_y <= 0.0 || milieu_y >= (*hauteur)*1.0);
}

//Saisir la largeur, avec verification
void choixLargeur(float* largeur) {
	int erreur = 0;
	do {
		if (erreur == 0) {
			printf("\nRentrez la largeur de la forme : ");
		} else {
			printf("\nErreur avec la valeur saisie, rentrez de nouveau la largeur de la forme : ");
		}
		scanf("%f", largeur);
		erreur = 1;
	} while(*largeur <= 0.0);
}

//Saisir le rayon, avec verification
void choixRayon(float* rayon) {
	int erreur = 0;
	do {
		if (erreur == 0) {
			printf("\nRentrez le rayon de la forme : ");
		} else {
			printf("\nErreur avec la valeur saisie, rentrez de nouveau le rayon de la forme : ");
		}
		scanf("%f", rayon);
		erreur = 1;
	} while(*rayon <= 0.0);
}

//Saisir le rayon, avec verification
void choixRayon_(float* rayon_x, float* rayon_y) {
	int erreur = 0;
	do {
		if (erreur == 0) {
			printf("\nRentrez le rayon x de la forme : ");
		} else {
			printf("\nErreur avec la valeur saisie, rentrez de nouveau le rayon x de la forme : ");
		}
		scanf("%f", rayon_x);
		erreur = 1;
	} while(*rayon_x <= 0.0);

	erreur = 0;
	do {
		if (erreur == 0) {
			printf("\nRentrez le rayon y de la forme : ");
		} else {
			printf("\nErreur avec la valeur saisie, rentrez de nouveau le rayon y de la forme : ");
		}
		scanf("%f", rayon_y);
		erreur = 1;
	} while(*rayon_y <= 0.0);
}

//Saisir la longueur, avec verification
void choixLongueur(float* longueur) {
	int erreur = 0;
	do {
		if (erreur == 0) {
			printf("\nRentrez la longueur d'un cote de la forme : ");
		} else {
			printf("\nErreur avec la valeur saisie, rentrez de nouveau la longueur d'un cote de la forme : ");
		}
		scanf("%f", longueur);
		erreur = 1;
	} while(*longueur <= 0.0);
}

//Saisir l'angle, avec verification
void choixAngle(float* angle) {
	int erreur = 0;
	do {
		if (erreur == 0) {
			printf("\nRentrez l'angle de la forme (entre -90 et 90) : ");
		} else {
			printf("\nErreur avec la valeur saisie, rentrez de nouveau l'angle de la forme (entre -90 et 90) : ");
		}
		scanf("%f", angle);
		erreur = 1;
	} while(*angle <= -90.0f || *angle >= 90.0f );
}

//Saisir la hauteur, avec verification
void choixHauteur(float* hauteur) {
	int erreur = 0;
	do {
		if (erreur == 0) {
			printf("\nRentrez la hauteur de la forme : ");
		} else {
			printf("\nErreur avec la valeur saisie, rentrez de nouveau la hauteur de la forme : ");
		}
		scanf("%f", hauteur);
		erreur = 1;
	} while(*hauteur <= 0.0);
}

//Saisir l'epaisseur, avec verification
void choixEpaisseur(size_t* epaisseur) {
	int erreur = 0;
	int temp = 0;
	do {
		if (erreur == 0) {
			printf("\nRentrez l'epaisseur de la forme : ");
		} else {
			printf("\nErreur avec la valeur saisie, rentrez de nouveau l'epaisseur de la forme : ");
		}
		scanf("%d", &temp);
		erreur = 1;
	} while(temp <= 0);
	*epaisseur = static_cast<int>(temp);
}

//Saisir le nombre de points, avec verification
void choixNbPoints(int* nombre_points, int forme) {
	int erreur = 0;
	do {
		if (erreur == 0) {
			if (forme == 1) printf("\nRentrez le nombre de points du polygone (3 minimum) : ");
			else if (forme == 2) printf("\nRentrez le nombre de points de la polyligne (2 minimum) : ");
		} else {
			printf("\nErreur avec la valeur saisie, rentrez de nouveau le nombre de points de la forme (3 minimum) : ");
		}
		scanf("%u", nombre_points);
		erreur = 1;
	} while(*nombre_points < 3);
}

//Saisir les coordoonees d'un point, avec verification par rapport a l'image
void choixPoint(float* x, float* y, int* hauteur, int* largeur, int numero) {
	do {
		printf("\nRentrez la coordonnee x du point %d : ", numero);
		scanf("%f", x);
	} while(*x <= 0.0 || *x >= (*largeur)*1.0);

	do {
		printf("\nRentrez la coordonnee y du point %d : ", numero);
		scanf("%f", y);
	} while(*y <= 0.0 || *y >= (*hauteur)*1.0);
}

//Menu pour ajouter une forme dans la figure
void ajoutForme(Figure& fig, Figure** tab_fig, int* taille_tab, int* hauteur, int* largeur) {
	using namespace Geom2D;
	char selection[64] = "";
	Color couleur = Color::red;
	int continuer = 0;
	do {
		
		printf("Choisissez la forme :\n - Cercle\n - Ellipse\n - Carre\n - Rectangle\n - Triangle\n - Losange\n - Parallelogramme\n - Pentagone\n - Hexagone\n - Heptagone\n - Octogone\n - Disque\n - Ovale\n - Segment\n - Polyligne\n - RETOUR\n\nVotre choix : ");
		scanf("%s", selection);
		transformationMaj(selection);
		continuer = 1;

		//Cercle
		if(strcmp("CERCLE", selection) == 0) {
			choixCouleur(&couleur);

			float x, y, rayon;
			choixCentre(&x, &y, hauteur, largeur);
			choixRayon(&rayon);

			size_t epaisseur;
			choixEpaisseur(&epaisseur);

			tab_fig[*taille_tab - 1] = new Figure({ new Curve::Circle({ x,y }, rayon, couleur, epaisseur) });
		}

		//Ellipse
		else if(strcmp("ELLIPSE", selection) == 0) {
			choixCouleur(&couleur);

			float x, y, rayon_x, rayon_y;
			choixCentre(&x, &y, hauteur, largeur);
			choixRayon_(&rayon_x, &rayon_y);

			size_t epaisseur;
			choixEpaisseur(&epaisseur);

			tab_fig[*taille_tab - 1] = new Figure({ new Curve::Ellipse({ x,y }, rayon_x, rayon_y, couleur, epaisseur) });
		}

		//Carre
		else if(strcmp("CARRE", selection) == 0) {
			choixCouleur(&couleur);

			float x, y, longueur;
			choixLargeur(&longueur);
			choixCoin(&x, &y, hauteur, largeur, &longueur, &longueur);

			tab_fig[*taille_tab - 1] = new Figure({ new Surface::Square({ x,y }, longueur, couleur) });
		}

		//Rectangle
		else if(strcmp("RECTANGLE", selection) == 0) {
			choixCouleur(&couleur);

			float x, y, longueur_x, longueur_y;
			choixLargeur(&longueur_x);
			choixHauteur(&longueur_y);
			choixCoin(&x, &y, hauteur, largeur, &longueur_x, &longueur_y);

			tab_fig[*taille_tab - 1] = new Figure({ new Surface::Rectangle({ x,y }, longueur_x, longueur_y, couleur) });
		}

		//Triangle
		else if(strcmp("TRIANGLE", selection) == 0) {
			int erreur_triangle = 0;
			char selection_triangle[64] = "";
			do {
				if (erreur_triangle == 0) {
					printf("\nRentrez le type de triangle (EQUILATERAL ou PERSONNALISE) : ");
				} else {
					printf("\nErreur, rentrez de nouveau le type de triangle (EQUILATERAL ou PERSONNALISE) : ");
				}
				scanf("%s", selection_triangle);
				transformationMaj(selection_triangle);
				erreur_triangle = 1;

				if(strcmp("EQUILATERAL", selection_triangle) == 0) erreur_triangle = 0;
				else if (strcmp("PERSONNALISE", selection_triangle) == 0) erreur_triangle = 0;

			} while (erreur_triangle == 1);

			choixCouleur(&couleur);

			if(strcmp("EQUILATERAL", selection_triangle) == 0) {
				float x, y, longueur;
				choixCentre(&x, &y, hauteur, largeur);
				choixLongueur(&longueur);

				tab_fig[*taille_tab - 1] = new Figure({ new Surface::Triangle({ x,y }, longueur, couleur) });
			} else {
				float x,y;
				Point liste_points_triangle[3];

				for (int i = 1; i<4; i++) {
					printf("\nRentrez les coordonnes x du point n%d du triangle : ", i);
					scanf("%f", &x);
					printf("Rentrez les coordonnes y du point n%d du triangle : ", i);
					scanf("%f", &y);
					liste_points_triangle[i-1] = Point(x, y);
				}

				tab_fig[*taille_tab - 1] = new Figure({ new Surface::Triangle({liste_points_triangle[0], liste_points_triangle[1], liste_points_triangle[2]}, couleur) });
			}
		}

		//Losange
		else if(strcmp("LOSANGE", selection) == 0) {
			choixCouleur(&couleur);

			float x, y, longueur_x, longueur_y;
			choixCentre(&x, &y, hauteur, largeur);
			choixLargeur(&longueur_x);
			choixHauteur(&longueur_y);

			tab_fig[*taille_tab - 1] = new Figure({ new Surface::Losange({ x,y }, longueur_x, longueur_y, couleur) });
		}


		//Parallelogramme
		else if(strcmp("PARALLELOGRAMME", selection) == 0) {
			choixCouleur(&couleur);

			float x, y, longueur_x, longueur_y, angle;
			choixCentre(&x, &y, hauteur, largeur);
			choixLargeur(&longueur_x);
			choixHauteur(&longueur_y);
			choixAngle(&angle);

			tab_fig[*taille_tab - 1] = new Figure({ new Surface::Parallelogramme({ x,y }, longueur_x, longueur_y, angle, couleur) });
		
		}
		//Pentagone
		else if(strcmp("PENTAGONE", selection) == 0) {
			choixCouleur(&couleur);

			float x, y, longueur;
			choixCentre(&x, &y, hauteur, largeur);
			choixLongueur(&longueur);

			tab_fig[*taille_tab - 1] = new Figure({ new Surface::Pentagon({ x,y }, longueur, couleur) });
		}

		//Hexagone
		else if(strcmp("HEXAGONE", selection) == 0) {
			choixCouleur(&couleur);

			float x, y, longueur;
			choixCentre(&x, &y, hauteur, largeur);
			choixLongueur(&longueur);

			tab_fig[*taille_tab - 1] = new Figure({ new Surface::Hexagon({ x,y }, longueur, couleur) });
		}

		//Heptagone
		else if(strcmp("HEPTAGONE", selection) == 0) {
			choixCouleur(&couleur);

			float x, y, longueur;
			choixCentre(&x, &y, hauteur, largeur);
			choixLongueur(&longueur);

			tab_fig[*taille_tab - 1] = new Figure({ new Surface::Heptagon({ x,y }, longueur, couleur) });
		}

		//Octogone
		else if(strcmp("OCTOGONE", selection) == 0) {
			choixCouleur(&couleur);

			float x, y, longueur;
			choixCentre(&x, &y, hauteur, largeur);
			choixLongueur(&longueur);

			tab_fig[*taille_tab - 1] = new Figure({ new Surface::Octogon({ x,y }, longueur, couleur) });
		}

		//Polygone
		else if(strcmp("POLYGONE", selection) == 0) {
			choixCouleur(&couleur);

			int nombre_points;
			choixNbPoints(&nombre_points, 1);

			float x, y, longueur;
			choixCentre(&x, &y, hauteur, largeur);
			choixLongueur(&longueur);

			tab_fig[*taille_tab - 1] = new Figure({ new Surface::Polygon(nombre_points,{ x,y }, longueur, couleur) });
		}

		//Disque
		else if(strcmp("DISQUE", selection) == 0) {
			choixCouleur(&couleur);

			float x, y, rayon;
			choixCentre(&x, &y, hauteur, largeur);
			choixRayon(&rayon);

			tab_fig[*taille_tab - 1] = new Figure({ new Surface::Disk({ x,y }, rayon, couleur) });
		}

		//Ovale
		else if(strcmp("OVALE", selection) == 0) {
			choixCouleur(&couleur);

			float x, y, rayon_x, rayon_y;
			choixCentre(&x, &y, hauteur, largeur);
			choixRayon_(&rayon_x, &rayon_y);

			tab_fig[*taille_tab - 1] = new Figure({ new Surface::Oval({ x,y }, rayon_x, rayon_y, couleur) });
		}

		//Segment
		else if(strcmp("SEGMENT", selection) == 0) {
			choixCouleur(&couleur);

			float x1, y1, x2, y2;
			choixPoint(&x1, &y1, hauteur, largeur, 1);
			choixPoint(&x2, &y2, hauteur, largeur, 2);
			
			size_t epaisseur;
			choixEpaisseur(&epaisseur);

			tab_fig[*taille_tab - 1] = new Figure({ new Curve::Segment({ x1,y1 },{ x2,y2 }, couleur, epaisseur) });
		}

		//Polylignes
		else if(strcmp("POLYLIGNE", selection) == 0) {
			choixCouleur(&couleur);

			int nombre_points;
			choixNbPoints(&nombre_points, 2);

			float x, y, longueur;
			choixCentre(&x, &y, hauteur, largeur);
			choixLongueur(&longueur);
			
			size_t epaisseur;
			choixEpaisseur(&epaisseur);

			tab_fig[*taille_tab - 1] = new Figure({ new Curve::Polyline(nombre_points, { x,y }, longueur, couleur, epaisseur) });
		}

        		//Quitter le menu
		else if(strcmp("RETOUR", selection) == 0) {
			printf("\nRetour au menu principal.\n");
		}

		//Erreur
		else {
			printf("\n/!\\ Erreur, ceci n'est pas une forme possible.\n\n");
			continuer = 0;
		}

		if (continuer == 1) sauvegardeForme(&fig, &tab_fig, taille_tab);
		
	} while (continuer == 0);
}

void selectionForme(Figure& fig, int* hauteur, int* largeur, int* taille, int* tableau) {
	int continuer = 0;
	char selection[32] = "";

	*hauteur = *hauteur * 1;
	*largeur = *largeur * 1;

	do {
		
		printf("\nComment voulez-vous proceder?\n- INDICE (Choisir l'indice de la forme a modifier)\n- TYPE (Choisir le type de forme a modifier)\n\nVotre choix : ");
		scanf("%s", selection);
		transformationMaj(selection);
		continuer = 1;


		//Indice
		if(strcmp("INDICE", selection) == 0) {
			*taille = 1;

			int indice;
			int erreur = 0;

			if (fig.GetSize() == 0){
				printf("Il n'y a pas de forme dans le canva.\n");
			} else {

				printf("\nQuelle forme voulez-vous modifier :\n");
				for (int ind = 0; ind<22; ind++) fig.Print(fig, ind+1);

				do {
					if (erreur != 0) {
						printf("Erreur, l'indice doit être compris entre 0 et %d.\n", fig.GetSize());
					}
					printf("\nVotre choix (indice de la forme) : ");
					scanf("%d", &indice);
					erreur=1;
				} while(indice<0 || indice>=fig.GetSize());

				tableau[0] = indice;
			}
		}


		//Type
		else if (strcmp("TYPE", selection) == 0) {
			int type = selectionType(2);

			fig.Select(fig, type, tableau, taille);
			if (*taille == 0) {
				printf("\nIl n'y a pas de forme de ce type dans le canva.\n");
			} else if (*taille == 1) {
				printf("\nIl y a une forme de ce type dans le canva.\n");
			} else {
				printf("\nIl y a %d formes de ce type dans le canva.\n", *taille);
			}
		}


		//Erreur
		else {
			printf("\n/!\\ Erreur, ceci n'est pas une forme possible.\n\n");
			continuer = 0;
		}

	} while (continuer == 0);


}

void supprimerForme(Figure& fig, int* hauteur, int* largeur, int* taille, int* tableau) {
	int continuer = 0;
	char selection[32] = "";

	*hauteur = *hauteur * 1;
	*largeur = *largeur * 1;

	do {
		
		printf("Comment voulez-vous proceder?\n- INDICE (Choisir l'indice de la forme a supprimer)\n- TYPE (Choisir le type de forme a supprimer)\n\nVotre choix : ");
		scanf("%s", selection);
		transformationMaj(selection);
		continuer = 1;


		//Indice
		if(strcmp("INDICE", selection) == 0) {
			*taille = 1;

			int indice;
			int erreur = 0;

			if (fig.GetSize() == 0){
				printf("Il n'y a pas de forme dans le canva.\n");
			} else {

				printf("\nQuelle forme voulez-vous supprimer :\n");
				for (int ind = 0; ind<22; ind++) fig.Print(fig, ind+1);

				do {
					if (erreur != 0) {
						printf("Erreur, l'indice doit être compris entre 0 et %d.\n", fig.GetSize());
					}
					printf("\nVotre choix (indice de la forme) : ");
					scanf("%d", &indice);
					erreur=1;
				} while(indice<0 || indice>=fig.GetSize());

				tableau[0] = indice;
			}
		}

        //Type
		else if (strcmp("TYPE", selection) == 0) {
			int type = selectionType(3);

			fig.Select(fig, type, tableau, taille);
			if (*taille == 0) {
				printf("\nIl n'y a pas de forme de ce type dans le canva.\n");
			} else if (*taille == 1) {
				printf("\nIl y a une forme de ce type dans le canva.\n");
			} else {
				printf("\nIl y a %d formes de ce type dans le canva.\n", *taille);
			}
		}


		//Erreur
		else {
			printf("\n/!\\ Erreur, ceci n'est pas une forme possible.\n\n");
			continuer = 0;
		}

	} while (continuer == 0);


}

int selectionType(int etat) {
	int type = 0;
	int continuer = 0;
	char selection[32] = "";

	do {
		
		if (etat == 1) {
			printf("\nChoisissez le type de forme a enregistrer :\n - TOUTES les formes\n - Cercle\n - Ellipse\n - Carre\n - Rectangle\n - Triangle\n - Losange\n - Parallelogramme\n - Pentagone\n - Hexagone\n - Heptagone\n - Octogone\n - Disque\n - Ovale\n - Segment\n - Polyligne\n\nVotre choix : ");
		} else if (etat == 2) {
			printf("\nChoisissez le type de forme a modifier :\n - TOUTES les formes\n - Cercle\n - Ellipse\n - Carre\n - Rectangle\n - Triangle\n - Losange\n - Parallelogramme\n - Pentagone\n - Hexagone\n - Heptagone\n - Octogone\n - Disque\n - Ovale\n - Segment\n - Polyligne\n\nVotre choix : ");
		} else {
			printf("\nChoisissez le type de forme a supprimer :\n - TOUTES les formes\n - Cercle\n - Ellipse\n - Carre\n - Rectangle\n - Triangle\n - Losange\n - Parallelogramme\n - Pentagone\n - Hexagone\n - Heptagone\n - Octogone\n - Disque\n - Ovale\n - Segment\n - Polyligne\n\nVotre choix : ");
		}

		scanf("%s", selection);
		transformationMaj(selection);
		continuer = 1;

		//Toutes les formes
		if(strcmp("TOUTES", selection) == 0) {
			type = 0;
		}

		//Cercle
		else if(strcmp("CERCLE", selection) == 0) {
			type = 1;
		}

		//Ellipse
		else if(strcmp("ELLIPSE", selection) == 0) {
			type = 2;
		}

		//Carre
		else if(strcmp("CARRE", selection) == 0) {
			type = 14;
		}

		//Rectangle
		else if(strcmp("RECTANGLE", selection) == 0) {
			type = 13;
		}

		//Triangle
		else if(strcmp("TRIANGLE", selection) == 0) {
			type = 8;
		}

		//Losange
		else if(strcmp("LOSANGE", selection) == 0) {
			type = 15;
		}


		//Parallelogramme
		else if(strcmp("PARALLELOGRAMME", selection) == 0) {
			type = 16;
		
		}
		//Pentagone
		else if(strcmp("PENTAGONE", selection) == 0) {
			type = 9;
		}

		//Hexagone
		else if(strcmp("HEXAGONE", selection) == 0) {
			type = 10;
		}

		//Heptagone
		else if(strcmp("HEPTAGONE", selection) == 0) {
			type = 11;
		}

		//Octogone
		else if(strcmp("OCTOGONE", selection) == 0) {
			type = 12;
		}

		//Polygone
		else if(strcmp("POLYGONE", selection) == 0) {
			type = 7;
		}

		//Disque
		else if(strcmp("DISQUE", selection) == 0) {
			type = 5;
		}

		//Ovale
		else if(strcmp("OVALE", selection) == 0) {
			type = 6;
		}

		//Segment
		else if(strcmp("SEGMENT", selection) == 0) {
			type = 4;
		}

		//Polylignes
		else if(strcmp("POLYLIGNE", selection) == 0) {
			type = 3;

		}

		//Erreur
		else {
			printf("\n/!\\ Erreur, ceci n'est pas une forme possible.\n\n");
			continuer = 0;
		}
		
	} while (continuer == 0);

	return type;
}

void modifierForme(Figure& fig, int* hauteur, int* largeur) {
	int continuer = 0;
	char selection[32] = "";

	int taille = 0;
	int* tableau = new int[fig.GetSize()]();

	do {
		
		printf("Quelle type de modification voulez-vous effectuer?\n- Rotation\n- Translation\n- Redimension\n- Recoloration\n- Annuler la modification\n\nVotre choix : ");
		scanf("%s", selection);
		transformationMaj(selection);
		continuer = 1;


		//Rotation
		if(strcmp("ROTATION", selection) == 0) {
			selectionForme(fig, hauteur, largeur, &taille, tableau);

			float angle = 0.0;
			int erreur = 0;

			if (taille > 0) {
				do  {
					if (erreur == 0) {
						printf("\nEntrez l'angle de la rotation : ");
					} else {
						printf("Erreur, entrez de nouveau l'angle de la rotation : ");
					}

					scanf("%f", &angle);
					erreur = 1;

				} while (angle<=0.0);

				for (int i = 0; i < taille; i++) {
					fig.Rotate_(angle ,tableau[i]);
				}
			}
		}


		//Translation
		else if (strcmp("TRANSLATION", selection) == 0) {
			selectionForme(fig, hauteur, largeur, &taille, tableau);

			float x = 0.0, y = 0.0;
			int erreur = 0;

			if (taille > 0) {

				do  {
					if (erreur == 0) {
						printf("\nEntrez la coordonnee x pour la translation : ");
					} else {
						printf("Erreur, entrez de nouveau la coordonnee x pour la translation : ");
					}

					scanf("%f", &x);
					erreur = 1;

				} while (x <= 0.0);

				erreur = 0;

				do  {
					if (erreur == 0) {
						printf("\nEntrez la coordonnee y pour la translation : ");
					} else {
						printf("Erreur, entrez de nouveau la coordonnee y pour la translation : ");
					}

					scanf("%f", &y);
					erreur = 1;

				} while (y <= 0.0);

				for (int i = 0; i < taille; i++) {
					fig.Translate_(Geom2D::Point{x,y} ,tableau[i]);
				}
			}
		}


		//Redimension
		else if (strcmp("REDIMENSION", selection) == 0) {
			selectionForme(fig, hauteur, largeur, &taille, tableau);

			float ratio = 0.0;
			int erreur = 0;

			if (taille > 0) {

				do  {
					if (erreur == 0) {
						printf("\nEntrez le ratio de la redimension : ");
					} else {
						printf("Erreur, entrez de nouveau le ratio de la redimension : ");
					}

					scanf("%f", &ratio);
					erreur = 1;

				} while (ratio<=0.0);

				for (int i = 0; i < taille; i++) {
					fig.Scale_(ratio ,tableau[i]);
				}
			}
		}


		//Recoloration
		else if (strcmp("RECOLORATION", selection) == 0) {
			selectionForme(fig, hauteur, largeur, &taille, tableau);

			if (taille > 0) {
			
				Color couleur = Color::red;
				choixCouleur(&couleur);

				for (int i = 0; i < taille; i++) {
					fig.Recolor_(couleur, tableau[i]);
				}
			}
		}


		//Quitter le menu
		else if(strcmp("ANNULER", selection) == 0) {
			printf("\nRetour au menu principal.\n");
		}


		//Erreur
		else {
			printf("\n/!\\ Erreur, ceci n'est pas une forme possible.\n\n");
			continuer = 0;
		}

	} while (continuer == 0);

	delete[]tableau;

}

//Menu principal de l'editeur
void menuPrincipal(Figure& fig, char* nom_du_fichier, int *hauteur, int *largeur, float *ratio_hauteur, float *ratio_largeur, Figure** tab_fig, int *taille_tab_fig) {

	//Menu d'edition
	char action[64] = "";
	int annulations = 0;
	int refaire = 0;
	int etat_while = 0;
	int choix = 0;

	do {
		
		if(etat_while == 0) {

			//Editer une/des forme(s)
			if (choix == 1) {
				choix = 0;
				printf("Que voulez vous faire?\n- AJOUTER une forme\n- MODIFIER une forme\n- SUPPRIMER une forme\n- RETOUR\n\nVotre choix : ");
				scanf("%s", action);
				transformationMaj(action);
				printf("\n");


				//Ajouter une forme
				if(strcmp("AJOUTER", action) == 0) {
					ajoutForme(fig, tab_fig, taille_tab_fig, largeur, hauteur);
				}


				//Modifier une forme
				else if(strcmp("MODIFIER", action) == 0) {

					if (fig.GetSize() == 0){
						printf("Il n'y a pas de forme dans le canva.\n");
					} else {
						modifierForme(fig, largeur, hauteur);
					}
				}


				//Supprimer une forme
				else if(strcmp("SUPPRIMER", action) == 0) {

					if (fig.GetSize() == 0){
						printf("Il n'y a pas de forme dans le canva.\n");
					} else {

						int taille = 0;
						int* tableau = new int[fig.GetSize()]();
						int decalage = 0;
						
						supprimerForme(fig, hauteur, largeur, &taille, tableau);

						if (taille > 0) {

							for (int i = 0; i < taille; i++) {
								fig.Delete(fig ,tableau[i]-decalage);
								decalage++;
							}
						}
					}
				}


				//Annuler
				else if(strcmp("RETOUR", action) == 0) {
					printf("Retour au menu principal\n");
				}

				
				//Erreur
				else {
					printf("/!\\ Erreur, ceci n'est pas une action possible.\n");
				}

				etat_while = 1;

				if(strcmp("RETOUR", action) == 0) {
					etat_while = 0;
				}


			//MODIFIER l'image
			} else if (choix == 2) {
				choix = 0;
				printf("\nQue voulez vous faire?\n- REDIMENSIONNER l'image\n- ROGNER l'image\n- REINITIALISER le canva\n- RENOMMER le fichier\n- ANNULER des operations\n- REFAIRE des operations\n- RETOUR\n\nVotre choix : ");
				scanf("%s", action);
				transformationMaj(action);
				printf("\n");


				//Redimensionner l'image
				if(strcmp("REDIMENSIONNER", action) == 0) {
					tailleImage(hauteur, largeur, ratio_hauteur, ratio_largeur, 0);
					fig.Resize(fig, max(*ratio_hauteur, *ratio_largeur));
				}


				//Rogner l'image
				else if(strcmp("ROGNER", action) == 0) {
					tailleImage(hauteur, largeur, ratio_hauteur, ratio_largeur, 0);
					fig.Crop(fig, *hauteur, *largeur);
				}


				//Rogner l'image
				else if(strcmp("REINITIALISER", action) == 0) {
					if (fig.GetSize() == 0){
						printf("Il n'y a pas de forme dans le canva.\n");
					} else {

						char confirmation[32] = "";
						do {
							printf("Confirmer (OUI / NON) la reinitialisation : ");
							scanf("%s", confirmation);
							transformationMaj(confirmation);
						} while( (strcmp("OUI", confirmation) != 0) &&  (strcmp("NON", confirmation) != 0));

						if ((strcmp("OUI", confirmation) == 0)) {
							for (int i = 0; i<fig.GetSize(); i++) {
								fig.Delete(fig, i);
								*taille_tab_fig = 1;
							}
						}
					}
				}


				//Annuler des opérations
				else if(strcmp("RENOMMER", action) == 0) {
					printf("Choisir le nouveau nom du fichier : ");
					scanf("%s", nom_du_fichier);

					//Ajout automatique de l'extension ".html" s'il n'y a pas d'extension html ou svg
					int len_nouveau_nom = static_cast<int>(strlen(nom_du_fichier));
					if (strcmp(nom_du_fichier + len_nouveau_nom - 5, ".html") != 0 && strcmp(nom_du_fichier + len_nouveau_nom - 4, ".svg") != 0) {
						strcat(nom_du_fichier, ".html");
					}
				}


				//Annuler des opérations
				else if(strcmp("ANNULER", action) == 0) {
					printf("Combien d'etapes voulez-vous annuler? : ");
					scanf("%d", &annulations);

					printf("\nFonction bientot disponible.");
				}


				//Refaire des opérations
				else if(strcmp("REFAIRE", action) == 0) {
					printf("Combien d'etapes voulez-vous refaire? : ");
					scanf("%d", &refaire);
				}
				

				//Quitter le menu
				else if(strcmp("RETOUR", action) == 0) {
					printf("Retour au menu principal.\n");
				}


				//Erreur
				else {
					printf("/!\\ Erreur, ceci n'est pas une action possible.\n");
				}

				etat_while = 1;

				if(strcmp("RETOUR", action) == 0) {
					etat_while=0;
				}
			}

			else {
				
				printf("\nQue voulez vous faire?\n- EDITER une/des forme(s)\n- MODIFIER l'image\n- INFORMATIONS du fichier\n- ENREGISTRER certaines formes\n- QUITTER le programme\n\nVotre choix : ");
				scanf("%s", action);
				transformationMaj(action);
				printf("\n");

				//Modifier l'image
				if(strcmp("EDITER", action) == 0) {
					etat_while = 0;
					choix = 1;
				}

				//Modifier l'image
				else if(strcmp("MODIFIER", action) == 0) {
					etat_while = 0;
					choix = 2;
				}


				//Informations du fichier
				else if(strcmp("INFORMATIONS", action) == 0) {
					etat_while = 1;
					printf("Fichier : %s.\n\n", nom_du_fichier);
					printf("Taille : %d par %d.\n\n", *largeur, *hauteur);
					if (fig.GetSize() == 0){
						printf("Il n'y a pas de forme dans le canva.\n");
					} else {
						printf("Il y a %d formes :\n", fig.GetSize());
						for (int ind = 0; ind<22; ind++) fig.Print(fig, ind+1);
					}
				}


				//Enregistrer le fichier
				else if(strcmp("ENREGISTRER", action) == 0) {
					etat_while = 1;

					int type = 0;
					type = selectionType(1);

					int nombre = 0;
					fig.VerificationType(type, &nombre);

					if (nombre == 0) {
						printf("\nIl n'y a pas ce type de forme dans le canva. Enregistrement annule.\n");
					} else {
						printf("\nEnregistrement du fichier en cours (%d formes).\n", nombre);
						fig.ExportSVG(fig, nom_du_fichier, *hauteur, *largeur, type);
					}
				}


				//Quitter le programme
				else if(strcmp("QUITTER", action) == 0) {
					etat_while = 1;
					printf("\nFin de l'edition.\n");
				}


				//Erreur
				else {
					etat_while = 1;
					printf("/!\\ Erreur, ceci n'est pas une action possible.\n");
				}
			}


		//Apres un choix dans le menu d'edition
		} else {
			printf("\nQue vous voulez faire?\n- CONTINUER l'edition\n- ENREGISTRER le fichier et continuer l'edition\n- QUITTER le programme\n\nVotre choix : ");
			scanf("%s", action);
			transformationMaj(action);
			

			//Continuer le programme
			if(strcmp("CONTINUER", action) == 0) {
				etat_while = 0;
			}


			//Enregistrer le fichier
			else if(strcmp("ENREGISTRER", action) == 0) {
				printf("\nEnregistrement du fichier (toutes les formes).\n");
				fig.ExportSVG(fig, nom_du_fichier, *hauteur, *largeur, 0);
				etat_while = 0;
			}

			
			//Quitter le programme
			else if(strcmp("QUITTER", action) == 0) {
				etat_while = 1;
				printf("Fin de l'edition.\n");
			}


			//Erreur
			else {
				etat_while = 1;
				printf("\n/!\\ Erreur, ceci n'est pas une action possible.\n");
			}

		}

	} while (strcmp("QUITTER", action) != 0);

}
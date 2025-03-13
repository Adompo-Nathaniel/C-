#ifndef _GRAWINK_H_
#define _GRAWINK_H_

class GrawEditor {
  public:

    enum class ShapeType: uint64_t {
      Stroke    = 1ULL << 0,  // = 0000 0001 = 0x01 =   1
      Triangle  = 1ULL << 1,  // = 0000 0010 = 0x02 =   2
      Rectangle = 1ULL << 2,  // = 0000 0100 = 0x04 =   4
      Pentagon  = 1ULL << 3,  // = 0000 1000 = 0x08 =   8
      Hexagon   = 1ULL << 4,  // = 0001 0000 = 0x10 =  16
      Heptagon  = 1ULL << 5,  // = 0010 0000 = 0x20 =  32
      Octogon   = 1ULL << 6,  // = 0100 0000 = 0x40 =  64
      Ellipsis  = 1ULL << 7,  // = 1000 0000 = 0x80 = 128
      All       = ~0ULL       // = 111...111 = 0xff...ff = (2^64)-1
    };

    static GrawEditor& GetEditor( /* à vous de définir les paramètres */ );

    // Ajoute un nouveau objet au canevas
    GrawEditor& Add(Figure& figure, Figure& temp);

    // Supprime un objet du canevas
    GrawEditor& Delete(Figure& figure, int indice);

    // Annule le dernier ajout d'objet
    GrawEditor& Undo( /* à vous de définir les paramètres */ );

    // Réinsère le dernier objet supprimé
    GrawEditor& Redo( /* à vous de définir les paramètres */ );

    // Redimensionne le canevas
    GrawEditor& Resize(Figure& figure, float ratio);

    // Redimensionne le canevas en supprimant les objets extérieurs */
    GrawEditor& Crop(Figure& figure, int hauteur, int largeur);

    // Sélectionne les objets à exporter/afficher.
    GrawEditor& Select(Figure& figure, int type, int* tab_indice, int* taille_tab_indice);

    // Affiche l'ensemble des objets contenus dans le canevas, triés par
    // catégorie, dans la sortie standard.
    GrawEditor& Print(Figure& figure, int type);

    // Écrit le code SVG résultant des objets contenus dans le canevas
		GrawEditor& ExportSVG(Figure& fig, const char *fname, int hauteur, int largeur, int type);

    // Crée une nouvelle instance de la classe `Shape` (i.e. Rectangle,
    // Triangle, Stroke, Circle, etc.) et retourne un pointeur vers l'objet nouvellement alloué.
    // Cet objet peut ensuite être transformé, passé en paramètre à `Add` ou à `Delete`.
    template <typename Shape> Shape *GetNew( /* à vous de définir les paramètres */ );
};

#endif /* _GRAWINK_H_ */

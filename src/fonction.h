/*#ifndef FONCTIONS_H_
#define FONCTIONS_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>*/
#include <gtk/gtk.h>

typedef struct
{
    int jour;
    int mois;
    int annee;
} date;
typedef struct
{
    char identifiant[20];
    float poids;
    char type[20];
    int sexe; //1:male // 0:femalle
    int race; //1:pure // 0:hybride
    date date_naissance;
} troupeaux;

void ajout_troupeaux(troupeaux t);
void afficher_troupeaux(GtkWidget *treeview1);
void supprimer_troupeaux(char *identifiant);
void modifer_troupeaux(char *identifiant, troupeaux t2);
void cherche_id(char *identifiant, troupeaux *t);
int nombrestroupeaux(char *type);
void trfiltre(GtkWidget *treeview1, char *id);


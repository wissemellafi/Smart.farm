#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonction.h"
#include <gtk/gtk.h>
///////////////////////////////////////////////
void ajout_troupeaux(troupeaux t)
{
        FILE *f = NULL;
        f = fopen("troupeaux.txt", "a");
        if (f != NULL)
        {
                fprintf(f, "%s %f %s %d %d %d %d %d\n", t.identifiant, t.poids, t.type, t.sexe, t.race, t.date_naissance.jour, t.date_naissance.mois, t.date_naissance.annee);
                fclose(f);
        }
}
///////////////////////////////////////////////
void afficher_troupeaux(GtkWidget *treeview1)
{
        enum
        {
                identifiant_t,
                poid_t,
                type_t,
                sexe_t,
                race_t,
                jour_t,
                mois_t,
                annee_t,
                columns
        };

        GtkCellRenderer *renderer;
        GtkTreeViewColumn *column;
        GtkTreeIter iter;
        GtkListStore *store;

        char identifiant[20];
        char poid[20];
        char type[20];
        char sexe[20];
        char race[20];
        char jour[20];
        char mois[20];
        char annee[20];
        FILE *f;
        troupeaux t;
        f = fopen("troupeaux.txt", "a+");

        store = NULL;
        store = gtk_tree_view_get_model(treeview1);
        if (store == NULL)
        {

                renderer = gtk_cell_renderer_text_new();
                column = gtk_tree_view_column_new_with_attributes("identifiant", renderer, "text", identifiant_t, NULL);
                gtk_tree_view_append_column(GTK_TREE_VIEW(treeview1), column);

                renderer = gtk_cell_renderer_text_new();
                column = gtk_tree_view_column_new_with_attributes("poid", renderer, "text", poid_t, NULL);
                gtk_tree_view_append_column(GTK_TREE_VIEW(treeview1), column);

                renderer = gtk_cell_renderer_text_new();
                column = gtk_tree_view_column_new_with_attributes("type", renderer, "text", type_t, NULL);
                gtk_tree_view_append_column(GTK_TREE_VIEW(treeview1), column);

                renderer = gtk_cell_renderer_text_new();
                column = gtk_tree_view_column_new_with_attributes("sexe", renderer, "text", sexe_t, NULL);
                gtk_tree_view_append_column(GTK_TREE_VIEW(treeview1), column);

                renderer = gtk_cell_renderer_text_new();
                column = gtk_tree_view_column_new_with_attributes("race", renderer, "text", race_t, NULL);
                gtk_tree_view_append_column(GTK_TREE_VIEW(treeview1), column);

                renderer = gtk_cell_renderer_text_new();
                column = gtk_tree_view_column_new_with_attributes("jour", renderer, "text", jour_t, NULL);
                gtk_tree_view_append_column(GTK_TREE_VIEW(treeview1), column);

                renderer = gtk_cell_renderer_text_new();
                column = gtk_tree_view_column_new_with_attributes("mois", renderer, "text", mois_t, NULL);
                gtk_tree_view_append_column(GTK_TREE_VIEW(treeview1), column);

                renderer = gtk_cell_renderer_text_new();
                column = gtk_tree_view_column_new_with_attributes("annee", renderer, "text", annee_t, NULL);
                gtk_tree_view_append_column(GTK_TREE_VIEW(treeview1), column);

                store = gtk_list_store_new(columns, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

                f = fopen("troupeaux.txt", "r");

                if (f == NULL)
                {
                        return;
                }
                else
                {
                        while ((fscanf(f, "%s %f %s %d %d %d %d %d\n", &t.identifiant, &t.poids, t.type, &t.sexe, &t.race, &t.date_naissance.jour, &t.date_naissance.mois, &t.date_naissance.annee) != EOF))
                        {
                                if (t.sexe == 1)
                                        strcpy(sexe, "Male");
                                else
                                        strcpy(sexe, "Femelle");
                                if (t.race == 1)
                                        strcpy(race, "Pure");
                                else
                                        strcpy(race, "Hybride");
                                strcpy(type, t.type);
                                strcpy(identifiant, t.identifiant);

                                sprintf(poid, "%f", t.poids);
                                sprintf(jour, "%d", t.date_naissance.jour);
                                sprintf(mois, "%d", t.date_naissance.mois);
                                sprintf(annee, "%d", t.date_naissance.annee);
                                gtk_list_store_append(store, &iter);
                                gtk_list_store_set(store, &iter, identifiant_t, identifiant, poid_t, poid, type_t, type, sexe_t, sexe, race_t, race, jour_t, jour, mois_t, mois, annee_t, annee, -1);
                        }
                        fclose(f);
                }
                gtk_tree_view_set_model(GTK_TREE_VIEW(treeview1), GTK_TREE_MODEL(store));
                g_object_unref(store);
        }
}
//////////////////////////////////////////////
void supprimer_troupeaux(char *identifiant)
{
        FILE *f = NULL;
        FILE *tmp = NULL;
        troupeaux t1;
        f = fopen("troupeaux.txt", "r");
        tmp = fopen("tmp.txt", "w");
        if (f != NULL)
        {
                while (fscanf(f, "%s %f %s %d %d %d %d %d\n", t1.identifiant, &t1.poids, t1.type, &t1.sexe, &t1.race, &t1.date_naissance.jour, &t1.date_naissance.mois, &t1.date_naissance.annee) != EOF)
                {
                        if (strcmp(t1.identifiant, identifiant) != 0)
                        {
                                fprintf(tmp, "%s %f %s %d %d %d %d %d\n", t1.identifiant, t1.poids, t1.type, t1.sexe, t1.race, t1.date_naissance.jour, t1.date_naissance.mois, t1.date_naissance.annee);
                        }
                }
                fclose(f);
                fclose(tmp);
                remove("troupeaux.txt");
                rename("tmp.txt", "troupeaux.txt");
        }
}
//////////////////////////////////////////////
void modifer_troupeaux(char *identifiant, troupeaux t2)
{
        supprimer_troupeaux(identifiant);
        ajout_troupeaux(t2);
}
//////////////////////////////////////////////
void cherche_id(char *identifiant, troupeaux *t)
{
        FILE *f = NULL;
        troupeaux t1;
        int teste;
        f = fopen("troupeaux.txt", "r");
        teste = 0;
        if (f != NULL)
        {
                while (fscanf(f, "%s %f %s %d %d %d %d %d\n", t1.identifiant, &t1.poids, t1.type, &t1.sexe, &t1.race, &t1.date_naissance.jour, &t1.date_naissance.mois, &t1.date_naissance.annee) != EOF)
                {
                        if (strcmp(t1.identifiant, identifiant) == 0)
                        {
                                strcpy(t->identifiant, t1.identifiant);
                                t->poids = t1.poids;
                                strcpy(t->type, t1.type);
                                t->sexe = t1.sexe;
                                t->race = t1.race;
                                t->date_naissance.jour = t1.date_naissance.jour;
                                t->date_naissance.mois = t1.date_naissance.mois;
                                t->date_naissance.annee = t1.date_naissance.annee;

                                break;
                        }
                }
                fclose(f);
        }
}
///////////////////////////////////////////////
int nombrestroupeaux(char *type)
{
        troupeaux t1;
        FILE *f;
        int i = 0;
        f = fopen("troupeaux.txt", "r");
        if (f != NULL)

        {
                while (fscanf(f, "%s %f %s %d %d %d %d %d\n", t1.identifiant, &t1.poids, t1.type, &t1.sexe, &t1.race, &t1.date_naissance.jour, &t1.date_naissance.mois, &t1.date_naissance.annee) != EOF)
                {
                        if (!strcmp(t1.type, type))
                        {
                                i = i + 1;
                        }
                }
        }
        fclose(f);
        return (i);
}
////////////////////////////////////////////////

void trfiltre(GtkWidget *treeview1, char *id)
{
        enum
        {
                identifiant_t,
                poid_t,
                type_t,
                sexe_t,
                race_t,
                jour_t,
                mois_t,
                annee_t,
                columns
        };

        GtkCellRenderer *renderer;
        GtkTreeViewColumn *column;
        GtkTreeIter iter;
        GtkListStore *store;

        char identifiant[20];
        char poid[20];
        char type[20];
        char sexe[20];
        char race[20];
        char jour[20];
        char mois[20];
        char annee[20];
        FILE *f;
        troupeaux t;
        f = fopen("troupeaux.txt", "a+");

        store = NULL;
        store = gtk_tree_view_get_model(treeview1);
        if (store == NULL)
        {

                renderer = gtk_cell_renderer_text_new();
                column = gtk_tree_view_column_new_with_attributes("identifiant", renderer, "text", identifiant_t, NULL);
                gtk_tree_view_append_column(GTK_TREE_VIEW(treeview1), column);

                renderer = gtk_cell_renderer_text_new();
                column = gtk_tree_view_column_new_with_attributes("poid", renderer, "text", poid_t, NULL);
                gtk_tree_view_append_column(GTK_TREE_VIEW(treeview1), column);

                renderer = gtk_cell_renderer_text_new();
                column = gtk_tree_view_column_new_with_attributes("type", renderer, "text", type_t, NULL);
                gtk_tree_view_append_column(GTK_TREE_VIEW(treeview1), column);

                renderer = gtk_cell_renderer_text_new();
                column = gtk_tree_view_column_new_with_attributes("sexe", renderer, "text", sexe_t, NULL);
                gtk_tree_view_append_column(GTK_TREE_VIEW(treeview1), column);

                renderer = gtk_cell_renderer_text_new();
                column = gtk_tree_view_column_new_with_attributes("race", renderer, "text", race_t, NULL);
                gtk_tree_view_append_column(GTK_TREE_VIEW(treeview1), column);

                renderer = gtk_cell_renderer_text_new();
                column = gtk_tree_view_column_new_with_attributes("jour", renderer, "text", jour_t, NULL);
                gtk_tree_view_append_column(GTK_TREE_VIEW(treeview1), column);

                renderer = gtk_cell_renderer_text_new();
                column = gtk_tree_view_column_new_with_attributes("mois", renderer, "text", mois_t, NULL);
                gtk_tree_view_append_column(GTK_TREE_VIEW(treeview1), column);

                renderer = gtk_cell_renderer_text_new();
                column = gtk_tree_view_column_new_with_attributes("annee", renderer, "text", annee_t, NULL);
                gtk_tree_view_append_column(GTK_TREE_VIEW(treeview1), column);

                store = gtk_list_store_new(columns, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

                f = fopen("troupeaux.txt", "r");

                if (f == NULL)
                {
                        return;
                }
                else
                {
                        while ((fscanf(f, "%s %f %s %d %d %d %d %d\n", t.identifiant, &t.poids, t.type, &t.sexe, &t.race, &t.date_naissance.jour, &t.date_naissance.mois, &t.date_naissance.annee) != EOF))

                        {
                                if (strcmp(t.identifiant, id) == 0)
                                {
                                        if (t.sexe == 1)
                                                strcpy(sexe, "Male");
                                        else
                                                strcpy(sexe, "Femelle");
                                        if (t.race == 1)
                                                strcpy(race, "Pure");
                                        else
                                                strcpy(race, "Hybride");
                                        strcpy(type, t.type);
                                        strcpy(identifiant, t.identifiant);

                                        sprintf(poid, "%f", t.poids);
                                        sprintf(jour, "%d", t.date_naissance.jour);
                                        sprintf(mois, "%d", t.date_naissance.mois);
                                        sprintf(annee, "%d", t.date_naissance.annee);
                                        gtk_list_store_append(store, &iter);
                                        gtk_list_store_set(store, &iter, identifiant_t, identifiant, poid_t, poid, type_t, type, sexe_t, sexe, race_t, race, jour_t, jour, mois_t, mois, annee_t, annee, -1);
                                }
                        }
                        fclose(f);
                }
                gtk_tree_view_set_model(GTK_TREE_VIEW(treeview1), GTK_TREE_MODEL(store));
                g_object_unref(store);
        }
}

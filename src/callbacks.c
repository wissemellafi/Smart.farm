#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "fonction.h"
#include <stdio.h>

void on_trajaj_clicked(GtkWidget *objet_graphique,
                       gpointer user_data)
{

  GtkWidget *ajouttroupeaux;
  troupeaux t;
  GtkWidget *idtf, *poid, *type, *jour, *mois, *annee, *race, *sexe;
  GtkWidget *obidentifiant, *obtype, *obsexe, *obpoid, *obrace;

  jour = lookup_widget(objet_graphique, "trjour");
  mois = lookup_widget(objet_graphique, "trmois");
  annee = lookup_widget(objet_graphique, "trannee");
  idtf = lookup_widget(objet_graphique, "tridentifiant");
  sexe = lookup_widget(objet_graphique, "trsexe");
  poid = lookup_widget(objet_graphique, "trpoid");
  race = lookup_widget(objet_graphique, "trrace");
  type = lookup_widget(objet_graphique, "trtype");

  obidentifiant = lookup_widget(objet_graphique, "obidentifiant");
  obtype = lookup_widget(objet_graphique, "obtype");
  obsexe = lookup_widget(objet_graphique, "obsexe");
  obrace = lookup_widget(objet_graphique, "obrace");
  obsexe = lookup_widget(objet_graphique, "obsexe");

  if ((strcmp(gtk_entry_get_text(GTK_ENTRY(idtf)), "") != 0) && (strcmp(gtk_entry_get_text(GTK_ENTRY(type)), "") != 0) && (strcmp(gtk_entry_get_text(GTK_ENTRY(poid)), "") != 0) && (gtk_combo_box_get_active(GTK_COMBO_BOX(race)) != -1) && (gtk_combo_box_get_active(GTK_COMBO_BOX(sexe)) != -1))

  {
    t.date_naissance.jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(jour));

    t.date_naissance.mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(mois));
    t.date_naissance.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(annee));

    strcpy(t.identifiant, gtk_entry_get_text(GTK_ENTRY(idtf)));

    t.poids = atof(gtk_entry_get_text(GTK_ENTRY(poid)));

    strcpy(t.type, gtk_entry_get_text(GTK_ENTRY(type)));

    if (strcmp("Pure", gtk_combo_box_get_active_text(GTK_COMBO_BOX(race))) == 0)
      t.race = 0;
    else
      t.race = 1;

    if (strcmp("Male", gtk_combo_box_get_active_text(GTK_COMBO_BOX(sexe))) == 0)
      t.sexe = 1;
    else
      t.sexe = 0;

    ajout_troupeaux(t);

    ajouttroupeaux = lookup_widget(objet_graphique, "ajouttroupeaux");
    gtk_widget_destroy(ajouttroupeaux);

    ajouttroupeaux = create_ajouttroupeaux();
    gtk_widget_show(ajouttroupeaux);
  }

  else

  {
    if (strcmp(gtk_entry_get_text(GTK_ENTRY(idtf)), "") == 0)
    {
      gtk_label_set_text(GTK_LABEL(obidentifiant), "* champ obligatoire");
    }
    if (strcmp(gtk_entry_get_text(GTK_ENTRY(type)), "") == 0)
    {
      gtk_label_set_text(GTK_LABEL(obtype), "* champ obligatoire");
    }
    if (strcmp(gtk_entry_get_text(GTK_ENTRY(poid)), "") == 0)
    {
      gtk_label_set_text(GTK_LABEL(obpoid), "* champ obligatoire");
    }
    if (gtk_combo_box_get_active(GTK_COMBO_BOX(race)) == -1)
    {
      gtk_label_set_text(GTK_LABEL(obrace), "* champ obligatoire");
    }
    if (gtk_combo_box_get_active(GTK_COMBO_BOX(sexe)) == -1)
    {
      gtk_label_set_text(GTK_LABEL(obsexe), "* champ obligatoire");
    }
  }
}

void on_trajmo_clicked(GtkWidget *objet,
                       gpointer user_data)
{
  GtkWidget *ajouttroupeaux, *modiftroupeaux;
  ajouttroupeaux = lookup_widget(objet, "ajouttroupeaux");
  gtk_widget_destroy(ajouttroupeaux);
  modiftroupeaux = lookup_widget(objet, "modiftroupeaux");
  modiftroupeaux = create_modiftroupeaux();
  gtk_widget_show(modiftroupeaux);
}

void on_trajaf_clicked(GtkWidget *objet,
                       gpointer user_data)
{
  GtkWidget *ajouttroupeaux, *affichetroupeaux, *treeview1;

  ajouttroupeaux = lookup_widget(objet, "ajouttroupeaux");
  gtk_widget_destroy(ajouttroupeaux);

  affichetroupeaux = lookup_widget(objet, "affichetroupeaux");
  affichetroupeaux = create_affichetroupeaux();
  gtk_widget_show(affichetroupeaux);

  treeview1 = lookup_widget(affichetroupeaux, "treeview1");
  afficher_troupeaux(treeview1);
}

void on_fill_clicked(GtkWidget *objet,
                     gpointer user_data)
{
  char id[20];
  char ch[20];
  troupeaux *t;
  t = (troupeaux *)malloc(sizeof(troupeaux));

  GtkWidget *identifiant, *poid, *type, *jour, *mois, *annee, *race, *sexe, *treeview1, *tridentifiant2;

  tridentifiant2 = lookup_widget(objet, "tridentifiant2");
  strcpy(id, gtk_entry_get_text(GTK_ENTRY(tridentifiant2)));

  cherche_id(id, t);

  jour = lookup_widget(objet, "trjour2");
  mois = lookup_widget(objet, "trmois2");
  annee = lookup_widget(objet, "trannee2");
  identifiant = lookup_widget(objet, "tridentifiant3");
  poid = lookup_widget(objet, "trpoid2");
  type = lookup_widget(objet, "trtype2");
  race = lookup_widget(objet, "trrace2");
  sexe = lookup_widget(objet, "trsexe2");

  gtk_entry_set_text(GTK_ENTRY(type), t->type);
  gtk_entry_set_text(GTK_ENTRY(identifiant), t->identifiant);

  sprintf(ch, "%f", t->poids);
  gtk_entry_set_text(GTK_ENTRY(poid), ch);
  gtk_combo_box_set_active(GTK_COMBO_BOX(race), t->race);
  gtk_combo_box_set_active(GTK_COMBO_BOX(sexe), t->sexe);
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(annee), t->date_naissance.annee);
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(mois), t->date_naissance.mois);
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(jour), t->date_naissance.jour);
}

void on_trmoaj_clicked(GtkWidget *objet,
                       gpointer user_data)
{
  GtkWidget *ajouttroupeaux, *modiftroupeaux;

  modiftroupeaux = lookup_widget(objet, "modiftroupeaux");
  gtk_widget_destroy(modiftroupeaux);

  ajouttroupeaux = lookup_widget(objet, "ajouttroupeaux");
  ajouttroupeaux = create_ajouttroupeaux();
  gtk_widget_show(ajouttroupeaux);
}

void on_trmoaf_clicked(GtkWidget *objet,
                       gpointer user_data)
{
  GtkWidget *modiftroupeaux, *affichetroupeaux, *treeview1;
  modiftroupeaux = lookup_widget(objet, "modiftroupeaux");
  gtk_widget_destroy(modiftroupeaux);
  affichetroupeaux = lookup_widget(objet, "affichetroupeaux");
  affichetroupeaux = create_affichetroupeaux();
  gtk_widget_show(affichetroupeaux);
  treeview1 = lookup_widget(affichetroupeaux, "treeview1");
  afficher_troupeaux(treeview1);
}

void on_trmomo_clicked(GtkWidget *objet_graphique,
                       gpointer user_data)
{
  troupeaux t;
  char id[20];
  GtkWidget *identifiant, *poid, *type, *jour, *mois, *annee, *race, *sexe, *treeview1, *identifiant_m, *modiftroupeaux;

  identifiant_m = lookup_widget(objet_graphique, "tridentifiant2");
  strcpy(id, gtk_entry_get_text(GTK_ENTRY(identifiant_m)));

  jour = lookup_widget(objet_graphique, "trjour2");
  t.date_naissance.jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(jour));

  mois = lookup_widget(objet_graphique, "trmois2");
  t.date_naissance.mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(mois));

  annee = lookup_widget(objet_graphique, "trannee2");
  t.date_naissance.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(annee));

  identifiant = lookup_widget(objet_graphique, "tridentifiant3");
  strcpy(t.identifiant, gtk_entry_get_text(GTK_ENTRY(identifiant)));

  poid = lookup_widget(objet_graphique, "trpoid2");
  t.poids = atof(gtk_entry_get_text(GTK_ENTRY(poid)));

  type = lookup_widget(objet_graphique, "trtype2");
  strcpy(t.type, gtk_entry_get_text(GTK_ENTRY(type)));

  race = lookup_widget(objet_graphique, "trrace2");
  sexe = lookup_widget(objet_graphique, "trsexe2");

  if (strcmp("Male", gtk_combo_box_get_active_text(GTK_COMBO_BOX(sexe))) == 0)
    t.sexe = 1;
  else
    t.sexe = 0;
  if (strcmp("Pure", gtk_combo_box_get_active_text(GTK_COMBO_BOX(race))) == 0)
    t.race = 1;
  else
    t.race = 0;
  modifer_troupeaux(id, t);
  modiftroupeaux = lookup_widget(objet_graphique, "modiftroupeaux");
  gtk_widget_destroy(modiftroupeaux);
  modiftroupeaux = create_modiftroupeaux();
  gtk_widget_show(modiftroupeaux);
}

void on_treeview1_row_activated(GtkTreeView *treeview,
                                GtkTreePath *path,
                                GtkTreeViewColumn *column,
                                gpointer user_data)
{
}

void on_trafmo_clicked(GtkWidget *objet,
                       gpointer user_data)
{
  GtkWidget *modiftroupeaux, *affichetroupeaux;

  affichetroupeaux = lookup_widget(objet, "affichetroupeaux");
  gtk_widget_destroy(affichetroupeaux);

  modiftroupeaux = lookup_widget(objet, "modiftroupeaux");
  modiftroupeaux = create_modiftroupeaux();
  gtk_widget_show(modiftroupeaux);
}

void on_trafaj_clicked(GtkWidget *objet,
                       gpointer user_data)
{
  GtkWidget *ajouttroupeaux, *affichetroupeaux;

  affichetroupeaux = lookup_widget(objet, "affichetroupeaux");
  gtk_widget_destroy(affichetroupeaux);

  ajouttroupeaux = lookup_widget(objet, "ajouttroupeaux");
  ajouttroupeaux = create_ajouttroupeaux();
  gtk_widget_show(ajouttroupeaux);
}

void on_trafre_clicked(GtkWidget *objet,
                       gpointer user_data)
{
  GtkWidget *affichetroupeaux, *tridentifiant4, *treeview1;
  char id[20];

  tridentifiant4 = lookup_widget(objet, "tridentifiant4");
  strcpy(id, gtk_entry_get_text(GTK_ENTRY(tridentifiant4)));
  affichetroupeaux = lookup_widget(objet, "affichetroupeaux");
  gtk_widget_destroy(affichetroupeaux);
  affichetroupeaux = create_affichetroupeaux();
  gtk_widget_show(affichetroupeaux);
  treeview1 = lookup_widget(affichetroupeaux, "treeview1");
  trfiltre(treeview1, id);
}

void on_trafsu_clicked(GtkWidget *objet,
                       gpointer user_data)
{
  GtkWidget *id, *affichetroupeaux, *treeview1;
  char identifiant[20];
  id = lookup_widget(objet, "tridentifiant4");
  strcpy(identifiant, gtk_entry_get_text(GTK_ENTRY(id)));
  supprimer_troupeaux(identifiant);
  affichetroupeaux = lookup_widget(objet, "affichetroupeaux");
  gtk_widget_destroy(affichetroupeaux);
  affichetroupeaux = create_affichetroupeaux();
  gtk_widget_show(affichetroupeaux);
  treeview1 = lookup_widget(affichetroupeaux, "treeview1");
  afficher_troupeaux(treeview1);
}

void on_trchmo_clicked(GtkButton *button,
                       gpointer user_data)
{
}

void on_trchsu_clicked(GtkButton *button,
                       gpointer user_data)
{
}

void on_trveou_clicked(GtkButton *button,
                       gpointer user_data)
{
}

void on_trveno_clicked(GtkButton *button,
                       gpointer user_data)
{
}

void on_trnombre_clicked(GtkWidget *objet,
                         gpointer user_data)
{
  GtkWidget *entrytrtyno, *troupeauxtype;
  char type[20];
  char str[10];
  int i;

  troupeauxtype = lookup_widget(objet, "troupeauxtype");
  entrytrtyno = lookup_widget(objet, "entrytrtyno");
  strcpy(type, gtk_entry_get_text(GTK_ENTRY(entrytrtyno)));
  i = nombrestroupeaux(type);

  sprintf(str, "%d", i);

  gtk_label_set_text(GTK_LABEL(troupeauxtype), str);
}

void
on_trrefresh_clicked                   (GtkWidget       *objet,
                                        gpointer         user_data)
{
  GtkWidget *affichetroupeaux, *treeview1;
  affichetroupeaux = lookup_widget(objet, "affichetroupeaux");
  gtk_widget_destroy(affichetroupeaux);
  affichetroupeaux = create_affichetroupeaux();
  gtk_widget_show(affichetroupeaux);
  treeview1 = lookup_widget(affichetroupeaux, "treeview1");
  afficher_troupeaux(treeview1);


}


void
on_trajde_clicked                      (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_trmode_clicked                      (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_trafde_clicked                      (GtkButton       *button,
                                        gpointer         user_data)
{

}


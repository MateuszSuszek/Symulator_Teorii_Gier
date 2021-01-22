#include <stdio.h>
#include <stdbool.h>
#include "head.h"
#include <gtk/gtk.h>

GtkWidget *nimWindow;
GtkToggleButton *AItog, *Playertog;
GtkSpinButton *colNumSpin, *colHgtSpin;
GtkWidget *mainWindow;

void CreateMenuWindow(){

  GtkBuilder *builder;

  builder = gtk_builder_new();
  gtk_builder_add_from_file(builder, "MainMenu.glade", NULL);

  mainWindow = GTK_WIDGET(gtk_builder_get_object(builder, "mainWindow"));

  gtk_builder_connect_signals(builder, NULL);
  g_object_unref(builder);

  gtk_widget_show_all(mainWindow);
}

void CreateNimSetupWindow(){

  GtkBuilder *builder;

  builder = gtk_builder_new();
  gtk_builder_add_from_file(builder, "NimMenu.glade", NULL);

  nimWindow = GTK_WIDGET(gtk_builder_get_object(builder, "nimWindow"));
  AItog = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "checkAI"));
  Playertog = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "checkPlayer"));
  colNumSpin = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "colNumSpin"));
  colHgtSpin = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "colHgtSpin"));

  gtk_builder_connect_signals(builder, NULL);
  g_object_unref(builder);

  gtk_widget_show_all(nimWindow);
}

int main(int argc, char *argv[]){


  gtk_init(&argc, &argv);

  CreateMenuWindow();

  gtk_main();

  return 0;
}

void exit_app() {

  gtk_main_quit();
}

void go_back(){
  gtk_widget_destroy(GTK_WIDGET(nimWindow));
}

void NimClicked(){
    CreateNimSetupWindow();
}

void NimStart(){

  bool isAI = gtk_toggle_button_get_active(AItog);
  int columns = gtk_spin_button_get_value_as_int(colNumSpin);
  int height = gtk_spin_button_get_value_as_int(colHgtSpin);
  gtk_widget_destroy(GTK_WIDGET(nimWindow));
  PlayNim(isAI, columns, height);
}

void ObstructionClicked(){

}

void DomineeringClicked(){

}

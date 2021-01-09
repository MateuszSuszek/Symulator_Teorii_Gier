#include <stdio.h>
#include "head.h"
#include <gtk/gtk.h>

GtkWidget *nimWindow;
GtkToggleButton *AItog;
GtkSpinButton *colNumSpin, *colHgtSpin;
GtkWidget *mainWindow;

int gamemode = 0; // 0-menu 1-Nim 2-Obstruction 3-Domineering

void CreateMenuWindow(){

  //GtkLabel *mainLabel;

  GtkBuilder *builder;

  builder = gtk_builder_new();
  gtk_builder_add_from_file(builder, "MainMenu.glade", NULL);

  mainWindow = GTK_WIDGET(gtk_builder_get_object(builder, "mainWindow"));
  //mainLabel = GTK_LABEL(gtk_builder_get_object(builder, "mainLabel"));

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
  gamemode = 0;
  gtk_widget_destroy(GTK_WIDGET(nimWindow));
}

void NimClicked(){
  if(gamemode == 0){
    gamemode = 1;
    CreateNimSetupWindow();
  }
}

void NimStart(){

  int isAI = gtk_toggle_button_get_active(AItog);
  int columns = gtk_spin_button_get_value_as_int(colNumSpin);
  int height = gtk_spin_button_get_value_as_int(colHgtSpin);

  PlayNim(isAI, columns, height);
}

void ObstructionClicked(){

}

void DomineeringClicked(){

}

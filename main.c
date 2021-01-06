#include <stdio.h>
#include "head.h"
#include <gtk/gtk.h>



void CreateMenuWindow(){

  GtkWidget *mainWindow;
  GtkLabel *mainLabel;

  GtkBuilder *builder;

  builder = gtk_builder_new();
  gtk_builder_add_from_file(builder, "MainMenu.glade", NULL);

  mainWindow = GTK_WIDGET(gtk_builder_get_object(builder, "mainWindow"));
  mainLabel = GTK_LABEL(gtk_builder_get_object(builder, "mainLabel"));

  gtk_builder_connect_signals(builder, NULL);
  g_object_unref(builder);

  gtk_widget_show_all(mainWindow);
}

int main(int argc, char *argv[]){


  gtk_init(&argc, &argv);

  CreateMenuWindow();

  gtk_main();

  return 0;
}

void exit_app() {
  //printf("Exit app\n");
  gtk_main_quit();
}

void NimClicked(){

  printf("N\n");

}

void ObstructionClicked(){

}

void DomineeringClicked(){

}

#include <fcntl.h>

#include <gtk/gtk.h>

#include <string.h>

#include <sys/wait.h>

#include <stdio.h>

/* declarations variables GTK*/
GtkWidget * window, * window3, * window2, * btn1, * btn2, * box, * box2, * box3, * btn, * lbl, * lbl2, * grid, * grid2;
char buff[5000] = "";

/* execution de module tubes nommes + signals */
void tubenom(GtkWidget * widget, gpointer data) {

    g_print("vous avez choisi les tubes nommés\n");
    window2 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    box2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window2), grid);
    lbl = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid), lbl, 0, 0, 1, 1);

    buff[0] = '\0';
    size_t bufflen = 0;
    FILE * fr;
    char * iter = NULL;
    ssize_t read;
    fr = fopen("out.txt", "r");
    if (fr == NULL)
      exit(1);
    while ((read = getline( & iter, & bufflen, fr)) != -1) {
      strcat(buff, iter);
      gtk_label_set_text(GTK_LABEL(lbl), buff);
    }
    fclose(fr);
    if (iter) {
      free(iter);
    }

    g_signal_connect(window2, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_window_set_title(GTK_WINDOW(window2), "Execution Tubes Nommes + Signals");
    gtk_window_set_position(GTK_WINDOW(window2), GTK_WIN_POS_CENTER);
    gtk_widget_show_all(window2);
    gtk_main();

}

/* execution de module sockets */
void sock(GtkWidget * window, gpointer data) {
    g_print("vous avez choisi les sockets\n");
    window3 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    box3 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    grid2 = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window3), grid2);
    lbl2 = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid2), lbl2, 0, 0, 1, 1);

    buff[0] = '\0';
    size_t bufflen = 0;
    FILE * fr;
    char * iter = NULL;
    ssize_t read;

    fr = fopen("out.txt", "r");
    if (fr == NULL)
      exit(1);

    while ((read = getline( & iter, & bufflen, fr)) != -1) {
      strcat(buff, iter);
      gtk_label_set_text(GTK_LABEL(lbl2), buff);
    }

    fclose(fr);
    if (iter) {
      free(iter);
    }

    g_signal_connect(window3, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_window_set_title(GTK_WINDOW(window3), "Execution Sockets");
    gtk_window_set_position(GTK_WINDOW(window3), GTK_WIN_POS_CENTER);
    gtk_widget_show_all(window3);
    gtk_main();
}

/* interface globale */

int main(int argc, char ** argv) {

  gtk_init( & argc, & argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

  btn1 = gtk_button_new_with_label("Tubes nommes + signals");
  btn2 = gtk_button_new_with_label("Sockets");

  gtk_container_add(GTK_CONTAINER(window), box);

  gtk_box_pack_start(GTK_BOX(box), btn1, TRUE, TRUE, 50);
  gtk_box_pack_start(GTK_BOX(box), btn2, TRUE, TRUE, 50);

  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  g_signal_connect(btn1, "clicked", G_CALLBACK(tubenom), "button");
  g_signal_connect(btn2, "clicked", G_CALLBACK(sock), "button");

  gtk_window_set_title(GTK_WINDOW(window), "Faites Votre Choix");
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_widget_show_all(window);

  gtk_main();

  return 0;

}

#include <gtk/gtk.h>

void tubenom(GtkWidget* widget, gpointer data)
{
    g_print("vous avez choisi les tubes nommés\n");
    execl("server_client_fifo",NULL);
    
}

void sock(GtkWidget* widget, gpointer data)
{
    g_print("vous avez choisi les sockets\n");
    execl("server_client_sock",NULL);
}

int main(int argc,char **argv){

gtk_init(&argc,&argv);

GtkWidget *window,*btn1,*btn2,*box;

window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
box=gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);

btn1=gtk_button_new_with_label("Tubes nommes + signals");
btn2=gtk_button_new_with_label("Sockets");

gtk_container_add(GTK_CONTAINER(window),box);

gtk_box_pack_start(GTK_BOX(box),btn1,TRUE,TRUE,50);
gtk_box_pack_start(GTK_BOX(box),btn2,TRUE,TRUE,50);

g_signal_connect(window,"destroy",G_CALLBACK(gtk_main_quit),NULL);
g_signal_connect(btn1,"clicked", G_CALLBACK(tubenom),"button");
g_signal_connect(btn2,"clicked", G_CALLBACK(sock),"button");

gtk_window_set_title(GTK_WINDOW(window),"Faites Votre Choix");
gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
gtk_widget_show_all(window);

gtk_main();

return 0;
	
}

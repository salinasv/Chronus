#include <gtk/gtk.h>

#define APP_NAME_STR "Chronus"

void main_close()
{
	gtk_main_quit();
}

int main (int argc, char *argv[])
{
	GtkWidget *main_window;
	GtkWidget *vbox;
	GtkWidget *calendar;

	gtk_init(&argc, &argv);

	main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(main_window),APP_NAME_STR);
	g_signal_connect(G_OBJECT(main_window), "destroy", G_CALLBACK(main_close), NULL);

	vbox = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(main_window), vbox);

	calendar = gtk_calendar_new();
	gtk_box_pack_start(GTK_BOX(vbox), calendar, FALSE, FALSE, 0);

	gtk_widget_show_all(main_window);
	gtk_main();

	return 0;
}
	

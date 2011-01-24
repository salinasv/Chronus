#include <gtk/gtk.h>
#include <webkit/webkit.h>

#include "menu.h"
#include "todo.h"

#define APP_NAME_STR "Chronus"

/* Menu callbacks */
static void new_action(){}
static void open_action(){}
static void save_action(){}
static void save_as_action(){}
static void quit_action()
{
	gtk_main_quit();
}
static void about_action()
{
	GtkWidget *dialog;
	GtkWidget *vbox;
	GtkWidget *label;
	GtkWidget *button;

	dialog = gtk_dialog_new();

	vbox = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

	label = gtk_label_new("About dialog\n");
	gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 0);

	button = gtk_button_new_from_stock(GTK_STOCK_ABOUT);
	gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 0);

	gtk_widget_show_all(dialog);

}

/* Menu creation */
static GtkActionEntry entries[] =
{
	{ "FileMenuAction", NULL, "_File"},
	{ "HelpMenuAction", NULL, "_Help"},

	{ "NewAction", GTK_STOCK_NEW, "_New", NULL, NULL,
		G_CALLBACK(new_action)	},
	{ "OpenAction", GTK_STOCK_OPEN, "_Open", NULL, NULL,
		G_CALLBACK(open_action)},
	{ "SaveAction", GTK_STOCK_SAVE, "_Save", NULL, NULL,
		G_CALLBACK(save_action)},
	{ "SaveAsAction", GTK_STOCK_SAVE, "Save _As", NULL, NULL,
		G_CALLBACK(save_as_action)},
	{ "QuitAction", GTK_STOCK_QUIT, "_Quit", NULL, NULL,
		G_CALLBACK(quit_action)},

	{ "AboutAction", GTK_STOCK_ABOUT, "_About", NULL, NULL,
		G_CALLBACK(about_action)}
};
static guint n_entries = G_N_ELEMENTS(entries);

void main_close()
{
	todo_uninit();
	gtk_main_quit();
}

int main (int argc, char *argv[])
{
	GtkWidget *main_window;
	GtkWidget *vbox;
	GtkWidget *menubar;
	GtkWidget *web_view;
	GtkActionGroup *action_group;
	GtkUIManager *ui_manager;
	GError *error = NULL;
	gint ui_id;

	gtk_init(&argc, &argv);

	if(!g_thread_supported ())
		g_thread_init (NULL);

	todo_init();
	
	main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(main_window),APP_NAME_STR);
	g_signal_connect(G_OBJECT(main_window), "destroy", G_CALLBACK(main_close), NULL);

	vbox = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(main_window), vbox);

	/* GTKUIManager Menu stuff */
	action_group = gtk_action_group_new("Actions");
	gtk_action_group_add_actions(action_group, entries, n_entries, NULL);

	ui_manager = gtk_ui_manager_new();
	gtk_ui_manager_insert_action_group(ui_manager, action_group, 0);
	ui_id = gtk_ui_manager_add_ui_from_string(ui_manager, MENU_MAIN,-1, &error);
	if (error)
		printf("error %d: %s", error->code, error->message);
	menubar = gtk_ui_manager_get_widget(ui_manager, "/MainMenu");

	gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);
#if 0
	web_view = webkit_web_view_new();
	webkit_web_view_load_uri (WEBKIT_WEB_VIEW(web_view),"http://calendar.google.com");

	gtk_box_pack_start(GTK_BOX(vbox), web_view, FALSE, FALSE, 0);
#endif
	web_view = todo_get_widget();
	gtk_box_pack_start(GTK_BOX(vbox), web_view, FALSE, FALSE, 0);
	gtk_window_set_default_size(GTK_WINDOW (main_window), 800, 600);
	gtk_window_add_accel_group(GTK_WINDOW(main_window),
			gtk_ui_manager_get_accel_group(ui_manager));
	gtk_widget_show_all(main_window);
	gtk_main();

	return 0;
}
	

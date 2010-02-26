#include <gtk/gtk.h>

#define APP_NAME_STR "Chronus"

/* Menu callbacks */
static void new_action(){}
static void open_action(){}
static void save_action(){}
static void save_as_action(){}
static void quit_action(){}
static void help_action(){}

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

	{ "HelpAction", GTK_STOCK_QUIT, "_help", NULL, NULL,
		G_CALLBACK(help_action)}
};
static guint n_entries = G_N_ELEMENTS(entries);

void main_close()
{
	gtk_main_quit();
}

int main (int argc, char *argv[])
{
	GtkWidget *main_window;
	GtkWidget *vbox;
	GtkWidget *calendar;
	GtkWidget *menubar;
	GtkActionGroup *action_group;
	GtkUIManager *ui_manager;
	GError *error = NULL;
	gint ui_id;

	gtk_init(&argc, &argv);

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
	ui_id = gtk_ui_manager_add_ui_from_file(ui_manager, "src/menu.xml", &error);
	if (error)
		printf("error %d: %s", error->code, error->message);
	menubar = gtk_ui_manager_get_widget(ui_manager, "/MainMenu");

	gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);

	calendar = gtk_calendar_new();
	gtk_box_pack_start(GTK_BOX(vbox), calendar, FALSE, FALSE, 0);

	gtk_widget_show_all(main_window);
	gtk_main();

	return 0;
}
	

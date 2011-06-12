#include <stdio.h>
#include <gtk/gtk.h>

#include "io.h"

typedef enum {
	TODO_DONE,
	TODO_TEXT,
	TODO_PROGRESS,
	TODO_NCOLUMNS
} TODO_MODEL_COLS;

typedef struct {
	GtkWidget *dialog;
	GtkWidget *name;
	GtkWidget *description;
} TodoDialog;

typedef struct {
	GtkTreeStore *store;
	GtkWidget *treeview;
	TodoDialog *dialog;
} GtkToDo;

#define CHRONUS_HIG_BORDER 4

GtkToDo *todo = NULL;

static void populate_model(GtkTreeStore *store)
{
	/* TODO: Get actual data to populate at init/refresh. */
}

static void task_do_add(const char *task_name, int progress)
{
	GtkTreeIter iter;
	GtkTreeStore *store = todo->store;

	/* TODO: get actual data */
	gtk_tree_store_append(store, &iter, NULL);

	gtk_tree_store_set(store, &iter,
			TODO_DONE, FALSE,
			TODO_TEXT, g_strdup(task_name),
			TODO_PROGRESS, progress,
			-1);
}

static void add_columns(GtkWidget *treeview)
{
	GtkCellRenderer *rend;
	GtkTreeViewColumn *column;

	/* Done */
	column = gtk_tree_view_column_new();
	gtk_tree_view_column_set_title(column, "Done");
	gtk_tree_view_column_set_resizable(column, FALSE);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

	rend = gtk_cell_renderer_toggle_new();
	gtk_tree_view_column_pack_start(column, rend, TRUE);
	gtk_tree_view_column_add_attribute(column, rend, "active", TODO_DONE);

	/* Description */
	column = gtk_tree_view_column_new();
	gtk_tree_view_column_set_title(column, "Description");
	gtk_tree_view_column_set_resizable(column, FALSE);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

	rend = gtk_cell_renderer_text_new();
	gtk_tree_view_column_pack_start(column, rend, TRUE);
	gtk_tree_view_column_add_attribute(column, rend, "text", TODO_TEXT);

	/* Progress */
	column = gtk_tree_view_column_new();
	gtk_tree_view_column_set_title(column, "Progress");
	gtk_tree_view_column_set_resizable(column, FALSE);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

	rend = gtk_cell_renderer_progress_new();
	gtk_tree_view_column_pack_start(column, rend, TRUE);
	gtk_tree_view_column_add_attribute(column, rend, "value", TODO_PROGRESS);
}

void todo_init()
{

	todo = g_new(GtkToDo, 1);
	todo->dialog = NULL;

	todo->store = gtk_tree_store_new(TODO_NCOLUMNS,
			G_TYPE_BOOLEAN,
			G_TYPE_STRING,
			G_TYPE_INT);

	/* TreeView */
	todo->treeview = gtk_tree_view_new_with_model(GTK_TREE_MODEL(todo->store));
	gtk_tree_view_set_rules_hint(GTK_TREE_VIEW(todo->treeview), TRUE);

	add_columns(todo->treeview);
	populate_model(todo->store);
}

void todo_uninit()
{
	g_object_unref(G_OBJECT(todo->store));
	g_free(todo);
}

void todo_add_task(const char *task_name, int progress)
{
	task_do_add(task_name, progress);
}

GtkWidget* todo_get_widget()
{
	return todo->treeview;
}

static void task_dialog_cb(GtkDialog *dialog, gint response_id,
		gpointer user_data)
{
	TodoDialog *todo_dialog;
	const char *name;

	todo_dialog = todo->dialog;

	switch (response_id) {
		case GTK_RESPONSE_ACCEPT:
			name = gtk_entry_get_text(GTK_ENTRY(todo_dialog->name));
			todo_add_task(g_strdup(name), 0);
		case GTK_RESPONSE_CLOSE:
		case GTK_RESPONSE_DELETE_EVENT:
			gtk_widget_destroy(todo_dialog->dialog);
			g_free(todo->dialog);
			todo->dialog = NULL;
			break;
	}
}

void todo_add_task_dialog()
{
	GtkWidget *dialog;
	GtkWidget *hbox;
	GtkWidget *vbox;
	GtkWidget *label;
	GtkWidget *entry;
	GtkWidget *content_area;
	TodoDialog *todo_dialog;

	dialog = gtk_dialog_new();
	todo_dialog = g_new(TodoDialog, 1);
	todo->dialog = todo_dialog;
	todo_dialog->dialog = dialog;

	hbox = gtk_hbox_new(TRUE, CHRONUS_HIG_BORDER);
	vbox = gtk_vbox_new(FALSE, CHRONUS_HIG_BORDER);

	/* Task name and stuff */
	label = gtk_label_new("Task Name:");
	entry = gtk_entry_new();
	todo_dialog->name = entry;
	gtk_entry_set_activates_default(GTK_ENTRY(todo_dialog->name), TRUE);

	gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, CHRONUS_HIG_BORDER);
	gtk_box_pack_start(GTK_BOX(hbox), entry, FALSE, FALSE, CHRONUS_HIG_BORDER);

	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, CHRONUS_HIG_BORDER);

	/* Task description */
	hbox = gtk_hbox_new(TRUE, CHRONUS_HIG_BORDER);

	label = gtk_label_new("Description:");
	entry = gtk_entry_new();
	todo_dialog->description = entry;
	gtk_entry_set_activates_default(GTK_ENTRY(todo_dialog->description), TRUE);

	gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, CHRONUS_HIG_BORDER);
	gtk_box_pack_start(GTK_BOX(hbox), entry, FALSE, FALSE, CHRONUS_HIG_BORDER);

	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, CHRONUS_HIG_BORDER);

	content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
	gtk_container_add(GTK_CONTAINER(content_area), vbox);

	/* Buttons */
	gtk_dialog_add_button(GTK_DIALOG(dialog), GTK_STOCK_NEW,
			GTK_RESPONSE_ACCEPT);
	gtk_dialog_add_button(GTK_DIALOG(dialog), GTK_STOCK_CLOSE,
			GTK_RESPONSE_CLOSE);

	gtk_dialog_set_default_response(GTK_DIALOG(dialog), GTK_RESPONSE_ACCEPT);
	g_signal_connect(dialog, "response", G_CALLBACK(task_dialog_cb),
			(gpointer)todo->dialog);

	gtk_widget_show_all(dialog);
}

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
	GtkTreeStore *store;
	GtkWidget *treeview;
} GtkToDo;


GtkToDo *todo = NULL;

static void populate_model(GtkTreeStore *store)
{
	GtkTreeIter iter;

	/* TODO: get actual data */
	gtk_tree_store_append(store, &iter, NULL);

	gtk_tree_store_set(store, &iter,
			TODO_DONE, FALSE,
			TODO_TEXT, "No Task available.",
			TODO_PROGRESS, 50,
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


GtkWidget* todo_get_widget()
{
	return todo->treeview;
}

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"

gboolean   lengthLimit   = FALSE;
guint      wordNumber    = 10;
guint      wordLength    = 6;
GtkWindow *mainWindow    = NULL;
GtkWindow *aboutWindow   = NULL;
GtkWindow *authorWindow  = NULL;
GtkFileSelection *fileselection = NULL;
GString   *themeName     = NULL;
GString   *themeFilename = NULL;
guint      themeWeight   = 50;
guint      totalWeight   = 0;

enum
{
	COL_THEME_NAME = 0,
	COL_FILE_NAME,
	COL_WEIGHT_INT,
	NUM_COLS
};

GtkListStore *liststore;
GtkTreeIter   iter;

void callback_init(GtkWidget* main) {
	mainWindow = GTK_WINDOW(main);

	themeName     = g_string_new(NULL);
	themeFilename = g_string_new(NULL);

	liststore = gtk_list_store_new(NUM_COLS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_UINT);

	GtkWidget* view = lookup_widget(main,"treeview");
	gtk_tree_view_set_model(GTK_TREE_VIEW(view), GTK_TREE_MODEL(liststore));

	g_object_unref(liststore);

	/* Now the model will be destroyed when the tree view is destroyed */

	/* --- Column #1 --- */

	GtkTreeViewColumn* col = gtk_tree_view_column_new();

	gtk_tree_view_column_set_title(col, "Name");

	/* pack tree view column into tree view */
	gtk_tree_view_append_column(GTK_TREE_VIEW(view), col);

	GtkCellRenderer* renderer = gtk_cell_renderer_text_new();

	/* pack cell renderer into tree view column */
	gtk_tree_view_column_pack_start(col, renderer, TRUE);

	/* connect 'text' property of the cell renderer to
	 *  model column that contains the first name */
	gtk_tree_view_column_add_attribute(col, renderer, "text", COL_THEME_NAME);


	/* --- Column #2 --- */

	col = gtk_tree_view_column_new();

	gtk_tree_view_column_set_title(col, "Filename");

	/* pack tree view column into tree view */
	gtk_tree_view_append_column(GTK_TREE_VIEW(view), col);

	renderer = gtk_cell_renderer_text_new();

	/* pack cell renderer into tree view column */
	gtk_tree_view_column_pack_start(col, renderer, TRUE);

	/* connect 'text' property of the cell renderer to
	 *  model column that contains the first name */
	gtk_tree_view_column_add_attribute(col, renderer, "text", COL_FILE_NAME);

	/* --- Column #3 --- */

	col = gtk_tree_view_column_new();

	gtk_tree_view_column_set_title(col, "Weight");

	/* pack tree view column into tree view */
	gtk_tree_view_append_column(GTK_TREE_VIEW(view), col);

	renderer = gtk_cell_renderer_text_new();

	/* pack cell renderer into tree view column */
	gtk_tree_view_column_pack_start(col, renderer, TRUE);

	/* connect 'text' property of the cell renderer to
	 *  model column that contains the first name */
	gtk_tree_view_column_add_attribute(col, renderer, "text", COL_WEIGHT_INT);
}

void computeTotalWeight() {
	/* TODO */
}

void
on_new_activate                        (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_open_activate                       (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_save_activate                       (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_save_as_activate                    (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_quit_activate                       (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	exit(0);
}


void
on_add_activate                        (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_remove_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_find_words_activate                 (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	GString* command = g_string_new(NULL);

	/* create inital command with nbTry parameter */
	g_string_printf(command,"babbler -n %d",wordNumber);
	
	/* add limit length parameter */
	if(lengthLimit == TRUE) {
		g_string_append_printf(command," -l %d",wordLength);
	}

	gboolean valid = gtk_tree_model_get_iter_first (GTK_TREE_MODEL(liststore), &iter);

	while (valid)
	{
		/* Walk through the list, reading each row */
		gchar *name;
		gchar *file;
		guint weight;

		/* Make sure you terminate calls to gtk_tree_model_get()
		 * with a '-1' value
		 */
		gtk_tree_model_get (GTK_TREE_MODEL(liststore), &iter, 
				COL_THEME_NAME, &name,
				COL_FILE_NAME, &file,
				COL_WEIGHT_INT, &weight,
				-1);

		/* Do something with the data */
		g_string_append_printf(command," -r '%s:%d'",file,weight);
		g_free(name);
		g_free(file);

		valid = gtk_tree_model_iter_next (GTK_TREE_MODEL(liststore), &iter);
	}
	
	/* let's execute it */
	gint exit_value = 0;
	gchar *output = NULL;
	gboolean ok =
	  g_spawn_command_line_sync(command->str,&output,NULL,&exit_value,NULL);

	GtkWidget* area = lookup_widget(GTK_WIDGET(menuitem),"wordView");
	gtk_label_set_text(GTK_LABEL(area),output);

	g_string_free(command,TRUE);
	g_free(output);
}


void
on_aboutOKButton_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
	gtk_widget_hide(GTK_WIDGET(aboutWindow));
}


void
on_lengthCheck_toggled                 (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(lengthLimit == TRUE) {
		lengthLimit = FALSE;
	}
	else {
		lengthLimit = TRUE;
	}
	/*printf("lengthCheck %d\n",lengthLimit);*/
	GtkWidget *control = lookup_widget(GTK_WIDGET(togglebutton),"wordLength");
	gtk_widget_set_sensitive(control,lengthLimit);
}


void
on_about_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	if(aboutWindow == NULL) {
		aboutWindow = GTK_WINDOW(create_aboutWindow());
	}
	gtk_widget_show(GTK_WIDGET(aboutWindow));
}


void
on_aboutWindow_destroy                 (GtkObject       *object,
                                        gpointer         user_data)
{
	gtk_widget_destroy(GTK_WIDGET(aboutWindow));
	aboutWindow = NULL;
}


void
on_mainWindow_destroy                  (GtkObject       *object,
                                        gpointer         user_data)
{
	exit(0);
}


void
on_wordLength_changed                  (GtkSpinButton   *spinbutton,
                                        gpointer         user_data)
{
	wordLength = gtk_spin_button_get_value_as_int(spinbutton);
	/*printf("wordLength changed %d\n",wordLength);*/
}


void
on_wordNumbers_changed                 (GtkSpinButton   *spinbutton,
                                        gpointer         user_data)
{
	wordNumber = gtk_spin_button_get_value_as_int(spinbutton);
	/*printf("wordNumber changed %d\n",wordNumber);*/
}


void
on_themeNameEntry_changed              (GtkEditable     *editable,
                                        gpointer         user_data)
{
	GtkWidget *entry = lookup_widget(GTK_WIDGET(editable),"themeNameEntry");
	g_string_assign(themeName, gtk_entry_get_text(GTK_ENTRY(entry)));
	/*printf("name = [%s]\n",themeName->str);*/
}


void
on_themeWeightSpin_value_changed       (GtkSpinButton   *spinbutton,
                                        gpointer         user_data)
{
	themeWeight = gtk_spin_button_get_value_as_int(spinbutton);
	/*printf("themeWeight changed %d\n",themeWeight);*/
}


void
on_themeFilenameEntry_changed          (GtkEditable     *editable,
                                        gpointer         user_data)
{
	GtkWidget *entry = lookup_widget(GTK_WIDGET(editable),"themeFilenameEntry");
	g_string_assign(themeFilename, gtk_entry_get_text(GTK_ENTRY(entry)));
	/*printf("filename = [%s]\n",themeFilename->str);*/

}


void
on_themeAddButton_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
	/* Append an empty row to the list store. Iter will point to the new row */
	gtk_list_store_append(liststore, &iter);

	/* Fill fields with some data */
	gtk_list_store_set (liststore, &iter,
			COL_THEME_NAME, themeName->str,
			COL_FILE_NAME, themeFilename->str,
			COL_WEIGHT_INT, themeWeight,
			-1);

	/*printf("new Theme [%s,%s,%d]\n",themeName->str,themeFilename->str,themeWeight);*/
	computeTotalWeight();
}


void
on_themeRemoveButton_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkTreeSelection *selection;
	GtkTreeModel     *model;
	GtkTreeView      *treeview;

	treeview = GTK_TREE_VIEW(lookup_widget(GTK_WIDGET(button),"treeview"));

	/* This will only work in single or browse selection mode! */

	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));
	if (gtk_tree_selection_get_selected(selection, &model, &iter))
	{

		gtk_list_store_remove(GTK_LIST_STORE(model), &iter);
	}

	computeTotalWeight();
}


void
on_creditButton_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
	if(authorWindow == NULL) {
		authorWindow = GTK_WINDOW(create_authorWindow());
	}
	gtk_widget_show(GTK_WIDGET(authorWindow));
}


void
on_authorOKButton_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
	gtk_widget_hide(GTK_WIDGET(authorWindow));
}


void
on_authorWindow_destroy                (GtkObject       *object,
                                        gpointer         user_data)
{
	gtk_widget_destroy(GTK_WIDGET(authorWindow));
	authorWindow = NULL;
}



void
on_treeview_cursor_changed             (GtkTreeView     *treeview,
                                        gpointer         user_data)
{
  GtkTreeSelection *selection;
  GtkTreeModel     *model;

  /* This will only work in single or browse selection mode! */

  selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));
  if (gtk_tree_selection_get_selected(selection, &model, &iter))
  {
    gchar *name;
    gchar *file;
    guint weight;

    gtk_tree_model_get (model, &iter,
                        COL_THEME_NAME, &name,
                        COL_FILE_NAME, &file,
                        COL_WEIGHT_INT, &weight,
                        -1);

    /*gtk_tree_model_get (model, &iter, COL_THEME_NAME, &name, -1);
    gtk_tree_model_get (model, &iter, COL_FILE_NAME, &file, -1);
    gtk_tree_model_get (model, &iter, COL_WEIGHT_INT, &weight, -1);*/

    g_print ("selected row is: %s/%s/%d\n", name,file,weight);

    g_string_assign(themeName,name);
    g_string_assign(themeFilename,file);
    themeWeight = weight;

    GtkWidget* widget = lookup_widget(GTK_WIDGET(treeview),"themeNameEntry");
    gtk_entry_set_text(GTK_ENTRY(widget),name);

    widget = lookup_widget(GTK_WIDGET(treeview),"themeFilenameEntry");
    gtk_entry_set_text(GTK_ENTRY(widget),file);

    widget = lookup_widget(GTK_WIDGET(treeview),"themeWeightSpin");
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget),weight);
    

    g_free(name);
    g_free(file);
  }
}


void
on_themeModify_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkTreeSelection *selection;
	GtkTreeModel     *model;
	GtkTreeView      *treeview;

	treeview = GTK_TREE_VIEW(lookup_widget(GTK_WIDGET(button),"treeview"));

	/* This will only work in single or browse selection mode! */

	/*printf("change to (%s/%s/%d)\n",themeName->str,themeFilename->str,themeWeight);*/

	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));
	if (gtk_tree_selection_get_selected(selection, &model, &iter))
	{

		gtk_list_store_set (GTK_LIST_STORE(model), &iter,
				COL_THEME_NAME, themeName->str,
				COL_FILE_NAME, themeFilename->str,
				COL_WEIGHT_INT, themeWeight,
				-1);
	}
}


void
on_themeFilenameButton_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{
	if(fileselection == NULL) {
		fileselection = GTK_FILE_SELECTION(create_fileselection());
	}

	gtk_widget_show(GTK_WIDGET(fileselection));
}


void
on_fileselection_response              (GtkDialog       *dialog,
                                        gint             response_id,
                                        gpointer         user_data)
{
	if(response_id != GTK_RESPONSE_DELETE_EVENT) {
		gtk_widget_hide(GTK_WIDGET(fileselection));
	}
	else {
		/*printf("cassssséé !!\n");*/
		fileselection = NULL;
	}

	if(response_id == GTK_RESPONSE_OK) {
		gchar* filename = gtk_file_selection_get_filename(fileselection);
		/*printf("Responsseeeeeeee = [%s] - [%d]\n",filename,response_id);*/
		GtkWidget *entry = 
			lookup_widget(GTK_WIDGET(mainWindow),"themeFilenameEntry");
		gtk_entry_set_text(GTK_ENTRY(entry),filename);
	}
}



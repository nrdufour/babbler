#include <gtk/gtk.h>

void callback_init(GtkWidget* main);

void
on_new_activate                        (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_open_activate                       (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_save_activate                       (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_save_as_activate                    (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_quit_activate                       (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_add_activate                        (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_remove_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_find_words_activate                 (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_aboutOKButton_clicked               (GtkButton       *button,
                                        gpointer         user_data);

void
on_lengthCheck_toggled                 (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_about_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_aboutWindow_destroy                 (GtkObject       *object,
                                        gpointer         user_data);

void
on_mainWindow_destroy                  (GtkObject       *object,
                                        gpointer         user_data);

void
on_wordLength_changed                  (GtkSpinButton   *spinbutton,
                                        gpointer         user_data);

void
on_wordNumbers_changed                 (GtkSpinButton   *spinbutton,
                                        gpointer         user_data);

void
on_themeNameEntry_changed              (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_themeWeightSpin_value_changed       (GtkSpinButton   *spinbutton,
                                        gpointer         user_data);

void
on_themeFilenameEntry_changed          (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_themeAddButton_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_themeRemoveButton_clicked           (GtkButton       *button,
                                        gpointer         user_data);

void
on_creditButton_clicked                (GtkButton       *button,
                                        gpointer         user_data);

void
on_authorOKButton_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_authorWindow_destroy                (GtkObject       *object,
                                        gpointer         user_data);


void
on_treeview_cursor_changed             (GtkTreeView     *treeview,
                                        gpointer         user_data);

void
on_themeModify_clicked                 (GtkButton       *button,
                                        gpointer         user_data);

void
on_themeFilenameButton_clicked         (GtkButton       *button,
                                        gpointer         user_data);

void
on_fileselection_response              (GtkDialog       *dialog,
                                        gint             response_id,
                                        gpointer         user_data);


#include "p3/intelliappwin.h"
#include "p3/buttontest.h"
#include "p3/intelliapp.h"
#include <gtk/gtk.h>

struct _IntelliAppWindow {
  GtkApplicationWindow parent;
};

typedef struct _IntelliAppWindowPrivate IntelliAppWindowPrivate;

struct _IntelliAppWindowPrivate {
  // Add different widgets to be controlled here
  GtkWidget *stack;
};

G_DEFINE_TYPE_WITH_PRIVATE(IntelliAppWindow, intelli_app_window,
                           GTK_TYPE_APPLICATION_WINDOW);

static void intelli_app_window_init(IntelliAppWindow *win) {
  gtk_widget_init_template(GTK_WIDGET(win));
}

static void printtest(GtkWidget *widget, gpointer data) {
  g_print("BUTTON CLICKED");
}

static void intelli_app_window_class_init(IntelliAppWindowClass *clas) {
  // This is the function call to load the UI from the file
  gtk_widget_class_set_template_from_resource(
      GTK_WIDGET_CLASS(clas), "/org/gtk/intelliapp/Project3.ui");
  // For each widget that appears in
  // struct _IntelliAppWindowPrivate
  // add this kind of line:
  gtk_widget_class_bind_template_child_private(GTK_WIDGET_CLASS(clas),
                                               IntelliAppWindow, stack);
  // an attempt to create event handlers with the buttons
  GtkBuilder *builder;
  GObject *button;
  char buttonNames[16][20] = {"Attri_FU_But",        "Constraint_FU_But",
                              "Pref_Lab_FU",         "Pen_FU_But",
                              "Poss_FU_But",         "Qual_FU_But",
                              "Attri_Man_But",       "Constraint_Man_But",
                              "Pref_Lab_Man",        "Pen_Man_But",
                              "Poss_Man_But",        "Qual_Man_But",
                              "Omni_Opt_But",        "Opt_But",
                              "Exemplification_But", "Feasability_But"};
  builder = gtk_builder_new();
  // for (int i = 0; i < 16; i++) {
  // }
  g_print("BUILD_BUILDER_HERE");
  button = gtk_builder_get_object(builder, "Attri_Man_But");
  // TODO: Figure out why G_CALLBACK doesn't work
  g_signal_connect(button, "clicked", G_CALLBACK(printtest), NULL);
}

IntelliAppWindow *intelli_app_window_new(IntelliApp *app) {
  return (_IntelliAppWindow *)g_object_new(INTELLI_APP_WINDOW_TYPE,
                                           "application", app, NULL);
}

void intelli_app_window_open(IntelliAppWindow *win, GFile *file) {
  IntelliAppWindowPrivate *priv;
  gchar *basename;
  GtkWidget *scrolled, *view;
  gchar *contents;
  gsize length;

  priv =
      (_IntelliAppWindowPrivate *)intelli_app_window_get_instance_private(win);
  basename = g_file_get_basename(file);
  // submenu thing
  // builder = gtk_builder_new_from_resource
  // ("/org/gtk/exampleapp/gears-menu.ui");
  scrolled = gtk_scrolled_window_new(NULL, NULL);
  gtk_widget_show(scrolled);
  gtk_widget_set_hexpand(scrolled, TRUE);
  gtk_widget_set_vexpand(scrolled, TRUE);
  view = gtk_text_view_new();
  gtk_text_view_set_editable(GTK_TEXT_VIEW(view), FALSE);
  gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(view), FALSE);
  gtk_widget_show(view);
  gtk_container_add(GTK_CONTAINER(scrolled), view);
  gtk_stack_add_titled(GTK_STACK(priv->stack), scrolled, basename, basename);

  if (g_file_load_contents(file, NULL, &contents, &length, NULL, NULL)) {
    GtkTextBuffer *buffer;

    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));
    gtk_text_buffer_set_text(buffer, contents, length);
    g_free(contents);
  }

  g_free(basename);
}

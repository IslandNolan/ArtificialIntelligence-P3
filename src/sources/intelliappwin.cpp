#include "p3/intelliappwin.h"
#include "p3/intelliapp.h"
#include <gtk/gtk.h>

struct _IntelliAppWindow {
  GtkApplicationWindow parent;
};

typedef struct _IntelliAppWindowPrivate IntelliAppWindowPrivate;

struct _IntelliAppWindowPrivate {
  GtkWidget *stack;
};

G_DEFINE_TYPE_WITH_PRIVATE(IntelliAppWindow, intelli_app_window,
                           GTK_TYPE_APPLICATION_WINDOW);

static void intelli_app_window_init(IntelliAppWindow *win) {
  gtk_widget_init_template(GTK_WIDGET(win));
}

static void intelli_app_window_class_init(IntelliAppWindowClass *clas) {
  gtk_widget_class_set_template_from_resource(
      GTK_WIDGET_CLASS(clas), "/org/gtk/intelliapp/Project3.ui");
  gtk_widget_class_bind_template_child_private(GTK_WIDGET_CLASS(clas),
                                               IntelliAppWindow, stack);
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

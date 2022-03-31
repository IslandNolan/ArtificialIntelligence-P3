#include "p3/intelliapp.h"
#include "p3/intelliappwin.h"
#include "p3/p3.h"
#include <gtk/gtk.h>

struct _IntelliApp {
  GtkApplication parent;
};

G_DEFINE_TYPE(IntelliApp, intelli_app, GTK_TYPE_APPLICATION);

static void intelli_app_init(IntelliApp *app) {}

static void intelli_app_activate(GApplication *app) {
  IntelliAppWindow *win;

  win = intelli_app_window_new(INTELLI_APP(app));
  gtk_window_present(GTK_WINDOW(win));
}

static void intelli_app_open(GApplication *app, GFile **files, gint n_files,
                             const gchar *hint) {
  GList *windows;
  IntelliAppWindow *win;
  int i;

  windows = gtk_application_get_windows(GTK_APPLICATION(app));
  if (windows)
    win = INTELLI_APP_WINDOW(windows->data);
  else
    win = intelli_app_window_new(INTELLI_APP(app));

  for (i = 0; i < n_files; i++)
    intelli_app_window_open(win, files[i]);

  gtk_window_present(GTK_WINDOW(win));
}

static void intelli_app_class_init(IntelliAppClass *clas) {
  G_APPLICATION_CLASS(clas)->activate = intelli_app_activate;
  G_APPLICATION_CLASS(clas)->open = intelli_app_open;
}

IntelliApp *intelli_app_new(void) {
  return (_IntelliApp *)g_object_new(INTELLI_APP_TYPE, "application-id",
                                     "org.gtk.intelliapp", "flags",
                                     G_APPLICATION_HANDLES_OPEN, NULL);
}

#ifndef __INTELLIAPPWIN_H
#define __INTELLIAPPWIN_H

#include "intelliapp.h"
#include <gtk/gtk.h>

#define INTELLI_APP_WINDOW_TYPE (intelli_app_window_get_type())
G_DECLARE_FINAL_TYPE(IntelliAppWindow, intelli_app_window, INTELLI, APP_WINDOW,
                     GtkApplicationWindow)

IntelliAppWindow *intelli_app_window_new(IntelliApp *app);
void intelli_app_window_open(IntelliAppWindow *win, GFile *file);

#endif /* __INTELLIAPPWIN_H */

#ifndef __INTELLIAPP_H
#define __INTELLIAPP_H

#include <gtk/gtk.h>

#define INTELLI_APP_TYPE (intelli_app_get_type())
G_DECLARE_FINAL_TYPE(IntelliApp, intelli_app, INTELLI, APP, GtkApplication)

IntelliApp *intelli_app_new(void);

#endif /* __INTELLIAPP_H */

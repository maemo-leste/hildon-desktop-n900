#ifndef __HD_LAUNCHER_ENV_H__
#define __HD_LAUNCHER_ENV_H__

#include <glib.h>

char **hd_launcher_get_env(gboolean hildonize);
void hd_launcher_env_free(void);

#endif

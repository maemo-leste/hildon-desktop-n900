#include <glib.h>
#include <glib/gprintf.h>
#include <stdio.h>
#include "hd-launcher-env.h"

#define ENV_INI             "/etc/hildon-desktop/environment.conf"
#define ENV_GENERIC_GROUP     "Generic"
#define ENV_HILDON_GROUP      "Hildon"

static char **env_generic = NULL;
static char **env_hildon = NULL;

static void hd_launcher_env_load(void)
{
  GKeyFile *keyFile = g_key_file_new();
  
  env_generic = g_get_environ();
  env_hildon = g_get_environ();
  
  if (!g_key_file_load_from_file(keyFile, ENV_INI, G_KEY_FILE_NONE, NULL)) {
    g_key_file_free(keyFile);
    return;
  }
  
  gchar **genericKeys = g_key_file_get_keys(keyFile, ENV_GENERIC_GROUP, NULL, NULL);
  if (genericKeys) {
    for (int i = 0; genericKeys[i] != NULL; ++i) {
      char *var = g_key_file_get_string(keyFile, ENV_GENERIC_GROUP, genericKeys[i], NULL);
      if(var) {
        env_generic = g_environ_setenv(env_generic, genericKeys[i], var, TRUE);
        g_free(var);
      }
    }
    g_strfreev(genericKeys);
  }
  
  gchar **hildonKeys = g_key_file_get_keys(keyFile, ENV_HILDON_GROUP, NULL, NULL);
  if (hildonKeys) {
    for (int i = 0; hildonKeys[i] != NULL; ++i) {
      char *var = g_key_file_get_string(keyFile, ENV_HILDON_GROUP, hildonKeys[i], NULL);
      if(var) {
        env_hildon = g_environ_setenv(env_hildon, hildonKeys[i], var, TRUE);
        g_free(var);
      }
    }
    g_strfreev(hildonKeys);
  }
  
  g_key_file_free(keyFile);
}

char **hd_launcher_get_env(gboolean hildonize)
{
  if (!env_generic || !env_hildon)
    hd_launcher_env_load();
  
  if (hildonize)
    return env_hildon;
  else 
    return env_generic;
}

void hd_launcher_env_free(void) 
{
  if (env_generic) 
    g_strfreev(env_generic);
  if (env_hildon) 
    g_strfreev(env_hildon);
}

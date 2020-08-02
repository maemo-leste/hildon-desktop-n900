#include "iio-dbus.h"
#include <string.h>

static const char *orientations[] = {
        "undefined",
        "normal",
        "bottom-up",
        "left-up",
        "right-up",
        NULL
};

int dbus_parse_orientation_property_changed(DBusMessage *m)
{
  const char *interface;
  DBusMessageIter iter, sub;

  if (!dbus_message_iter_init(m, &iter) || dbus_message_iter_get_arg_type(&iter) != DBUS_TYPE_STRING)
    goto error;

  dbus_message_iter_get_basic(&iter, &interface);
  
  if(strcmp(interface, "net.hadess.SensorProxy") != 0)
    return -1;

  if (!dbus_message_iter_next(&iter) || dbus_message_iter_get_arg_type(&iter) != DBUS_TYPE_ARRAY)
    goto error;

  dbus_message_iter_recurse(&iter, &sub);

  while (dbus_message_iter_get_arg_type(&sub) == DBUS_TYPE_DICT_ENTRY) 
    {
      const char *name;
      DBusMessageIter entry;
      
      dbus_message_iter_recurse(&sub, &entry);

      if (dbus_message_iter_get_arg_type(&entry) != DBUS_TYPE_STRING)
        goto error;

      dbus_message_iter_get_basic(&entry, &name);
      if(!dbus_message_iter_next(&entry))
        goto error;

      if (strcmp(name, "AccelerometerOrientation") == 0) 
        {
          if (dbus_message_iter_get_arg_type(&entry) == DBUS_TYPE_VARIANT) 
            {
              DBusMessageIter variant;
              const char *orientation;
              int i = 0;
              int ret = -1;
              
              dbus_message_iter_recurse(&entry, &variant);
              if (dbus_message_iter_get_arg_type(&variant) != DBUS_TYPE_STRING)
                return -1;
              
              dbus_message_iter_get_basic(&variant, &orientation);
              
              while(orientations[i] != NULL)
                {
                  if(strcmp(orientations[i], orientation) == 0) 
                    {
                      ret = i;
                      break;
                    }
                  ++i;
                }
              
              return ret;
            }
          else goto error;
        }

      dbus_message_iter_next(&sub);
    }

  error:
  return -1;
}

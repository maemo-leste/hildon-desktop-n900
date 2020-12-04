
#ifndef __IIO_DBUS_H__
#define __IIO_DBUS_H__

#include <dbus/dbus.h>

#define IIO_PROXY_PATH "/net/hadess/SensorProxy"
#define IIO_PROXY_IFACE "net.hadess.SensorProxy"
#define FDO_PROPERTIES_IFACE "org.freedesktop.DBus.Properties"

typedef enum {
  ORIENTATION_UNDEFINED = 0,
  ORIENTATION_NORMAL = 1,
  ORIENTATION_BOTTOM_UP = 2,
  ORIENTATION_LEFT_UP = 3,
  ORIENTATION_RIGHT_UP = 4
} orientation_enums;

int dbus_parse_orientation_property_changed(DBusMessage *m);


#endif

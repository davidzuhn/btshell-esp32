idf_component_register(
SRCS
  "main.c"
  "gatt_svr.c"
#  "cmd_btshell.c"
#  "btshell.c"
#  "parse.c"
#  "misc.c"
INCLUDE_DIRS
  "."
REQUIRES
  "bt"
  "console"
)

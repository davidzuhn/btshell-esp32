idf_component_register(
SRCS
  "main.c"
  "gatt_svr.c"
  "misc.c"
  "parse.c"
  "cmd.c"
#  "cmd_btshell.c"
#  "btshell.c"
INCLUDE_DIRS
  "."
REQUIRES
  "bt"
  "console"
)

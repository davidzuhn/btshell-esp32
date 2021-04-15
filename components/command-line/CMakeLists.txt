idf_component_register(SRCS
			 "command-line.c"
                       INCLUDE_DIRS
		         "."
		       REQUIRES
		         console
			 vfs
			 fatfs)

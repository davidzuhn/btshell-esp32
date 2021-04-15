idf_component_register(SRCS
			 "command-line.c"
                       INCLUDE_DIRS
		         "include"
		       REQUIRES
		         console
			 vfs
			 fatfs)

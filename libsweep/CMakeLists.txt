add_definitions (-D__LIBSWEEP__)

add_library (sweep #SHARED
	init.c
	find_dir.c
	cmdline.c)
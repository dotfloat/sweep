add_definitions (-D__LIBSWEEP__)

add_library (sweep #SHARED
	m_init.c
	m_find_dir.c
	m_cmdline.c
	m_state.c
	m_time.c
	m_debug.c
	
	g_init.c
	g_data.c
	
	b_init.c
	b_resize.c
	b_limits.c
	b_populate.c
	b_cell.c)
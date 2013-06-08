
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>

#include <sweep.h>

const char *configdir = "/";

const char *userdirs[] = { /* search directories within the user's home directory */
	"/.config/sweep",
	"/.local/share/sweep",
	NULL
};

const char *globaldirs[] = { /* search directories within the system */
	"/usr/share/sweep",
	"/usr/share/games/sweep",
	"/usr/local/share/sweep",
	"/usr/local/share/games/sweep",
	"/etc/sweep",
	NULL
};

/* User dir search */
const char *__sFindUserDir(const char *dir, const char *file, S_BOOL create){
	file = file?file:""; /* Avoid segfaults when file == NULL */

	/* get home dir (~) */
	struct passwd *pw = getpwuid(getuid());

	/* check if dirs exist */
	int i;
	for(i=0; userdirs[i]; i++) {
		size_t len = strlen(pw->pw_dir) + strlen(userdirs[i]) + strlen(dir) + 1;
		char test[len];
		struct stat st = {0};
		snprintf(test, len, "%s%s%s", pw->pw_dir, userdirs[i], dir);

		if(!stat(test, &st)) {
			if(S_ISDIR(st.st_mode)) {
				break;
			}
		} else {
			/* TODO: Check to see that it is safe to not do anything. */
		}
	}

	/* If directory not found, create it (but only if S_BOOL create = true) */
	if(!userdirs[i] && create) {
		size_t len = strlen(pw->pw_dir) + strlen(userdirs[0]) + strlen(dir)+1; /* First search location is assumed to be default */
		char test[len];
		snprintf(test, len, "%s%s%s", pw->pw_dir, userdirs[0], dir);
		mkdir(test, 0755);
		i=0; /* We're using the first search location. */
	} else if(!userdirs[i]) {
		return NULL;
	}

	size_t len = strlen(pw->pw_dir) + 
				 strlen(userdirs[i]) +
				 strlen(dir) + 
				 strlen(file) + 1;

	char *path = malloc(len);
	snprintf(path, len, "%s%s%s%s", pw->pw_dir, userdirs[i], dir, file);

	return path;
}

const char *sFindUserConfig(const char *file, S_BOOL create){
	return __sFindUserDir(configdir, file, create);
}

/* Global dir search */
const char *__sFindGlobalDir(const char *dir, const char *file){
	file = file?file:""; /* Avoid segfaults when file == NULL */

	/* check if dirs exist */
	int i;
	for(i=0; globaldirs[i]; i++) {
		size_t len = strlen(globaldirs[i]) + strlen(dir) + 1;
		char test[len];
		struct stat st = {0};
		snprintf(test, len, "%s%s", globaldirs[i], dir);

		if(!stat(test, &st)) {
			if(S_ISDIR(st.st_mode)) {
				break;
			}
		} else {
			/* TODO: Check to see that it is safe to not do anything. */
		}
	}

	if(!globaldirs[i]) {
		return NULL;
	}

	size_t len = strlen(globaldirs[i]) +
				 strlen(dir) + 
				 strlen(file) + 1;

	char *path = malloc(len);
	snprintf(path, len, "%s%s%s", globaldirs[i], dir, file);

	return path;
}

const char *sFindGlobalConfig(const char *file){
	return __sFindGlobalDir(configdir, file);
}
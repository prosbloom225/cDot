#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <pwd.h>

// Debug defines
#define DEBUG_OUT  1
#define HOME "/home/prosbloom/tmp/cdot/home"


int main(int argc, char** argv) {
#ifdef DEBUG_OUT
	printf("ARGS\n");
	for (int i=0; i < argc; i++) {
		printf("%i: %s\n", i, argv[i]);
	}
#endif
	//  argv[1] should be the folder we want to parse
	DIR *dp = NULL;
	char buff[128];
	memset(buff,0,sizeof(buff));
	strcpy(buff, argv[0]);
	// Relative pathing
	char path_to_dotfiles[256];	
	realpath(argv[1], path_to_dotfiles);
#ifdef DEBUG_OUT
	printf("DOTFILES: %s\n", path_to_dotfiles);
#endif
	// Check that it exists, if not return 1
	if (NULL == (dp = opendir(path_to_dotfiles)) ) {
		printf("Cannot open input directory [%s]\n", path_to_dotfiles);
		return 1;
	} else {
		// Set the HOME to argv[2], else ~ if undefined
#ifndef HOME
		const char* HOME;
		if (argc == 3) {
			HOME = argv[1];
			printf("arg\n");
			printf("%s\n", argv[1]);
		} else {
			struct passwd *pw = getpwuid(getuid());
			HOME= pw->pw_dir;
			printf("pwd\n");
		}
#endif
#ifdef DEBUG_OUT
		printf("HOME: %s\n", HOME);
#endif
		// Foreach through the directory and symlink any file to HOME
		struct dirent *dir;
		while ((dir = readdir(dp)) != NULL) {
			// ignore nonfile files
			if (dir->d_type == DT_REG) {
				// Build paths
				char initial_file_location[256];
				char link_file_location[256];
				snprintf(initial_file_location, sizeof initial_file_location, "%s/%s", path_to_dotfiles, dir->d_name);
				snprintf(link_file_location, sizeof link_file_location, "%s/%s", HOME, dir->d_name);
#ifdef DEBUG_OUT
				printf("\n%s -> %s", initial_file_location, link_file_location);
#endif
				// Symlink
				int ret = symlink(initial_file_location, link_file_location);
#ifdef DEBUG_OUT
				if (ret != 0) 
					printf(" - ERROR Symlinking: %i", ret);
#endif
			}
		}
		printf("\n---------------------\nSymlinking complete!\n");
		closedir(dp);
	}
	return 0;
}

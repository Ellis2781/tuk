//libc
#include <stdio.h>
#include <string.h>

//libgit
#include <git2/clone.h>
#include <git2/global.h>
#include <git2/types.h>
#include <git2/deprecated.h>

int main(int argc, char *argv[]) {

	if(argc<2) {
		printf("No arguments specified. Use --help for help\n");
		return 1;
	}
	if(strcmp(argv[1], "update")==0) {
		// Updating stuff, existing packages
		printf("Syncing all packages\n");
		printf("Building from source may take a while\n");
		return 0;
	}
	if(strcmp(argv[1], "-S")==0) {
		if(argc<3) {
			printf("Not enough arguments\n");
			return 1;
		//This is where the program would check if the package name exists under /etc/tuk
		}
	
	}
	if(strcmp(argv[1], "addpkg")==0) {
                if(argc<4) {
                        printf("Not enough arguments\n");
                        return 1;
		}
                //This is where tuk program will check if the package name exists under /etc/tuk
		//Currently working on getting git to work, may not function properly
		git_libgit2_init();
		git_clone(NULL, argv[3], "/etc/tuk/", NULL);
		
		return 0;
        }
	// As of now, this section is formatted horribly
        if(strcmp(argv[1], "--help")==0) {
		printf("System update		tuk update\n"); 
		printf("Updates/reinstalls a package		tuk -S [package] \n");
		printf("Removes a package		tuk -R [package]\n");
		printf("Displays this page		tuk --help\n");
		printf("Adds a package              tuk pkgadd [package] [giturl]\n");
		return 0;
	}
}

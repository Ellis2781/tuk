//libc
#include <stdio.h>
#include <string.h>
#include <unistd.h>

//libgit
#include <git2/clone.h>
#include <git2/global.h>
#include <git2/types.h>
#include <git2/deprecated.h>
#include <git2/errors.h>

static struct package 
{
	char name[50];
	char giturl[100];
	char directory[100];
};

int main(int argc, char *argv[]) {
	struct package pkgconfig;
	
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
		else 
		{	
			//check online directory with libcurl to see if it already has a makefile if possible.
			printf("Downloading src...\n");
			//git clone
			printf("Checking for a Makefile...\n");
			//checks the directory from pkgconfig

			if (fopen("test/Makefile", "r") == NULL) {
				printf("Makefile doesn't exist\n");
				
			}
			else 
			{
				static char command[20] = "make -C test";
				printf("Found Makefile, executing make\n");
				//system(command);
				if(system(command) != 0)
				{
					printf("Something failed, returning 1.");
					return 1;
				}			
			}
		}
			
	}
	if(strcmp(argv[1], "addpkg")==0) {
                if(argc<2) {
                        printf("Not enough arguments\n");
                        return 1;
		}
                else 
		{
                        printf("Null\n");
                        return 1;
                }
                //This is where tuk program will check if the package name exists under /etc/tuk
		//Currently working on getting git to work, may not function properly

		git_libgit2_init();
	
		git_error_last();

		//char command[1024];
		//sprintf(command, "git clone %10s", argv[2]);
		//system(command);

		printf("%s\n", argv[2]);
		
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

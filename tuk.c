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

#include "tuk.h"

int main(int argc, char *argv[]) {
	static struct pkgconfig pkg;
	
	if(argc<2) 
	{
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
		if(argc<4) 
		{
			printf("Not enough arguments\n");
			return 1;
		//This is where the program would check if the package name exists under /etc/tuk
		}
		else 
		{	
			//At this point the package name is already supplied so now it can be added to the struct.
			memcpy(pkg.name, argv[2], 50);
			
			FILE *fptr;
			if(fopen("pkglist", "r") == 0 || fopen("pkglist", "r") != NULL)
			{
				fptr = fopen("pkglist", "r");
			}
			else if(fopen("/etc/tuk/pkglist", "r") == 0 || fopen("/etc/pkglist", "r") != NULL)
			{
				fptr = fopen("/etc/tuk/pkglist", "r");
			}

			if (fopen("test/Makefile", "r") == NULL) 
			{
				printf("Makefile doesn't exist\n");
			}
			else 
			{
				static char directory[50] = "etc/tuk/";
				static char command[20] = "make -C etc/tuk";
				sprintf(command, "%s %s", command, directory);
				printf("Found Makefile, executing make\n");
				//system(command);
				if(system(command) != 0)
				{
					printf("Something failed, returning 1.\n");
					return 1;
				}			
			}

			//I kind of copied and pasted these functions from a tutorial
			int line, col;			
			indexOf(fptr, pkg.name, &line, &col);

			//checks if the pkg name is in the pkglist file
			//for now all this does is check if the package name exists in the file.
			//this may not seem too bad but you need to consider the possibility that the package name may be apart of another link or url
			
			
			
			//if it exists then it checks the link to see if it is working
			if (line != -1)
			{
        			printf("'%s' was found in pkglist.\n", pkg.name);
			}
			else
			{
				printf("'%s' does not exist in pkglist. Please use the addpkg flag or add the package to pkglist.", pkg.name);
				return 1;
			}
			
			//then it stores the name into pkg.name and url into pkg.giturl

			////check online directory with libcurl to see if it already has a makefile if possible.
			printf("Downloading src...\n");
			//git clone
			printf("Checking for a Makefile...\n");

			//checks the directory from pkg.directory for the makefile

			//stores arg 2 into the pkg struct

			//checks if the package name is thee name of a valid package

		}
			
	}
	if(strcmp(argv[1], "addpkg")==0) {
                if(argc<4) {
                        printf("Not enough arguments\n");
                        return 1;
		}
		if(argv[2] == NULL)
		{
			printf("Arg 2 is equal to null, something failed.");
		}
		
		//static char name = (char)*argv[2];
		
		//static char url = (char)*argv[3];

		//Adding package to struct
		memcpy(pkg.giturl, argv[3], 50);
		memcpy(pkg.name, argv[2], 50);

		FILE *pkglist;

		pkglist = fopen("pkglist", "w");

		//setting up line to print to the text file
		static char txtline[2400];

		sprintf(txtline, "%s %s", pkg.name, pkg.giturl);

		fputs(txtline, pkglist);

		if(fputs == NULL)
		{
			printf("Something failed :(\n");
		}
		else
		{
			printf("Successfully added %s to pkglist.\n", pkg.name);
		}

                //This is where tuk program will check if the package name exists under /etc/tuk
		//Currently working on getting git to work, may not function properly

		//git_libgit2_init();
	
		//git_error_last();

		//char command[1024];
		//sprintf(command, "git clone %10s", argv[2]);
		//system(command);
		
		return 0;
        }
	// As of now, this section is formatted horribly
        if(strcmp(argv[1], "--help")==0) {
		printf("System update		tuk update\n"); 
		printf("Updates/reinstalls a package		tuk -S [package] \n");
		printf("Removes a package		tuk -R [package]\n");
		printf("Displays this page		tuk --help\n");
		printf("Adds a package              tuk addpkg [package] [giturl]\n");
		return 0;
	}
}

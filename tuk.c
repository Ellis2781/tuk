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
		if(argc<3) 
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
				printf("'%s' does not exist in pkglist. Please use the addpkg flag or add the package to pkglist manually.\n", pkg.name);
				return 1;
			}
			
			//then it stores the name into pkg.name and url into pkg.giturl

			////check online directory with libcurl to see if it already has a makefile if possible.
			
			//git clone
			printf("Checking for a Makefile...\n");

			git_libgit2_init();			

			git_repository *repo = NULL;
	
			//until the pkglist reading is finished, this will be a set link for the giturl.
		
			printf("Downloading src...\n");	
	
			sprintf(pkg.giturl, "https://github.com/Ellis2781/tuk");

			sprintf(pkg.directory, "usr/src/%s", pkg.name);

			if(fopen(pkg.directory, "r") != NULL)
			{
				//this will add the new directory to the pkglist file but for now this is still in working
				

				//setting a static variable so that it's only available here
				static int i = 1;

				//adding "-" to the pkg directory to avoid - getting printed over and over again in the loop because the loop will run atleast once. 
				//Without this directory names could be something like bash-1-2-3-4-5-6-7-8, this just isn't what is wanted.

				static char temp[100];

				sprintf(temp, pkg.directory);

				sprintf(pkg.directory, "%s-", pkg.directory);
				
				//It took a "while" to get this loop running
				while(fopen(temp, "r") != NULL)
				{
					printf("%s exists, checking another directory\n", temp);
					
					//adds one to the end of the package directory so if the first directory isn't found then it adds one to see if the next directory name exists and if it doesn't then it creates that directory and uses that in the pkg struct.
				
					//char *pkgp = pkg.directory;

					sprintf(temp, "%s%d", pkg.directory, i);
	
					//sprintf(pkg.directory, "%s%d", pkg.directory, i);

					i = ++i;
				}
				//adds the value of temp back to pkgdirectory after the loop is over
				sprintf(pkg.directory, temp);
			}
			
			printf("Using %s as package directory.\n", pkg.directory);

			//Error handling
			if(git_clone(&repo, pkg.giturl, pkg.directory, NULL) != 0)
			{
				
				printf("The git clone has failed. Returning 1.\n");

				printf(giterr_last()->message);
				printf("\n");

				//Prints the last error provided by git
				return 1;
			}

			

			//checks the directory from pkg.directory for the makefile

			//stores arg 2 into the pkg struct

			//checks if the package name is the name of a valid package

			char makefile[100];
			
			sprintf(makefile, "%s/Makefile", pkg.directory);

			if(fopen(makefile, "r") == NULL) 
			{
				printf("Makefile doesn't exist in %s\n", pkg.directory);
			}
			else 
			{
				static char command[20] = "make -C";
				sprintf(command, "%s %s", command, pkg.directory);
				printf("Found Makefile, executing make\n");
				//system(command);
				if(system(command) != 0)
				{
					printf("Something failed, returning 1.\n");
					return 1;
				}
				printf("%s was successfully built.\n", pkg.name);
				return 0;			
			}
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

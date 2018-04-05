#include <stdio.h>


#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>


int createDirAndFiles(char *projectName, char *languageType, char *licenseType, int git)
{	
	/* buffer to handle the current directory */
	char currentDir[256];
	
	/* 
	 * using POSIX API to get the current directory and dump it to the buffer 
	 * char *getcwd(char *buf, size_t size);
	 *
	 */
	getcwd(currentDir, sizeof(currentDir));

	/* concatentate the current directory with a slash (/) to append the project name */
	strcat(currentDir, "/");
	strcat(currentDir, projectName);
	
	/* 
	 * using POSIX API to make a directory with an access mode equals to : 770 
	 * int mkdir(const char *path, mode_t mode); 
	 *
	 * */
	mkdir(currentDir, 0770);

	/* using a main, license, and makefile buffers to create those files */
        char main[512];
        char license[512];
        char makefile[512];
	
	/* copy the current directory to main, license and makefile buffer */
        strncpy(main, currentDir, sizeof(currentDir));
        strncpy(license, currentDir, sizeof(currentDir));
        strncpy(makefile, currentDir, sizeof(currentDir));
	
	/* check if languageType is NULL or no to create the proper main file and copy the right content */

	FILE *main__ = NULL;
	if (languageType != NULL){
        	if (strcmp(languageType, "-C") == 0) {
			main__ = fopen("../initdevs/sources/main.c", "r");
			strcat(main, "/main.c");
		}
	        else if (strcmp(languageType, "-Py") == 0) {
			main__ = fopen("../initdevs/sources/main.py", "r");
			strcat(main, "/main.py");
		}
        	else if (strcmp(languageType, "-Latex") == 0) {
			main__ = fopen("../initdevs/sources/latexMin.tex", "r");
			strcat(main, "/main.tex");
		}
	        else if (strcmp(languageType, "-CPP") == 0) {
			main__ = fopen("../initdevs/sources/main.cpp", "r");
			strcat(main, "/main.cpp");
		}
        	else if (strcmp(languageType, "-C++") == 0) {
			main__ = fopen("../initdevs/sources/main.cpp", "r");
			strcat(main, "/main.cpp");
		}
	        else if (strcmp(languageType, "-BEAMER") == 0) {
			main__ = fopen("../initdevs/sources/beamer.tex", "r");
			strcat(main, "/main.tex");
		}
	}
	else {
		strcat(main, "/main");
	}
        
        strcat(license, "/LICENSE");
        strcat(makefile, "/Makefile");

	/* create the three files */
	FILE *license_ = fopen(license, "w+");
	FILE *make = fopen((const char*)makefile, "w");
	FILE *main_file = fopen((const char*)main, "w");

	/* if we opened the correct file, then copy its content to main file */
	if (main__ != NULL){
		char c = fgetc(main__);	
		while (c != EOF){
			fputc(c, main_file);
			c = fgetc(main__);
		}
	}

	/* Fill the license with the proper terms and leave it blank when not specified */
	FILE *fptr_license;
	if (licenseType != NULL){
		if (strcmp(licenseType, "-GPL") == 0 || strcmp(licenseType, "-MIT") == 0){
			if (strcmp(licenseType, "-GPL") == 0)
				fptr_license = fopen("../initdevs/licenses/GPL", "r");
			else 
				fptr_license = fopen("../initdevs/licenses/MIT", "r");
			char c = fgetc(fptr_license);	
			while (c != EOF){
				fputc(c, license_);
				c = fgetc(fptr_license);
			}
		}
	}	
	
	/* If the git bit is set, we check if the language type is provided and provided correctly, else an error is raised */
	if (git){
		char gitignore_buffer[512];
		strncpy(gitignore_buffer, currentDir, sizeof(currentDir));
		strcat(gitignore_buffer, "/.gitignore");
		FILE *gitignore = fopen((const char*)gitignore_buffer, "w+");

		FILE *git;
		if (!(strcmp(languageType, "-C"))){
			git = fopen("../initdevs/gitignores/c", "r");
		}
		else if (!(strcmp(languageType, "-CPP")) || !(strcmp(languageType, "-C++"))){
			git = fopen("../initdevs/gitignores/cpp", "r");
		}
		else if (!(strcmp(languageType, "-Py"))){
			git = fopen("../initdevs/gitignores/python", "r");
		}
		else if (!(strcmp(languageType, "-Latex")) || !(strcmp(languageType, "-BEAMER"))){
			git = fopen("../initdevs/gitignores/tex", "r");
		}
		char c = fgetc(git);	
		while (c != EOF){
			fputc(c, gitignore);
			c = fgetc(git);
		}		
	}

        return 0;
}

/* Check the spelling of the language */
int is_language_correct(char *arg){
	 if(strcmp(arg,"-C") &&  
            strcmp(arg,"-CPP") &&
            strcmp(arg,"-C++") &&
            strcmp(arg,"-Py") &&
            strcmp(arg,"-Latex") &&
            strcmp(arg,"-BEAMER"))
	{
		return 1;
	}
	return 0;
}

/* Check the spelling of the license */
int is_license_correct(char *arg){
	if (strcmp(arg,"-GPL") &&
	    strcmp(arg,"-MIT"))
	{
		return 1;
	}
	return 0;
}

/* Check the spelling of the language and the license */
int is_argv_two_correct(char *arg){
	  return is_language_correct(arg) && 
		  is_license_correct(arg);            
}

/* check the spell of git */
int is_argv_git_correct(char *arg){
	if (strcmp(arg, "-git")) return 1;
	return 0;
}





int main(int argc, char **argv){
    /* When there are less than 2 arguments */
    if (argc < 2){
        printf("Expected arguments, please check the help: initdev -help \n");
        return 1;
    }
    if (argc == 2){
        if (strcmp(argv[1], "-help") == 0){
                printf("Initdev: a developer tool that save time by setting up dev Directory\n");
                printf("use: initdev <dev_source_name> [args]\n");
                printf("args:\t\t  -C: C project\n");
                printf("\t\t  -CPP or -C++: C++ project\n");
                printf("\t\t  -Py: Python project\n");
                printf("\t\t  -Latex: Latex project\n");
                printf("\t\t  -BEAMER: BEAMER project\n");
                return 0;
        }
	createDirAndFiles(argv[1], NULL, NULL, 0);
    }
    /* Format: initdev projectName -languageType/-LicenseType */
    else if(argc == 3){ 
        if (is_argv_two_correct(argv[2]))
        {
                printf("Uknown arguments, please check the help: initdev -help");
                return 1;
        }
	/*If the syntax is correct we check whether it is a program or a license argument to handle NULL pointer.*/
	else if(is_license_correct(argv[2])){
		createDirAndFiles(argv[1], argv[2], NULL, 0);
	}
	else {
		createDirAndFiles(argv[1], NULL, argv[2], 0);
	}
        
    }
    /* 
     * Format: initdev projectName -languageType -git 
     * or: initdev projectName -languageType -licenseType
     * */
    else if(argc == 4){
	if (is_language_correct(argv[2]) && is_argv_git_correct(argv[3]))
	{
		printf("Uknown arguments, please check the help: initdev -help");
                return 1;		
	}
	if (is_language_correct(argv[2]) && !is_argv_git_correct(argv[3])){
		printf("You must set Project type, please check the help: initdev -help");
                return 1;		
	}
	if (!is_language_correct(argv[2]) && !is_license_correct(argv[3])){
		createDirAndFiles(argv[1], argv[2], argv[3], 0);		
	}
	else {
		createDirAndFiles(argv[1], argv[2], NULL, 1);
	}

	
    }
    /* Format: initdev projectName -licenseType -languageType -git */
    else if(argc == 5){
 	if(is_language_correct(argv[3]) || is_license_correct(argv[2]) || is_argv_git_correct(argv[4])) {
		printf("Uknown arguments, please check the help: initdev -help");
                return 1;		
	}else {
		createDirAndFiles(argv[1], argv[3], argv[2], 1);
	}
    }

    return 0;
}


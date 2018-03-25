#include <stdio.h>

#ifdef __linux__
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #define LICENSE "LICENSE"
    #define MAKEFILE "Makfile"
#endif

#ifdef __WIN32
    #include <Windows.h>
    #include <WinBase.h>

    int createDirAndFilesWindows(char *languageType, char *projectName){
        char currentDir[256];
        GetCurrentDirectory(sizeof(currentDir), currentDir);
        strcat(currentDir, "\\");
        strcat(currentDir, projectName);

        if(CreateDirectory(currentDir, NULL) == 0){
            printf("Failed to create directory");
            return 1;
        }// TODO: Include details of failure 

        // There is another proper way to do it :-)

        char main[512];
        char license[512];
        char makefile[512];

        strncpy(main, currentDir, sizeof(currentDir));
        strncpy(license, currentDir, sizeof(currentDir));
        strncpy(makefile, currentDir, sizeof(currentDir));

        if (strcmp(languageType, "-C") == 0) {strcat(main, "\\main.c");}
        else if (strcmp(languageType, "-Py") == 0) {strcat(main, "\\main.py");}
        else if (strcmp(languageType, "-Latex") == 0) {strcat(main, "\\main.tex");}
        else if (strcmp(languageType, "-CPP") == 0) {strcat(main, "\\main.cpp");}
        else if (strcmp(languageType, "-C++")) {strcat(main, "\\main.cpp");}
        else if (strcmp(languageType, "-BEAMER") == 0) {strcat(main, "\\main.tex");}
        else strcat(main, "\\main");
        
        strcat(license, "\\LICENSE");
        strcat(makefile, "\\Makefile");

        HANDLE hMain = CreateFile((LPCSTR)main,
                                    GENERIC_READ | GENERIC_WRITE,
                                    0,
                                    NULL,
                                    1, //Create new file if the a file with a same name exists
                                    FILE_ATTRIBUTE_NORMAL,
                                    NULL);

        HANDLE hLicense = CreateFile((LPCSTR)license,
                                    GENERIC_READ | GENERIC_WRITE,
                                    0,
                                    NULL,
                                    1, //Create new file if the a file with a same name exists
                                    FILE_ATTRIBUTE_NORMAL,
                                    NULL);
        /* Create a license */    
        //TODO: Copy the appropriate License Terms to LICENSE FILE..

        BYTE buffer[1024 * 50];
        DWORD nNumberofBytesWritten;
        if  (strcmp(languageType, "-GPL") == 0){
            //Garbage to test
            //strncpy(licenseText, "This program is free software: you can redistribute it and/or modify\rit under the terms of the GNU General Public License as published bythe Free Software Foundation, version 3.\n\rThis program is distributed in the hope that it will be useful, but\nWITHOUT ANY WARRANTY; without even the implied warranty of\nMERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU\rGeneral Public License for more details.\n\nYou should have received a copy of the GNU General Public License\nalong with this program. If not, see \n\n", sizeof(licenseText));
        } else if (strcmp(languageType, "-MIT") == 0){
            //Garbage to test
            //strncpy(licenseText, "The MIT License\n\nCopyright \n\nPermission is hereby granted, free of charge, to any person obtaining a copy\nof this software and associated documentation files, to deal\nin the Software without restriction, including without limitation the rights\nto use, copy, modify, merge, publish, distribute, sublicense, and/or sell\ncopies of the Software, and to permit persons to whom the Software is\nfurnished to do so, subject to the following conditions:\n\nThe above copyright notice and this permission notice shall be included in\nall copies or substantial portions of the Software.\n\nTHE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\nIMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\nFITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE\nAUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\nLIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\nOUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN\nTHE SOFTWARE.\n", sizeof(licenseText));
        }
        

        /* Makefile creation */
        HANDLE hMakefile = CreateFile((LPCSTR)makefile,
                                    GENERIC_READ | GENERIC_WRITE,
                                    0,
                                    NULL,
                                    1, //Create new file if the a file with a same name exists
                                    FILE_ATTRIBUTE_NORMAL,
                                    NULL);
        return 0;
    }
#endif


int main(int argc, char **argv){
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
        #ifdef __linux__
            mkdir(argv[1], 0770);
        #endif

        #ifdef __WIN32
            createDirAndFilesWindows(NULL, argv[1]);
        #endif
    }else if(argc == 3){
        if (strcmp(argv[2],"-C") &&  
            strcmp(argv[2],"-CPP") &&
            strcmp(argv[2],"-C++") &&
            strcmp(argv[2],"-Py") &&
            strcmp(argv[2],"-Latex") &&
            strcmp(argv[2],"-BEAMER") &&
            strcmp(argv[2],"-GPL") &&
            strcmp(argv[2],"-MIT"))
        {
                printf("Uknown arguments, please check the help: initdev -help");
                return 1;
        }
        createDirAndFilesWindows(argv[2], argv[1]);
    }
    //TODO: Handle initdev with 4 args.
    
    return 0;
}
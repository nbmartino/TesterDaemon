/**
 * C program to copy contents of one file to another.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define DEST_PATH "/Users/a1234/Documents/testerd/scripts/"
#define FNAME_SRC_FILE_PATH "/Users/a1234/Documents/testerd/gen_files/filenames.txt"
#define TMPL_SRC_FILE_PATH "/Users/a1234/Documents/testerd/scripts/TEMPLATE.ksh"

int main()
{

    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    FILE *sourceFile;
    FILE *destFile;
    char destPath[256];
    char destFilename[256];

    char ch;

    printf("Script Generator\n");
    fp = fopen(FNAME_SRC_FILE_PATH, "r");
    if (fp == NULL)
    {
        printf("fp == NULL \n");
        exit(EXIT_FAILURE);
    }

    sourceFile = fopen(TMPL_SRC_FILE_PATH, "r");
    strcpy(destPath,"");

    while ((read = getline(&line, &len, fp)) != -1)
    {
        strcpy(destPath,DEST_PATH);
        strcpy(destFilename,"");
        printf("Retrieved line of length %zu:\n", read);
        printf("line: %s\n", line);
        strcpy(destFilename, strtok(line, "\n"));
        printf("destFilename: %s\n", destFilename);
        /* sprintf(destPath,"%s/%s",DEST_PATH,line); */
        strcat(destPath,destFilename);
        
        /*
         * Open source file in 'r' and
         * destination file in 'w' mode
         */
        
        printf("\ndestPath: %s\n", destPath);
        
        destFile = fopen(destPath, "w");

        /* fopen() return NULL if unable to open file in given mode. */
        if (sourceFile == NULL || destFile == NULL)
        {
            /* Unable to open file hence exit */
            printf("\nUnable to open file.\n");
            printf("Please check if file exists and you have read/write privilege.\n");

            exit(EXIT_FAILURE);
        }

        fseek(sourceFile, 0, SEEK_SET);

        /*
         * Copy file contents character by character.
         */
        ch = fgetc(sourceFile);
        while (ch != EOF)
        {
            /* Write to destination file */
            fputc(ch, destFile);

            /* Read next character from source file */
            ch = fgetc(sourceFile);
        }

        printf("\nFiles copied successfully.\n");

        /* Finally close files to release resources */
       
        fclose(destFile);
    }  /* while */

    fclose(sourceFile);

    fclose(fp);
    /* if (line)
        free(line);
        
    if (destPath)
        free(destPath); */

    return 0;
}
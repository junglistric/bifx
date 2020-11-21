#include <stdio.h>
#include <stdlib.h>


int main(int argc, const char * argv[]) {

        char *inFilename, *outFilename;
        char ch;
        int nbytes = 100;
        FILE *infp, *outfp;
        
        printf("Enter the name of the input file:");
        getline(&inFilename,&nbytes,stdin);
        size_t len = strlen(inFilename);
        len -= 1;
        char *inFile = (char *)malloc(len);
        memcpy(inFile,inFilename,len);
        printf("What would you like to save it as?");
        getline(&outFilename,&nbytes,stdin);
        size_t len2 = strlen(outFilename);
        len2 -= 1;
        char *outFile = (char *)malloc(len2);
        memcpy(outFile,outFilename,len2);

        //open the file
        infp = fopen(inFile,"r");
        if (infp == NULL)
        {
            printf("File %s not found.\n", inFile);
            return EXIT_FAILURE;
        }

        outfp = fopen(outFile,"r");
        if(outfp){
            fclose(outfp);
            
            printf("File %s already exists.  Overwite? [y/n]", outFile);
            ch = getchar();
            while (ch != 'y' && ch != 'n')
            {
                printf("Please type y or n:");
                ch = getchar();
            }
            if (ch == 'n'){
                fclose(infp);
                return EXIT_SUCCESS;
            }
        }
        
        outfp = fopen(outFile,"w");
        if(outfp == NULL)
        {
            printf("Unable to save file.\n");
            return EXIT_FAILURE;
        }
        
        ch = getc(infp);
        while(ch != EOF){
            if (isalpha(ch)){
                printf("%c",ch);
                if (putc(ch,outfp) == EOF)
                {
                    printf("Error writing file.\n");
                    fclose(infp);
                    fclose(outfp);
                    return EXIT_FAILURE;
                }
            }
            ch = getc(infp);
        }
        
        fclose(infp);
        fclose(outfp);
        printf("File saved.\n");
        
        return EXIT_SUCCESS;
    }
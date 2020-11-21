#include <stdlib.h>
#include <stdio.h>

char* getWord(char * ,FILE *, int *);
char* findSequence(char *, FILE *);
void writeSequence(char *,char *,char *, FILE *);

int main(int argc, const char * argv[]) {
    FILE *infp;
    FILE *haplotype;
    FILE *outfp;
    char word[100];
    int *a;
    char haplogroup[100];
    char polymorphism[100];
    char sequence[11];
    char* temp;
    char ch;
    
    infp = fopen("mtDNA-rCRS.txt", "r");
    if (infp == NULL)
    {
        printf("File not found.\n");
        return EXIT_FAILURE;
    }
    
    haplotype = fopen("A.txt","r");
    if (infp == NULL)
    {
        printf("File not found.\n");
        return EXIT_FAILURE;
    }

    outfp = fopen("A.fasta","w");
    if(outfp){
        fclose(outfp);
        
        printf("File already exists.  Overwrite? [y/n]");
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
     
    temp = getWord(word,haplotype,a);
    memcpy(haplogroup,&temp,sizeof(*temp));
    while ((getc(haplotype) != EOF))
    {
               temp = getWord(word, haplotype, a);
               if (*a < 10)
               {
                   memcpy(polymorphism,&temp,sizeof(*temp));
                   temp = findSequence(polymorphism,infp);
                   writeSequence(temp,haplogroup,polymorphism,outfp);
               }
               else if (*a > 100)
               {
                   memcpy(haplogroup,&temp,sizeof(*temp));
               }
    }
    
    fclose(infp);
    fclose(outfp);
    fclose(haplotype);
    printf("File saved.\n");
    
    return EXIT_SUCCESS;
}

char* getWord(char* word,FILE *file, int * a)
{
    char ch;
    *a = 0;
    bool found = false;
    while (found == false)
    {
        while ((ch = getc(file)) != EOF)
        {
            //find the beginning of the word
            if (isalnum(ch) || ch == '\'' || ch == '!' || ch == ')' || ch == '(' || ch == '.' || ch == '-')
            {
                found = true;
                //while the word continues
                while(ch != ' ' || ch != EOF)
                {
                    ch = word[*a];
                    ++*a;
                    ch = getc(file);
                }
            word[*a] = '\0';
            }
        }
    }
return word;
}

char* findSequence(char *  polymorphism, FILE * infp)
{
    int a = 0;
    int b = 0;
    int c = 0;
    char ch;
    string position[20000];
    while (!isdigit(polymorphism[a]))
    {
        a++;
    }
    while(isdigit(polymorphism[a]))
    {
        position[b] = polymorphism[a];
        a++;
        b++;
    }
    int pos = stoi(*position,NULL,10);
    pos -= 5;
    for (int i = 1; i < pos; i++)
    {
        ch = getc(infp);
    }
    for (int i = pos; i < pos + 18; i++)
    {
        ch = getc(infp);
        polymorphism[c] = ch;
    }
    return polymorphism;
}

void writeSequence(char* sequence, char * polymorphism, char * haplogroup, FILE *outfp)
{
    fputs(">A | ",outfp);
    fputs(haplogroup,outfp);
    fputs(" | ", outfp);
    fputs(polymorphism,outfp);
    fputs("\n",outfp);
    fputs(sequence,outfp);
    fputs("\n\n",outfp);
}

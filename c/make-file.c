#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>

void generate_fixed_file(char* file_path, char * buffer,long int file_size);

int main(int argc, char* argv[])
{
    if (argc != 2) {
        printf("Usage: %s <file_size_in_bytes>\n", argv[0]);
        return 1;
    }

    //char* file_path = argv[1];
    long int file_size = atol(argv[1]);


    char dirname[50];
    char filename[50];
    char file_path[50];

    if (file_size <= 0) {
        printf("Error: invalid file size specified.\n");
        return 1;
    }

    char hex[]="0123456789abcdef";

    char* buffer = (char*)malloc(file_size);

    for (long int i = 0; i < file_size; i++) {
        buffer[i] = (char)(0);
    }
    for (int i=0;i<=15;i++){
        for (int j=0;j<=15;j++){
            sprintf(dirname,"./out/%c%c",hex[i],hex[j]);
            mkdir("./out",0755);
            mkdir(dirname,0755);
            for (int p=0;p<=15;p++){
                for (int q=0;q<=15;q++){
                    sprintf(file_path,"./out/%c%c/%c%c%c%c",hex[i],hex[j],hex[i],hex[j],hex[p],hex[q]);
                    generate_fixed_file(file_path, buffer,file_size);
                }
            }
            printf("complete-%c%c\n",hex[i],hex[j]);
        }
    }

    free(buffer);

    return 0;
}

void generate_fixed_file(char* file_path, char* buffer, long int file_size)
{
    FILE* fp = fopen(file_path, "wb");

    if (fp == NULL) {
        printf("Error: could not open file for writing.");
        exit(1);
    }

    fwrite(buffer, 1, file_size, fp);

    fclose(fp);
}


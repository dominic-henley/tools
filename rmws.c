#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_SIZE 1000
#define REALLOC_SIZE 1000

void remove_whitespace(char *buf, int size);
void print_char_arr(char *arr, int size);

int main(int argc, char *argv[]){
    FILE *fp;
    char c;
    int i = 0;
    int curr_size = INITIAL_SIZE; // the initial size of our buffer array

    if(argc == 1){
        printf("No file provided! Please provide a file to remove whitespace.\n");
        printf("Usage: give one file as input to remove whitespace\n");
        return 0;
    }else if(argc > 2){
        printf("Too many files!\n");
        printf("Usage: give one file as input to remove whitespace\n");
        return 0;
    }else{
        fp = fopen(argv[1], "r+");
        if(fp == NULL){ // error reading file
            printf("Error reading file!\n");
            printf("Exiting...!\n");
            exit(0);
        }

        char *buf = (char *)malloc(sizeof(char) * INITIAL_SIZE); // create a buffer for 1000 characters
        while((c = (char)fgetc(fp)) != EOF){
            if(i == curr_size){
                curr_size = curr_size + REALLOC_SIZE;
                buf = (char *)realloc(buf, curr_size);
                if(buf == NULL){
                    printf("Error reallocating buffer!\n");
                    printf("Exiting...!\n");
                    free(buf);  
                    exit(0);
                }
            }
            buf[i++] = c;
        }
        remove_whitespace(buf, i);
        printf("%s\n", buf);
        free(buf);
    }
    return 0;
}

void remove_whitespace(char buf[], int size){
    char str[size]; // placeholder for string with whitelines removed
    int i;
    int counter = 0;
    for(i = 0; i < size; i++){
        if(buf[i] == ' ' || buf[i] == '\n' || buf[i] == '\t'){
        }else{
            str[counter++] = buf[i];
        }
    }
    str[counter] = '\0';    // make the final char of the buffer a null byte to signal the end of a string
    strcpy(buf, str);
}

// debug function
void print_char_arr(char *arr, int size){
    int i;
    for(i = 0; i < size; i++){
        printf("char %d: %c\\ascii: %d\n", i, arr[i], arr[i]);
    }
}

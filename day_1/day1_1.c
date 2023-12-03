#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"

#define path "input.txt"
#define LINE_LENGTH 100
#define NUM_NUMBERS 9
#define DEFAULT_POSITION (-1)
#include <time.h>

const char *NUMBER_STRINGS[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

char *strrstr(char *str, const char *substr) {
    char *last = NULL;
    if (*substr == '\0') {
        return str;
    }
    while ((str = strstr(str, substr)) != NULL) {
        last = str;
        str++;
    }
    return last;
}

long getPositionFirst(char *buffer, const char *numberString) {
    char *position = strstr(buffer, numberString);
    return (position == NULL) ? DEFAULT_POSITION : position - buffer;
}

long getPositionLast(char *buffer, const char *numberString) {
    char *position = strrstr(buffer, numberString);
    return (position == NULL) ? DEFAULT_POSITION : position - buffer;
}

void getPositions(char *buffer, long firstPositions[], long lastPositions[]) {
    for (int x = 0; x < NUM_NUMBERS; x++) {
        firstPositions[x] = getPositionFirst(buffer, NUMBER_STRINGS[x]);
        lastPositions[x] = getPositionLast(buffer, NUMBER_STRINGS[x]);
    }
}

int main(){
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    FILE * fp = fopen(path,"r");
    if(fp == NULL){
        perror("ERROR");
        return EXIT_FAILURE;
    }

    long total=0;
    char *buffer = malloc(LINE_LENGTH * sizeof(char));
    char numberRetrievedFromOneLine[3];
    while(fgets(buffer, LINE_LENGTH,fp)){
        int firstPositionDigit=100;
        int lastPositionDigit=-100;
        long firstPositionWritten=100;
        long lastPositionWritten=-100;
        for(int x=0;x<LINE_LENGTH;x++){
            if(isdigit(buffer[x])){
                if(firstPositionDigit == 100){
                    firstPositionDigit=x;
                }
                lastPositionDigit=x;
            }
        }
        long firstPositions[9];
        long lastPositions[9];
        getPositions(buffer,firstPositions,lastPositions);
        int raz=0;
        int rez=0;
        for(int x=0;x<9;x++){
            if(firstPositionWritten >= firstPositions[x] && firstPositions[x] != -1){
                firstPositionWritten=firstPositions[x];
                raz=x+1;
            }
            if(lastPositionWritten < lastPositions[x] && lastPositions[x] != -1){
                lastPositionWritten=lastPositions[x];
                rez=x+1;
            }
        }
        if(firstPositionWritten<=firstPositionDigit){
            char test[2];
            sprintf(test, "%d", raz);
            numberRetrievedFromOneLine[0]=test[0];
        }
        else numberRetrievedFromOneLine[0]=buffer[firstPositionDigit];
        if(lastPositionWritten>=lastPositionDigit){
            char test[2];
            sprintf(test, "%d", rez);
            numberRetrievedFromOneLine[1]=test[0];
        }
        else numberRetrievedFromOneLine[1]=buffer[lastPositionDigit];
        numberRetrievedFromOneLine[2]='\0';
        long test = strtol(numberRetrievedFromOneLine,NULL,10);
        printf("%ld\n",test);
        total = total + test;
        memset(buffer,0,LINE_LENGTH);
        memset(numberRetrievedFromOneLine,0, sizeof(numberRetrievedFromOneLine));
    }
    free(buffer);
    printf("%ld",total);
    fclose(fp);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("The runtime of the program is: %f seconds or %f milliseconds\n", cpu_time_used, cpu_time_used * 1000);
    return EXIT_SUCCESS;
}
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <time.h>
#define path "input.txt"
#define LINE_LENGTH 200
#define TICK(X) clock_t X = clock()
#define TACK(X) printf("time %s: %g sec.\n", (#X), (double)(clock() - (X)) / CLOCKS_PER_SEC)


int main(){
    TICK(TIME_A);
    FILE * fp = fopen(path,"r");
    if(fp == NULL){
        perror("ERROR");
        return EXIT_FAILURE;
    }

    char *buffer = malloc(LINE_LENGTH * sizeof(char));
    int total=0;
    long nScratchingCards[205][1]={};
    for (size_t i = 0; i < 205; ++i) {
        nScratchingCards[i][0] = 1;
    }
    while(fgets(buffer, LINE_LENGTH,fp)){
        buffer[strlen(buffer)-1]='\0';
        long currentCard = strtol(&buffer[5],NULL,10);
        char *buffer1Token;
        char *buffer2Token;
        char *buffer2=&buffer[9];
        char *bufferCopy = strdup(buffer2);
        buffer1Token= strtok(bufferCopy,"|");
        buffer2=&buffer[41];
        bufferCopy = strdup(buffer2);
        buffer2Token=strtok(bufferCopy," ");
        int nMatchingNumbers=0;
        int totalPerCard=0;
        while(buffer2Token){
            char *test = buffer1Token;
            size_t needleLength = strlen(buffer2Token);
            while((test= strstr(test,buffer2Token))!= NULL){
                if(buffer1Token[test-buffer1Token-1]!=' ' || buffer1Token[test-buffer1Token+needleLength]!=' '){
                    test++;
                } else{
                    break;
                }
            }
            if(test){
                if(strtol(test,NULL,10) == strtol(buffer2Token,NULL,10)){
                    nMatchingNumbers++;
                    if(totalPerCard==0){
                        totalPerCard++;
                    }else{
                        totalPerCard = (totalPerCard << 1);
                    }
                }
            }
            buffer2Token= strtok(NULL," ");
        }
        long calc=nScratchingCards[currentCard-1][0];
        for(size_t x=0;x<nMatchingNumbers;x++){
            nScratchingCards[currentCard+x][0]+=calc;
        }

        free(bufferCopy);
        if(totalPerCard!=0) {
            total = total + totalPerCard;
        }

    }
    long total2=0;
    for (size_t i = 0; i < 205; ++i) {
        total2=total2+nScratchingCards[i][0];
    }
    printf("%d\n",total);
    printf("%ld\n",total2);
    free(buffer);
    fclose(fp);
    TACK(TIME_A);
    return EXIT_SUCCESS;
}
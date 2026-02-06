/* 
------------------------------------
Student Name: Fortune Nzobigeza
Student ID: 3131442
Submission Date: February 21st 2026
File Name: scheduling.c
------------------------------------
*/

//Remember to close the file, and free memory

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

 int read_my_file(char* filename){
    FILE *fptr=NULL;
    fptr = fopen(filename, "r");


    if (fptr == NULL) {
        printf("Usage: ./sched --policy=FCFS|RR [--quantum=N] --in=FILE\n");
        return 1;
    }
    //char *file_line=malloc(256*sizeof(char));
    //char c=fgetc(fptr);
    
    while (!feof(fptr)){
        char c=fgetc(fptr);
        if (c != -1 ) printf("%c",c);
    }
    //printf("\n");
    //what if you used fscanf since you know you will get three numbers so the formatting would be "%d %d %d",n1,n2,n3
    return 0;
 }


int main(int argc, char *argv[]) {
    if (argc < 3 || argc > 4 ) {
        fprintf(stderr,
            "Usage: ./sched --policy=FCFS|RR [--quantum=N] --in=FILE\n",
            argv[0]);
        return 1;
    }

    //First Come First Serve
    if (strcmp(argv[1], "--policy=FCFS") == 0) {
        
        int filename_len = (int) strlen(argv[2])-5;
        char* filename = malloc((filename_len+1)*sizeof(char)); //don't include "--in="
        char* test=malloc(sizeof(char)*6);
        if (!filename) return 1;
        if (!test) return 1;
        //check first 5 chars
        for (int i=0; i<5;i++){
            *(test+i)=argv[2][i];
        }

        if (strcmp(test,"--in=")!=0){
            fprintf(stderr,
                "Usage: ./sched --policy=FCFS|RR [--quantum=N] --in=FILE\n",
                argv[0]);
            return 1;
        }

        //take filename
        for (int i=5,y=0; i<filename_len+5;i++,y++){
            *(filename+y)=argv[2][i];
        }
        //printf("filename -> '%s'\n",filename);

        //test if argv[2] is not --in=blah

        read_my_file(filename);
    } 
    
    //Round Robin
    else if (strcmp(argv[1], "--policy=RR") == 0) {
        if (argc != 4) {
            fprintf(stderr,
                "Usage: ./sched --policy=FCFS|RR [--quantum=N] --in=FILE\n",
                argv[0]);
            return 1;
        }

        //Checking --quantum
        
        int quantum_str_len = (int) strlen(argv[2])-10;
        char* quantum = malloc(sizeof(char)*(quantum_str_len+1));
        char* test=malloc(sizeof(char)*11);
        if (!test) return 1;
        //check first 10 chars
        for (int i=0; i<10;i++){
            *(test+i)=argv[2][i];
        }

        if (strcmp(test,"--quantum=")!=0){
            fprintf(stderr,
                "Usage: ./sched --policy=FCFS|RR [--quantum=N] --in=FILE\n",
                argv[0]);
            return 1;
        }

        for (int i=10,y=0; i<quantum_str_len+10;i++,y++){
            if (!isdigit(argv[2][i])){
                fprintf(stderr,
                    "Usage: ./sched --policy=FCFS|RR [--quantum=N] --in=FILE\n",
                    argv[0]);
                return 1;
            }
            
            *(quantum+y)=argv[2][i];
            //printf("argv[2][i] -> '%d'\n",argv[2][i]);
            
        }

        //printf("before quantum=%c\n",*quantum);
        int int_quantum=atoi(quantum);
        //printf("after quantum=%d\n",int_quantum);


        //Checking --in
        int filename_len = (int) strlen(argv[2])-5;
        char* filename = malloc((filename_len+1)*sizeof(char)); //don't include "--in="
        char* test2=malloc(sizeof(char)*6);
        if (!filename) return 1;
        if (!test2) return 1;
        //check first 5 chars
        for (int i=0; i<5;i++){
            *(test2+i)=argv[3][i];
        }

        if (strcmp(test2,"--in=")!=0){
            fprintf(stderr,
                "Usage: ./sched --policy=FCFS|RR [--quantum=N] --in=FILE\n",
                argv[0]);
            return 1;
        }

        //take filename
        for (int i=5,y=0; i<filename_len+5;i++,y++){
            *(filename+y)=argv[3][i];
        }
        //printf("filename -> '%s'\n",filename);

        //test if argv[2] is not --in=blah

        read_my_file(filename);

       
    } 
    
    else {
        fprintf(stderr, "Usage: ./sched --policy=FCFS|RR [--quantum=N] --in=FILE\n", argv[1]);
        return 1;
    }

    return 0;
}
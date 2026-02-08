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

void print_error(){
    printf("Usage: ./sched --policy=FCFS|RR [--quantum=N] --in=FILE\n");
}

int retrieve_quantum(int quantum_str_len, char* quantum, char* str){
    for (int i=10,y=0; i<quantum_str_len+10;i++,y++){
        if (!isdigit(str[i])){
            print_error();
            return 1;
        }
        
        *(quantum+y)=str[i];
        //printf("str[i] -> '%d'\n",str[i]);
    }

    return 0;
}

void retrieve_filename(int filename_len, char* filename, char* str){
    
    for (int i=5,y=0; i<filename_len+5;i++,y++){
        *(filename+y)=str[i];
    }
}
int verify_argument(char* str, int argument_len){

    char* test = malloc(sizeof(char)*6);
    if (!test) return 1;

    for (int i=0; i<argument_len;i++) *(test+i)=str[i];
    printf("test='%s'",test);
    // "--in="
    if (argument_len==5){
        if (strcmp(test,"--in=")!=0){
            print_error();
            return 1;
        }
    }

    // "--quantum="
    else if (argument_len==10){
        if (strcmp(test,"--quantum=")!=0){
            print_error();
            return 1;
        }
    }

    free(test);
    return 0;
}


int read_my_file(char* filename){
    FILE *fptr=NULL;
    fptr = fopen(filename, "r");


    if (fptr == NULL) {
        printf("Filename does not exist\n"); 
        return 1;
    }
    //char *file_line=malloc(256*sizeof(char));
    //char c=fgetc(fptr);

    //either realloc memory everytime
    
    while (!feof(fptr)){
        char c=fgetc(fptr);
        if (c != -1 ) printf("%c",c); 
    }
    //printf("\n");
    //what if you used fscanf since you know you will get three numbers so the formatting would be "%d %d %d",n1,n2,n3

    //don't forget to close file
    fclose(fptr);
    return 0;
}

int read_file(char* filename){
    FILE *fptr=NULL;
    fptr = fopen(filename, "r");

    if (fptr == NULL) {
        printf("Filename does not exist\n"); 
        return 1;
    }
    int pid=0, arrival=0, cpu_time=0, ret_val=1;
    int count=0;
    char c=0;
    printf("At Whiteloop \n");
    while (1){ //loop kinda works when there are no hashtags and other formats at the beginning
        count++;
        ret_val=fscanf(fptr,"%d %d %d",&pid,&arrival,&cpu_time);
        
        printf("ret_val='%d'\n",ret_val);
        if (feof(fptr) || count==10){break;}
        if (ret_val!=3){
            while (c!=10){
                c=fgetc(fptr);
            }
            
        }
        else {
            printf("pid='%d'\narrival='%d'\ncpu_time='%d'\n",pid,arrival,cpu_time);
        }
    }

    fclose(fptr);
    return 0;
}

void fcfs_sim(){

}

int main(int argc, char *argv[]) {

    // --- Only 3 or 4 arguments --- //
    if (argc < 3 || argc > 4 ) {
        print_error();
        return 1;
    }

    // --- Option 1: First Come First Serve --- //
    if (strcmp(argv[1], "--policy=FCFS") == 0) {
        
        // - Must be 3 arguments - //
        if (argc != 3){
            print_error();
            return 1;
        }
        printf("hello1\n");
        // - Verify filename argument - //
        if (verify_argument(argv[2],5)){
            print_error();
            return 1;
        }

        printf("hello2\n");
        // - Retrieve Filename - //
        int filename_len = (int) strlen(argv[2])-5; //don't include "--in="
        char* filename = malloc((filename_len+1)*sizeof(char)); 
        if (!filename) return 1;

        retrieve_filename(filename_len, filename, argv[2]);

        //printf("filename -> '%s'\n",filename);

        //test if argv[2] is not --in=blah

        //read_my_file(filename);
        read_file(filename);
        free(filename);
    } 
    
    // --- Option 2: Round Robin --- //
    else if (strcmp(argv[1], "--policy=RR") == 0) {
        
        // - Must be 4 arguments - //
        if (argc != 4) {
            print_error();
            return 1;
        }
        printf("hello3\n");
        // - Verify Quantum Argument - //
        if (verify_argument(argv[2],10)) {return 1;}

        printf("hello4");
        // - Retrieve Quantum - //
        int quantum_str_len = (int) strlen(argv[2])-10;
        char* quantum = malloc(sizeof(char)*(quantum_str_len+1));
        if (!quantum) return 1;
        
        if (retrieve_quantum(quantum_str_len,quantum,argv[2])) {return 1;}
        printf("hello5");
        //printf("before quantum=%c\n",*quantum);
        int int_quantum=atoi(quantum);
        free(quantum);
        //printf("after quantum=%d\n",int_quantum);

        // - Verify filename argument - //
        if (verify_argument(argv[3],5)) {return 1;}
        printf("hello6\n");
        // - Retrieve filename - //
        int filename_len = (int) strlen(argv[3])-5;
        char* filename = malloc((filename_len+1)*sizeof(char)); //don't include "--in="
        if (!filename) return 1;

        retrieve_filename(filename_len,filename,argv[3]);
        printf("filename -> '%s'\n",filename);

        //test if argv[2] is not --in=blah

        read_my_file(filename);
        free(filename);
    } 
    
    // --- Error with 1st agrument --- //
    else {
        print_error();
        return 1;
    }

    return 0;
}
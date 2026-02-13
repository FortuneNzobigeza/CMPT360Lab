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

int is_hashtag(char c){
    if (c==35) {return 1;}
    return 0;
}

int is_new_line(char c){
    if (c==10) {return 1;}
    return 0;
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

//Make sure to verify the format of the workload files; shoot an error if it's not in the right format
int read_file(char* filename, int* processes, int* pids, int* arrivals, int* cpu_times, int amt_process){
    FILE *fptr=NULL;
    fptr = fopen(filename, "r");

    if (fptr == NULL) {
        printf("Filename does not exist\n"); 
        return 1;
    }
    int ret_val=1;
    char c=0;
    int process=0; //amount of lines in file that is a process
   
    printf("At Whileloop \n");
    while (1){ //loop kinda works when there are no hashtags and other formats at the beginning
        if (feof(fptr)) {return 0;}

        c=fgetc(fptr);
        printf("\n--Found Character: >%c<\n",c);
        if (c==-1){
            break;
        }

        while (isblank(c)){
            c=fgetc(fptr);
        }

        if (is_hashtag(c)||is_new_line(c)){ 
            while(!is_new_line(c)) {c=fgetc(fptr);}
            continue;
        }

        else if (!isdigit(c)){
            printf("Error! Formatting is wrong");
            return 1;
        }

        else {
            //make a function to retrieve all the numbers, maybe pass the numbers as pointers and set the values
            //also i will probably need to set up the pointers in main since i will need them later
            //thinking of making a struct to hold the 3 variables together. I have to remember that each row will be combined to create the simulation
            
            //remember that i want to use scanf was the pid is found (just to simply everything lol)
            int value_size=1;
            char* value = malloc(value_size*sizeof(char));
            
            for (int i=0; i!=-1;i++){ //i wanted the 'i' variable
                
                value[i]=c;
                c=fgetc(fptr);
                if (isdigit(c)){
                    value_size++;
                    value=realloc(value,value_size*sizeof(char));
                    continue;
                }
                else if (isblank(c)){ 
                    if (process==amt_process){
                        amt_process++;
                        pids=realloc(pids,amt_process*sizeof(int)); 
                    }
                    pids[process]=atoi(value);
                    
                    free(value);
                    
                    ret_val=fscanf(fptr,"%d %d",arrivals+process,cpu_times+process);
                    if (ret_val!=2){
                        printf("Error! Formatting is wrong");
                        return 1;
                    }
                    printf("pid='%d'\narrival='%d'\ncpu_time='%d'\n",*(pids+process),*(arrivals+process),*(cpu_times+process));
                    break;
                }
                else{
                    printf("Error! Formatting is wrong");
                    free(value);
                    return 1;
                }
                
            }
            
        }
        process++;
    }
    //printf("pid='%d'\narrival='%d'\ncpu_time='%d'\n",pid,arrival,cpu_time);
    printf("process=%d",process);
    *processes=process;
    fclose(fptr);
    return 0;
}

//checks if a process is finished all its jobs
int is_done(int* process_done, int pid, int done){
    for (int i=0; i<done; i++){
        if (process_done[i]==pid){
            return 1;
        }
    }
    return 0;
}

//returns total time
int print_time(int* cpu_times, int* process,int* arrivals, int* pids){
    int current_value=-1;
    int current=0;
    int count_done=0;
    int* process_done = malloc ((*process)*sizeof(int));
    
    
    for (int y=0;y<*process;y++){
        if (arrivals[y]>current_value && !is_done(process_done,pids[y],count_done)){
            current=y;
            current_value=arrivals[y];
            break;
        }
    }
    int time=arrivals[current]+cpu_times[current];
    for (int i=1;i<*process;i++){
        if (time>=arrivals[i]){
            time+=cpu_times[i];
        }
        else{
            time+=(arrivals[i]-time);
            time+=cpu_times[i];
        }
    }
    
// arrivaltime+cpu_time=new_arrival_time
// I was thinking of making 2 arrays; each index represents a process and one array represents 
       

    printf("\ntime: ");
    for (int i=0;i<time;i++){
        printf("%d ",i);
    }
    
    free(process_done);
    return time;
}

void print_stats_fsfc(int* process, int* pids, int* arrivals, int* cpu_times, int* completions, int* first_run_list){
    int amt_of_processes=*process;
    int* all_tat=malloc(amt_of_processes*sizeof(int));
    int* all_rep=malloc(amt_of_processes*sizeof(int));
    int total_ctx_switches= amt_of_processes-1;
    int total_tat=0;
    int total_rep=0;
    for (int i=0;i<amt_of_processes;i++){
        all_tat[i]=completions[i]-arrivals[i];
        //printf("\nall_tat[i]==%d",all_tat[i]);
        total_tat+=all_tat[i];

        //printf("\n--first_run_list[i]=%d\narrivals[i]=%d",first_run_list[i],arrivals[i]);
        all_rep[i]=first_run_list[i]-arrivals[i];
        total_rep+=all_rep[i];
        //printf("\nall_rep[i]==%d",all_rep[i]);

        printf("\nP%d: first run=%d completion=%d TAT=%d RESP=%d",pids[i],first_run_list[i],completions[i],all_tat[i],all_rep[i]);
        //P0: first run=0 completion=4 TAT=4 RESP=0
    }
    double avg_tat =  ((double) total_tat/ (double) amt_of_processes);
    double avg_rep =  ((double) total_rep/ (double) amt_of_processes);
    //printf("\namt_of_processes=%d\ntotal_tat=%d\ntotal_rep=%d",amt_of_processes,total_tat,total_rep);
    printf("\nSystem: ctx_switches=%d, avgTAT=%f, avgRESP=%f\n",total_ctx_switches,avg_tat,avg_rep);
    //System: ctx_switches=2, avgTAT=4.667, avgRESP=2.000

    
}

void new_fcfs(int* process, int* pids, int* arrivals, int* cpu_times, int* completions, int* first_run_list, int* total_time_available){
    int total_time=*total_time_available;
    
    int current_value=total_time+1;
    int current=0;

    int count_done=0;

    int* process_done = malloc((*process)*sizeof(int));
    int* process_order = malloc(total_time*sizeof(int));
    for (int i=0;i<total_time;i++){
        process_order[i]=-1;
    }

    for (int i=0;i<*process;i++){

        //determine which process gets a turn
        //is it smaller? And is it done?
        for (int y=0;y<*process;y++){
            //printf("\n---y=%d\narrivals[y]=%d\ncurrent_value=%d",y,arrivals[y],current_value);
            
            if (arrivals[y]<current_value && !is_done(process_done,pids[y],count_done)){
                current=y;
                current_value=arrivals[y];
                //printf("inside if");
            }
            else if (is_done(process_done,pids[current],count_done)){
                current=y;
                current_value=arrivals[y];
            }
        }
        
        //printf("\n--current=%d",current);

        int start=0;
        int burst=cpu_times[current];
        int first_run=0;
        int completion_marker=0;
        for (int time=0;time<total_time;time++){
            
            if (time==arrivals[current]){
                start=1;
            }
            if (start && burst && process_order[time]==-1){
                if (!first_run){
                    first_run=1;
                    first_run_list[current]=time;
                    
                }
                process_order[time]=pids[current];
                burst--;
                
            }
             if (!burst&!completion_marker){
                    completion_marker=1;
                    completions[current]=time+1;
                }
            
            //printf("\ntimeslot >%d<\n",time);
            //printf("process id >%d<\n\n",process_order[time]);
        }


        process_done[i]=pids[current];
        count_done++;
        


    }

    printf("\nrun : ");
    for (int i=0;i<total_time;i++){
        if (process_order[i]==-1){
            printf("- ");
        }
        else{
            printf("%d ",process_order[i]);
        }
    }

   
    // for (int i=0;i<*process;i++){
    //     printf("\nPD%d \n started at:%d \n done at: %d\n",pids[i],first_run_list[i],completions[i]);
    // }
    free(process_done);
    free(process_order);
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
        
        printf("hello1");
        
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
        
        
        int amt_process = 1;
        int process=0; //amount of lines in file that is a process
        
        int* pids=malloc(amt_process*sizeof(int)); //first position is pid 0, then pid 1 then so on..
        int* arrivals=malloc(amt_process*sizeof(int));
        int* cpu_times=malloc(amt_process*sizeof(int));
        
        read_file(filename,&process,pids,arrivals,cpu_times,amt_process);
        int* completions=malloc(process*sizeof(int));
        int* first_run_list=malloc(process*sizeof(int));
        free(filename);


        printf("\n===========================================\n");
        int total_time=print_time(cpu_times, &process, arrivals, pids);
        new_fcfs(&process,pids,arrivals,cpu_times,completions,first_run_list,&total_time);
        //printf("\nAddress to first_run_list: %d",first_run_list[1]);
        //printf("\nAddress to arrivals: %d",arrivals[1]);
        print_stats_fsfc(&process,pids,arrivals,cpu_times,completions,first_run_list);
        printf("\n===========================================\n");
        
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
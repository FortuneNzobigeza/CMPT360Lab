/* 
------------------------------------
Student Name: Fortune Nzobigeza
Student ID: 3131442
Submission Date: February 21st 2026
File Name: scheduling.c
------------------------------------
*/

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr,
            "Usage: ./sched --policy=FCFS|RR [--quantum=N] --in=FILE\n",
            argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "--policy=FCFS") == 0) {
        
    } 
    
    else if (strcmp(argv[1], "--policy=RR") == 0) {
        if (argc != 4) {
            fprintf(stderr,
                "Usage: ./sched --policy=FCFS|RR [--quantum=N] --in=FILE\n",
                argv[0]);
            return 1;
        }
        
    } 
    
    else {
        fprintf(stderr, "Usage: ./sched --policy=FCFS|RR [--quantum=N] --in=FILE\n", argv[1]);
        return 1;
    }

    return 0;
}
/*Author: Salwa Abougamila
Course: CMPT 360, Winter 2026
Lab1: process_controller.c*/


#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

// fork + exec demonstration (wc)

void run_exec(void) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return;
    }

    if (pid == 0) {
        // Child: prevent wc from blocking on stdin
        freopen("/dev/null", "r", stdin);

        execlp("echo", "echo", "child replaced by exec", NULL);

        // Only reached if exec fails 
        perror("execlp");
        _exit(1);
    }

    wait(NULL);
    printf("exec demo complete\n");
}


 // PID / PPID demonstration 

void run_pid(void) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return;
    }

    if (pid == 0) {
        printf("Child: PID=%d PPID=%d\n", getpid(), getppid());
    } else {
        printf("Parent: PID=%d ChildPID=%d\n", getpid(), pid);
        wait(NULL);
    }
}

// exit vs _exit demonstration

void run_exit(void) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return;
    }

    if (pid == 0) {
        printf("Child exiting with status 42\n");
        exit(42);   // performs stdio cleanup 
    } else {
        int status;
        wait(&status);

        if (WIFEXITED(status)) {
            printf("Parent received exit status %d\n",
                   WEXITSTATUS(status));
        }
    }
}

//Signal demonstration (SIGTERM)

void run_signal(void) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return;
    }

    if (pid == 0) {
        printf("Child waiting for signal...\n");
        while (1) {
            pause();
        }
    } else {
        sleep(1);
        printf("Parent sending SIGTERM\n");
        kill(pid, SIGTERM);
        wait(NULL);
        printf("Signal demo complete\n");
    }
}


// Main controller

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr,
            "Usage: %s [--exec | --pid | --exit | --signal]\n",
            argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "--exec") == 0) {
        run_exec();
    } else if (strcmp(argv[1], "--pid") == 0) {
        run_pid();
    } else if (strcmp(argv[1], "--exit") == 0) {
        run_exit();
    } else if (strcmp(argv[1], "--signal") == 0) {
        run_signal();
    } else {
        fprintf(stderr, "Unknown option: %s\n", argv[1]);
        return 1;
    }

    return 0;
}

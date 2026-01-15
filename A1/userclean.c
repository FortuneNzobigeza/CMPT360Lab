#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]){

    if (argc<2){
        return 0; //if no arguments are passed, do nothing
    }
    int username_count=argc-1;

    for (int i=0;username_count>i;i++){
        char* username_for_test=argv[i];
        printf("%s",username_for_test);
    }

}


int is_reserved_name(){


}
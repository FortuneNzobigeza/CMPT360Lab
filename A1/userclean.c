#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//references: 
// teacher's notes for calloc, https://www.tutorialspoint.com/c_standard_library/c_function_calloc.htm
// https://www.geeksforgeeks.org/c/strcmp-in-c/
// https://www.ascii-code.com/
// https://www.tutorialspoint.com/c_standard_library/ctype_h.htm
// https://www.tutorialspoint.com/c_standard_library/c_function_realloc.htm

int main(int argc, char* argv[]){

    if (argc<2){
        return 0; //if no arguments are passed, do nothing
    }
    int username_count=argc;

    for (int i=1;username_count>i;i++){

        char* trial_username = calloc(strlen(argv[i])+1,sizeof(char));
        if (!trial_username){return 1;}

        

        strcpy(trial_username,argv[i]); //used notes from my cmpt201 teacher to get this idea

        //TEst
        printf("\nUsername I'm working with >%s< and its %d letters long\n",trial_username,strlen(argv[i]));
        printf("\nfirst letter I'm working with >%c<\n",*trial_username);
        printf("\nnext letter I'm working with >%c<\n",*(trial_username+1));
        //

        if (!test_first_letter(*trial_username)){
                printf("\nNON-FIRST LETTER DETECTED");
                free(trial_username);
                return 0;
            }

        transform_specials(trial_username);
        printf("Word {%s}\n",trial_username);
        transform_lowercase(trial_username);
        printf("Word {%s}\n",trial_username);
        transform_underscore(trial_username);
        printf("Word {%s}\n",trial_username);
        
            
        if (is_reserved_name(trial_username)){
                printf("\nRESERVED NAME DETECTED");
                free(trial_username);
                return 0;
            }
        
       
        


        free(trial_username);

    }

}

int test_first_letter(int c){
    if (!isalpha(c)){
        return 0;
    }
    return 1;
}
int is_reserved_name(char* username){
    
    if (strcmp(username, "root")==0 || strcmp(username, "admin")==0)
        return 1;
    return 0;
}



void transform_lowercase(char* username){
    for (int i=0;strlen(username)>i;i++){
        *(username+i)=tolower(*(username+i));
    }
}

void transform_underscore(char* username){
    for (int i=0;strlen(username)>i;i++){
        if(isspace(*(username+i))){
            (*(username+i))=95;
        }
    }
}

void transform_specials(char* username){
    char* new_name = calloc(strlen(username)+1,sizeof(char));
        if (!new_name){return;}

    int count = 0;
    int offset=0;
    
    for (int i=0; i<strlen(username);i++){
        if (isalnum(*(username+i)) || isspace(*(username+i))){
            *(new_name+i-offset)=*(username+i);
            count++;
            
        }

        else{
            offset++;
        }
        
    }

    strcpy(username,new_name);
    realloc(username, count*sizeof(char));

    free(new_name);

    
}

//void grow_username(char* username)

//void shrink_username(char* username)

//void print_username(char* username)


// ---


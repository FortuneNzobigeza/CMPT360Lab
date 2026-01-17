#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//References: 
// teacher's notes for calloc &  https://www.tutorialspoint.com/c_standard_library/c_function_calloc.htm
// https://www.geeksforgeeks.org/c/strcmp-in-c/
// https://www.ascii-code.com/
// https://www.tutorialspoint.com/c_standard_library/ctype_h.htm
// https://www.tutorialspoint.com/c_standard_library/c_function_realloc.htm
// https://stackoverflow.com/questions/8440816/message-warning-implicit-declaration-of-function (I was wondering why their were so many warnings saying implicit declaration)
// https://www.tutorialspoint.com/cprogramming/c_input_output.htm (getchar and fgets)

//Prototypes
int obtain_username(char* username);
int test_first_letter(int c); 
int is_reserved_name(char* username);
void transform_lowercase(char* username, int name_size);
void transform_underscore(char* username, int name_size);
void transform_specials(char* username, int name_size);

//Main
int main(){
    
    char* trial_username = calloc(17,sizeof(char));
    if (!trial_username) {return 1;} 

    int name_size=obtain_username(trial_username);
    
    
    
    // if ((fgets(trial_username,sizeof(trial_username),stdin))==NULL){
    //     printf("returns nothing\n");
    //     return 0;
    // };
    
    
    
    //strcpy(trial_username,input_name); //used notes from my cmpt201 teacher to get this idea

    //TEst
    printf("\nUsername I'm working with >%s< and its %d letters long\n",trial_username,name_size);
    //printf("\nfirst letter I'm working with >%c<\n",*trial_username);
    //printf("\nnext letter I'm working with >%c<\n",*(trial_username+1));
    //

    if (!test_first_letter(*trial_username)){
            printf("%s : invalid and unfixable\n",trial_username);
            free(trial_username);
            return 1;
        }

    transform_specials(trial_username,name_size);
    //printf("Word {%s} \n",trial_username);
    transform_lowercase(trial_username,name_size);
    //printf("Word {%s}\n",trial_username);
    transform_underscore(trial_username,name_size);
    //printf("Word {%s}\n",trial_username);
    
        
    if (is_reserved_name(trial_username)){
            printf("%s : invalid and unfixable\n",trial_username);
            free(trial_username);
            return 1;
        }
    
    printf("%s : %s\n",trial_username,trial_username);
    free(trial_username);

    

}


int obtain_username(char* username){

    int name_size = 0;
    char letter;

    while (1) {
        letter=getchar();
        printf("letter: %c, %d\n", letter, letter);
        if (letter<32){ //All ASCII codes below 32 cause the loop to break
            printf("name_size: %d\n",name_size);
            break;}

        *(username+name_size)=letter;
        name_size++;
    }

    return name_size;
}

int test_first_letter(int c){
    if (!isalpha(c)) 
        return 0;
    return 1;
}

int is_reserved_name(char* username){ 
    if (strcmp(username, "root")==0 || strcmp(username, "admin")==0)
        return 1;
    return 0;
}

void transform_lowercase(char* username, int name_size){
    for (int i=0;name_size>i;i++){
        *(username+i)=tolower(*(username+i));
    }
}

void transform_underscore(char* username, int name_size){
    for (int i=0;name_size>i;i++){
        if(isspace(*(username+i))){
            (*(username+i))=95;
        }
    }
}

void transform_specials(char* username, int name_size){
    char* new_name = calloc(name_size+1,sizeof(char));
        if (!new_name){return;}

    int count = 0;
    int offset=0; //if "ad^m" program won't stop at "ad"
    
    for (int i=0; i<name_size;i++){
        if (isalnum(*(username+i)) || isspace(*(username+i))){
            *(new_name+i-offset)=*(username+i);
            count++;   
        }

        else{
            offset++;
        }
    }

    strcpy(username,new_name);
    free(new_name);
}

//void grow_username(char* username)

//void shrink_username(char* username)

//void print_username(char* username)


// ---


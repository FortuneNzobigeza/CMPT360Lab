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
int transform_specials(char* username, int name_size);
void realloc_str(char* str1, char* str2, int size);
int shrink_username(char* username, int name_size);

//Main
int main(){
    
    char* original_username = calloc(17,sizeof(char));
    if (!original_username) {return 1;} 

    int name_size=obtain_username(original_username);
    
    char* new_username = calloc(name_size+1,sizeof(char));
    strcpy(new_username,original_username); //used notes from my cmpt201 teacher to get this idea
    
    
    // if ((fgets(new_username,sizeof(new_username),stdin))==NULL){
    //     printf("returns nothing\n");
    //     return 0;
    // };
    

    //TEst
    printf("\nUsername I'm working with >%s< and its %d letters long\n",new_username,name_size);
    //printf("\nfirst letter I'm working with >%c<\n",*new_username);
    //printf("\nnext letter I'm working with >%c<\n",*(new_username+1));
    //

    if (!test_first_letter(*new_username)){
            printf("%s : invalid and unfixable\n",new_username);
            free(new_username);
            return 1;
        }
    
    
    name_size=shrink_username(new_username,name_size);
    //name_size=transform_specials(new_username,name_size);
    //printf("Word {%s} \n",new_username);
    transform_lowercase(new_username,name_size);
    //printf("Word {%s}\n",new_username);
    transform_underscore(new_username,name_size);
    //printf("Word {%s}\n",new_username);
    
    
        
    if (is_reserved_name(new_username)){
            printf("%s : invalid and unfixable\n",new_username);
            free(new_username);
            return 1;
        }
    
    printf("%s : %s\n",original_username,new_username);
    free(new_username);

    

}


int obtain_username(char* username){

    int name_size = 0;
    char letter;

    while (1) {
        letter=getchar();
        printf("letter: %c, %d\n", letter, name_size);
        if (letter<32){ //All ASCII codes below 32 or username reaches limit, cause the loop to break
            printf("name_size: %d\n",name_size);
            break;}
        else if (name_size>15){
            printf("name_size lol: %d\n",name_size);
            username = realloc(username, sizeof(char)*strlen(username)+1);
        }
        *(username+name_size)=letter;
        name_size++;
    }
    printf("namesize: %d, strlen: %d",name_size,strlen(username));
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

int transform_specials(char* username, int name_size){
    char* new_name = calloc(name_size+1,sizeof(char));
    if (!new_name){return name_size;}

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

    realloc_str(username,new_name,count);
    free(new_name);

    return count;
}

//void grow_username(char* username)

int shrink_username(char* username, int name_size){
    int max_size=16;

    char* new_name = calloc(name_size+1,sizeof(char));
    if (!new_name){return name_size;}
    
    if (name_size>max_size){
        for (int i=0; i!=max_size;i++){
            *(new_name+i)=*(username+i);
        }
    }
    
    realloc_str(username,new_name,max_size);
    free(new_name);

    return max_size;
}

void realloc_str(char* str1, char* str2, int size){
    str1=realloc(str1, size*sizeof(char)+1);
    strcpy(str1,str2);
}
//void print_username(char* username)


// ---


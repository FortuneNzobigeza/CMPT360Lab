/* 
------------------------------------
Student Name: Fortune Nzobigeza
Student ID: 3131442
Submission Date: January 24th 2026
File Name: userclean.c
------------------------------------
*/

// -- Libraries -- //
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// -- Prototypes -- //
int obtain_username(char* username, int* EOF_finder);
int test_first_letter(int c); 
int is_reserved_name(char* username);
void transform_lowercase(char* username, int name_size);
void transform_underscore(char* username, int name_size);
int remove_specials(char* username, int name_size);
void realloc_str(char* str1, char* str2, int size);
int shrink_username(char* username, int name_size, int max_size);
int grow_username(char* username, int name_size, int min_size);

/*
Function Name: main
Purpose: To Sanitize Usernames
Parameters: None
Returns: returns 1 if errors were found. Otherwise, 0 is returned.
*/
int main(){

    int max_size=16; // Maximum Characters for Each Username
    int min_size=3;  // Minimum Characters for Each Username
    
    int* EOF_finder=calloc(1,sizeof(int));
    if (!EOF_finder) return 1;
    *EOF_finder=1; // Used to turn loop off if there are no more usernames in a file

    while (*EOF_finder){
        
        // --- Retrieve Username --- //
        char* original_username = calloc(max_size+1,sizeof(char));
        if (!original_username) return 1;

        int name_size=obtain_username(original_username,EOF_finder);

        if (*EOF_finder==0 && name_size==0){
            free (original_username);
            free (EOF_finder);
            return 0;
        }

        char* new_username = calloc(name_size+1,sizeof(char));
        if (!new_username) return 1; 

        strcpy(new_username,original_username); //used notes from my cmpt201 teacher to get this idea
        
        // --- Username Tranformations --- //
        
        if (!test_first_letter(*new_username)){
            printf("%s : invalid and unfixable\n",original_username);  
        }

        

        else{

            name_size=remove_specials(new_username,name_size);

            if (name_size>max_size){
                name_size=shrink_username(new_username,name_size,max_size);
            }

            if (name_size<min_size){
                name_size=grow_username(new_username,name_size,min_size);
            }
            
            transform_lowercase(new_username,name_size);
            transform_underscore(new_username,name_size);

            if (is_reserved_name(new_username)){
                printf("%s : invalid and unfixable\n",original_username);
            }

            else{
            printf("%s : %s\n",original_username,new_username);
            }
        }
        
        free(new_username);
        free(original_username);
    }
    
    free(EOF_finder);
    return 0;
}


/*
Function Name: obtain_username
Purpose: Retrieve's username from standard input
Parameters: 
    username - a string buffer to save the username
    EOF_finder - pointer to an integer.
Returns: returns the size of the username
*/
int obtain_username(char* username, int* EOF_finder){
    int name_size = 0;
    char letter;

    while (1) {
        letter=getchar();
        
        if (letter<32){ //All ASCII codes below 32 or username reaches limit, cause the loop to break
            if (letter==-1) *EOF_finder=0;
            break;
        }
        
        else if (name_size>15){
            username = realloc(username, sizeof(char)*strlen(username)+1);
        }
        *(username+name_size)=letter;
        name_size++;
    }

    return name_size;
}


/*
Function Name: test_first_letter
Purpose: Check whether a character is a letter
Parameters: 
    c - ASCII code for character
Returns: Returns 0 if the character is not a letter. Otherwise, returns 1.
*/
int test_first_letter(int c){
    if (!isalpha(c)) return 0;
    return 1;
}


/*
Function Name: is_reserved_name
Purpose: Verifies if the username is a reserved username (i.e. "admin" or "root")
Parameters: 
    username - the username to be verified
Returns: Returns 0 if the username is not a reserved name. Otherwise, returns 1.
*/
int is_reserved_name(char* username){ 
    if (strcmp(username, "root")==0 || strcmp(username, "admin")==0)
        return 1;
    return 0;
}


/*
Function Name: transform_lowercase
Purpose: Transforms each uppercase letter from a username into lowercase
Parameters: 
    username - the username to be changed
    name_size - the length of the username
Returns: None
*/
void transform_lowercase(char* username, int name_size){
    for (int i=0;name_size>i;i++){
        *(username+i)=tolower(*(username+i));
    }
}


/*
Function Name: transform_underscore
Purpose: Transforms any spaces in a username to underscore
Parameters: 
    username - the username to be changed
    name_size - the length of the username
Returns: None
*/
void transform_underscore(char* username, int name_size){
    for (int i=0;name_size>i;i++){
        if(isspace(*(username+i))){
            (*(username+i))=95;
        }
    }
}


/*
Function Name: remove_specials
Purpose: Removes any special characters from the username
Parameters: 
    username - the username to be changed
    name_size - the length of the username
Returns: returns the size of the username
*/
int remove_specials(char* username, int name_size){
    char* new_name = calloc(name_size+1,sizeof(char));
    if (!new_name) return name_size;

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


/*
Function Name: grow_username
Purpose: Increase the size of the username
Parameters: 
    username - the username to be changed
    name_size - the length of the username
    min_size - the minimum length for usernames
Returns: returns the size of the username
*/
int grow_username(char* username, int name_size, int min_size){
    int fill_amt=min_size-name_size;
    username=realloc(username, min_size*sizeof(char)+1);
    strncat(username, "user", fill_amt);

    return name_size+fill_amt;
}


/*
Function Name: shrink_username
Purpose: Reduce the size of a username
Parameters: 
    username - the username to be changed
    name_size - the length of the username
    max_size - the maximum length for usernames
Returns: returns the size of the username
*/
int shrink_username(char* username, int name_size, int max_size){
    char* new_name = calloc(name_size+1,sizeof(char));
    if (!new_name) return name_size;
    
    if (name_size>max_size){
        for (int i=0; i!=max_size;i++){
            *(new_name+i)=*(username+i);
        }
    }
    
    realloc_str(username,new_name,max_size);
    free(new_name);

    return max_size;
}


/*
Function Name: realloc_str
Purpose: Replace one string with another string
Parameters: 
    str1 - 1st String (will be replaced)
    str2 - 2nd string 
    size - the length of str2
Returns: None
*/
void realloc_str(char* str1, char* str2, int size){
    str1=realloc(str1, size*sizeof(char)+1);
    strcpy(str1,str2);
}
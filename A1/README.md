# CMPT 360 - A1
Name: Fortune Nzobigeza
ID: 3131442 
Due Date: Jan 24th 2026

# 1. Academic Integrity
“I certify that this submission represents entirely my own work.”

# 2. Overview
This Code is used to sanitize user inputted usernames. If any username is unable to be fully sanitized, program will state as such.

Username Specifications:
    Each Username must only contain:
        - Lowercase Letters (i.e. a-z)
        - Digits (i.e. 0-9)
        - Underscores (i.e. "_")

    No username is allowed to be "root" or "admin"

    Each username must start with a lowercase letter and be 3-16 characters in length.

# 3. Build
In order to compile the code, use the command "make"

# 4. Run
Here are some examples of how to run this program (please enter compile the code using "make" first):

Without file
    ./userclean
    echo "Hello World" | ./userclean

With file:
    ./userclean < filename.txt

# 5. Logic Summary
    a. Username is inputted by the user
    b. Username is dynamically allocated onto the heap
    c. Remove any special characters and Adjust username size to be between 3-16 characters
    d. Check if the first character is a letter
    e. Make final transformations (all letters to lowercase, and spaces converted to underscores)
    f. lastly, username is checked to see if it matches any reversed names (i.e. root or admin)

# 6. Status
Code should be working with no known errors.

# 6. Notes / Assumptions
If you want to end the program, simply pretty CTRL+C

References: 
CMPT201 teacher's notes (dynamic allocation, strcpy)
https://www.tutorialspoint.com/c_standard_library/c_function_calloc.htm
https://www.geeksforgeeks.org/c/strcmp-in-c/
https://www.ascii-code.com/
https://www.tutorialspoint.com/c_standard_library/ctype_h.htm
https://www.tutorialspoint.com/c_standard_library/c_function_realloc.htm
https://stackoverflow.com/questions/8440816/message-warning-implicit-declaration-of-function (I was wondering why their were so many warnings saying implicit declaration)
https://www.tutorialspoint.com/cprogramming/c_input_output.htm (getchar and fgets)
https://stackoverflow.com/questions/4034392/makefile-error1
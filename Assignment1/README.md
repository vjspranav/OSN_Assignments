A Collection of 2 codes written using System Calls Q1.c and Q2.c

Q1.c A C Program to Reverse contents of one File and write contents to Other File
    Run by: ./Q1 inputfile
    Creates Output: Assignment/inputfile # With reversed Contents.
    Errors if:
        - Filename is not provided.
        - Provided Filename doesn't exist.
        - If Unable to create directory due to any issue (permission or storage etc..)
        - If a file or symlink or anything other than Directory exists with the name 'Assignment'
    Warnings:
        - If more than one argument is passed the first argument will be considered as filename.
        - If Diectory exists it will be openend and if the input file named output exists it will be overwritten.
    Progress Bar:
        - Is a quirky Hello World being reversed on shell as the content reversing takes place.

Q2.c A C program to compare two files to check whether their contents are exactly reverse of each other or not
    Run by: ./Q2 oldfile newfile directory
    Prints Output: Reversed Successfully or not and permissions of Old/New File and Directory
    Errors if:
        - If no arguments are provided
        - All three arguments are invalid / Don't exist
        - If more than 3 arguments are provided
        -
    Warnings:
        - If either one or both of Old File and New File don't exist, Reversed will be shown as No and Permissions for valid file if any and Directory are printed
        - If Directory is invalid or not exists, the permissions for the files will be printed
    Permissions Printed as:
        '''
        User has read permissions on newfile: Yes
        User has write permission on newfile: Yes
        User has execute permission on newfile: No
        Group has read permissions on newfile: No
        Group has write permission on newfile: No
        Group has execute permission on newfile: No
        Others has read permissions on newfile: No
        Others has write permission on newfile: No
        Others has execute permission on newfile: No
        '''
        For oldfile newfile and directory in respective order.

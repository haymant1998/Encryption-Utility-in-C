#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headerSecure.c"
int main()
{
    clrscr();
    int choice;
    printf ("Enter your choice :\n1) Do you want to encrypt the file? \n2) Do you want to decrypt the file?\n3) Exit..\n");
    scanf ("%d",&choice);
    switch(choice)
    {
        case 1: encrypt();
                break;
        case 2: decrypt();
                break;
        case 3: exit(0);
        default: printf ("Invalid Choice.");
    }
}

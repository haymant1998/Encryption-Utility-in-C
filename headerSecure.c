#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <time.h>

static struct termios old, new;
/* Initialize new terminal i/o settings */
void initTermios(int echo)
{
    tcgetattr(0, &old); /* grab old terminal i/o settings */
    new = old; /* make new settings same as old settings */
    new.c_lflag &= ~ICANON; /* disable buffered i/o */
    if (echo) {
        new.c_lflag |= ECHO; /* set echo mode */
    } else {
        new.c_lflag &= ~ECHO; /* set no echo mode */
    }
    tcsetattr(0, TCSANOW, &new); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void)
{
    tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo)
{
    char ch;
    initTermios(echo);
    ch = getchar();
    resetTermios();
    return ch;
}

/* Read 1 character without echo */
char getch(void)
{
    return getch_(0);
}

/* Read 1 character with echo */
char getche(void)
{
    return getch_(1);
}

void clrscr()
{
    system("clear");
}
/* Let's test it out */

int randomChar()
{
    int ran=rand()%100+1;
    return (ran);
}

FILE* openFileRead(char fname[])
{
    FILE *fps;
    fps=fopen(fname,"r");
    if(fps==NULL){
        printf ("Error in opening file...!!");
        printf ("\n Press any key to exit..");
        getch();
        exit(1);
    }
    return (fps);
}
FILE* openFileWrite(char fname[])
{
    FILE *fps;
    fps=fopen(fname,"w");
    if(fps==NULL)
    {
        printf("Error in opening source file..!!");
        printf("\nPress any key to exit...");
        getch();
        exit(3);
    }
    return (fps);
}
FILE* openTempRead()
{
    FILE *fpt;
    fpt=fopen("temp.txt","r");
    if(fpt==NULL)
    {
        printf("Error in opening temp.txt file...!!");
        printf("\nPress any key to exit...");
        getch();
        exit(4);
    }
    return (fpt);
}
FILE* openTempWrite()
{
    FILE *fpt;
    fpt=fopen("temp.txt","w");
    if(fpt==NULL){
        printf ("Error in opening file...!!");
        printf ("\n Press any key to exit..");
        getch();
        exit(2);
    }
    return (fpt);
}
int getKeyInEncrypt()
{
    long int key=0;
    FILE *fpt;
    char ch;
    fpt=openTempRead();
    while(1){
        ch=fgetc(fpt);
        if(ch==EOF) break;
        else    key=key+ch;
    }
    return (key);
}
void encrypt()
{
    srand(time(NULL));
    char fname[20],ch;
    int tem=randomChar();
    char tempChar=tem;
    FILE *fps,*fpt;
    printf ("Enter file name you want to encrypt.");
    scanf ("%s",fname);
    fps=openFileRead(fname);
    fpt=openTempWrite();
    fputc(tempChar,fpt);
    while(1){
        ch=fgetc(fps);
        if(ch==EOF) break;
        else{
            ch=ch+tem;
            fputc(ch,fpt);
        }
    }
    fclose(fps);
    fclose(fpt);
    fps=openFileWrite(fname);
    fpt=openTempRead();
    while(1)
    {
        ch=fgetc(fpt);
        if(ch==EOF)
        {
            break;
        }
        else
        {
            fputc(ch, fps);
        }
    }
    printf("File %s encrypted successfully..!!", fname);
    printf("Key for this encrypted file is %d. Please keep this safe if you want to decrypt your file", getKeyInEncrypt());
    remove("temp.txt");
    printf("\nPress any key to exit...\n");
    fclose(fps);
    fclose(fpt);
    getch();
}
int fetchKeyInDecrypt(char fname[])
{
    long int key=0;
    FILE *fps;
    char ch;
    fps=openFileRead(fname);
    while(1){
        ch=fgetc(fps);
        if(ch==EOF) break;
        else    key=key+ch;
    }
    return (key);
}
void decrypt()
{
    char ch, choice, fname[20];
    FILE *fps, *fpt;
    printf("Enter file name (with extension like file.txt) which you have encrypted earlier to decrypt : ");
    scanf ("%s",fname);
    
    //Checks if the keys is correct or not
    printf ("\nPlease enter the passcord to decrypt the file..\n");
    long int pass;
    while(1)
    {
        scanf ("%ld",&pass);
        if(pass==fetchKeyInDecrypt(fname)) break;
        else printf ("Incorrect passcord. Please try again.\n");
    }
    
    fps=openFileRead(fname);
    fpt=openTempWrite();
    while(1){
        ch=fgetc(fps);
        if(ch==EOF) break;
        else fputc(ch,fpt);
    }
    fclose(fps);
    fclose(fpt);
    
    
    
    fps=openFileWrite(fname);
    fpt=openTempRead();
    
    char tempChar=fgetc(fpt);
    int tem=tempChar;
    while(1)
    {
        ch=fgetc(fpt);
        if(ch==EOF)
        {
            break;
        }
        else
        {
            ch=ch-tem;
            fputc(ch, fps);
        }
    }
    printf("You have successfully logged in and File %s decrypted successfully..!!",fname);
    printf("\nPress any key to exit...\n");
    fclose(fps);
    fclose(fpt);
    remove("temp.txt");
    getch();
}

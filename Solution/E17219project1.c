/*
******************************************************************************
=====================CO222-Programming Methodology============================
                    ---URL to QR code converter---
                    ----------project 1-----------

Author-Ishara Sandakelum Nawaranthna(K.G.I.S. Nawarathna)
E Number- E/17/219
******************************************************************************
*/

//Including the standard libraries===>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Prototyping Functions===>

//Basic Functions
int * hashs(char array[],int length); //hash code short version
int * hashl(char array[],int length);   //hash code long version
int * bits(int number);     //integer to binary converter

//ANSI related functions
void setLoc(int row,int col);       //cursor location changer
void clearS();      //clearing the terminal screen
void defaultset();      //restoring default ANSI ESC values
void whiteboxes(int numofboxes);        //printing white color boxes
void blackboxes(int numofboxes,int color);      //printing boxes with colors other than white

//Printing the QR code structure functions
void frameS();  //printing frame for the short version
void frameL();  //printing frame for the long version
void isquare(int row,int col,int color);    //printing identification squares
void struS(int color);      //printing the frame and the identification squares for the short version
void struL(int color);      //printing the frame and the identification squares for the long version

//Printing character patterns functions
void charbox(int numarray[],int row,int col,int color); //color pattern for one character
void complementS(char url[],int len,int color);     //character set for the short version
void complementL(char url[],int len,int color);     //character set for the long version

//Functions for printing the whole QR code
void fullS(char url[],int len,int color);   //whole QR code short version
void fullL(char url[],int len,int color);   //whole QR code long version

//Finalized function
void finalQR(int color);   //this function contains whole process of the program

//Argument handling functions
void error(char arg[]);     //printing the error message
void help(char arg[]);      //printing the help message

int main(int argc,char*argv[])
{
    if(argc==1){
        finalQR(40); //executing the default output when there is no flags
    }else if(argc==2){
        if(strcmp(argv[1],"-h")==0){
            help(argv[0]);  //executing the manual massage function for -h flag
        }else {
        error(argv[0]); //executing the error message function
    }
    }else if(argc==3){
        if(strcmp(argv[1],"-c")==0){
            if(strcmp(argv[2],"black")==0 || strcmp(argv[2],"BLACK")==0){
                finalQR(40);        //printing QR code in black
            }else if(strcmp(argv[2],"red" )==0|| strcmp(argv[2],"RED")==0){
                finalQR(41);        //printing QR code in red
            }else if(strcmp(argv[2],"green")==0 || strcmp(argv[2],"GREEN")==0){
                finalQR(42);        //printing QR code in green
            }else if(strcmp(argv[2],"yellow")==0|| strcmp(argv[2],"YELLOW")==0){
                finalQR(43);        //printing QR code in yellow
            }else if(strcmp(argv[2],"blue")==0||strcmp(argv[2],"BLUE")==0){
                finalQR(44);        //printing QR code in blue
            }else if(strcmp(argv[2],"magenta")==0||strcmp(argv[2],"MAGENTA")==0){
                finalQR(45);        //printing QR code in magenta
            }else if(strcmp(argv[2],"cyan")==0||strcmp(argv[2],"CYAN")==0){
                finalQR(46);        //printing QR code in cyan
            }else{
                error(argv[0]);     //executing the error message function
            }
        }else {
            error(argv[0]);     //executing the error message function
        }
    }else{
        error(argv[0]);     //executing the error message function
    }
    return 0;
}

//Basic Functions>>>>>==================================================================================

//This function defines the hash string for short version
int * hashs(char array[],int length){

    char url[21];   //URL
    int output[24];     //this array stores the hashed string before reversing
    static int results[24];     //final result
    int counter1,counter2;      //counters for loop through loops
    int fullrows; //full rows for the error detection part
    int left;   //for the last block of letters
    int lencounter=0;   //full rows counter
    //Assining the values for hashing
    for(counter1=0;counter1<length;counter1++){
        url[counter1] = array[counter1];
        lencounter += 1;
    }

    output[0] = 50 + lencounter;

    results[0] = output[0];

    fullrows = (23 - lencounter)/lencounter;

    left = 23-(lencounter+fullrows*(lencounter));

    //Assigning values for the 1st part
    for(counter1=1;counter1<=lencounter;counter1++){
            output[counter1] = url[counter1-1];
            results[counter1] = output[counter1];
    }

    //Assigning values for the 2nd part
    for(counter1=0;counter1<fullrows;counter1++){
        for(counter2=0;counter2<lencounter;counter2++){
            output[(counter1+1)*lencounter+counter2+1] = url[counter2] + (counter1 + 1);
        }
    }

    //Assigning values for the 3rd part
    for(counter1=0;counter1<left;counter1++){
        output[lencounter*(fullrows+1)+counter1+1] = url[counter1] + (fullrows+1);
    }

    //Reversing Process
    for(counter1=0;counter1<(lencounter*fullrows+left);counter1++){
        results[counter1+1+lencounter]=output[23-counter1];
    }

   return results;

}

//This function defines hash string for long version
int * hashl(char array[],int length){

    char url[120];  //URL
    int output[132];    //this array stores the hashed string before reversing
    static int resultl[132];    //final result
    int counter1,counter2;  //counters for loop through loops
    int fullrows; //full rows for the error detection part
    int left;   //for the last block of letters
    int lencounter=0;    //full rows counter
    //Assigning the values for hashing
    for(counter1=0;counter1<length;counter1++){
        url[counter1] = array[counter1];
        lencounter += 1;
    }

    output[0] = 50 + lencounter;

    resultl[0] = output[0];

    fullrows = (131 - lencounter)/lencounter;

    left = 131-(lencounter+fullrows*(lencounter));

    //Assigning values for the 1st part
    for(counter1=1;counter1<=lencounter;counter1++){
            output[counter1] = url[counter1-1];
            resultl[counter1] = output[counter1];
    }

    //Assigning values for the 2nd part
    for(counter1=0;counter1<fullrows;counter1++){
        for(counter2=0;counter2<lencounter;counter2++){
            output[(counter1+1)*lencounter+counter2+1] = url[counter2] + (counter1 + 1);
        }
    }

    //Assigning values for the 3rd part
    for(counter1=0;counter1<left;counter1++){
        output[lencounter*(fullrows+1)+counter1+1] = url[counter1] + (fullrows+1);
    }

    //Reversing Process
    for(counter1=0;counter1<(lencounter*fullrows+left);counter1++){
        resultl[counter1+1+lencounter]=output[131-counter1];
    }

    return resultl;

}

//This function defines binary number for an integer
int * bits(int number){
    static int numarray[9];
    int counter;
    for(counter=0;counter<9;counter++){
         numarray[8-counter]=number%2;
         number = number/2;
    }
    return numarray;
}

//===============================================================================================================


//ANSI RELATED FUNCTIONS>>>>=====================================================================================

//This function sets the cursor to a specified location in the terminal
void setLoc(int row,int col){
    printf("\x1b[%d;%df",row,col);
}
//This function clears the terminal
void clearS(){
    printf("\x1b[2J");
}
//This function sets default ANSI values
void defaultset(){
    printf("\x1b[0m\n");
}
//This function prints a number of white boxes
void whiteboxes(int numofboxes){
    int counter;
    for(counter=0;counter<numofboxes;counter++){
        printf("\x1b[47m  ");
        printf("\x1b[0m");
    }
}
//This function prints a number of black boxes(but the color can be changed in these boxes to red,green and etc.)
void blackboxes(int numofboxes,int color){
    int counter;
    for(counter=0;counter<numofboxes;counter++){
        printf("\x1b[%dm  ",color);
        printf("\x1b[0m");
    }
}
//======================================================================================================================



//Printing the QR code structure functions>>>>==========================================================================

//This function prints the basic frame for the short version
void frameS(){
    int counter;
    clearS();
    for(counter=1;counter<=20;counter++){
        if(counter==1||counter==20){
            setLoc(counter,1);
            whiteboxes(20);
        }else if(counter>1&&counter<20){
            setLoc(counter,1);
            whiteboxes(1);
            setLoc(counter,39);
            whiteboxes(1);
        }
    }
}
//This function prints the basic frame for the long version
void frameL(){
    int counter;
    clearS();
    for(counter=1;counter<=38;counter++){
        if(counter==1||counter==38){
            setLoc(counter,1);
            whiteboxes(38);
        }else if(counter>1&&counter<38){
            setLoc(counter,1);
            whiteboxes(1);
            setLoc(counter,75);
            whiteboxes(1);
        }
    }
}
//This function prints identification square in a specified location
void isquare(int row,int col,int color){
    int counter;
    setLoc(row,col);
    for(counter=1;counter<=6;counter++){
        if(counter==1||counter==6){
            blackboxes(6,color);
        }else if(counter==2||counter==5){
            blackboxes(1,color);
            whiteboxes(4);
            blackboxes(1,color);
        }else if(counter==3||counter==4){
            blackboxes(1,color);
            whiteboxes(1);
            blackboxes(2,color);
            whiteboxes(1);
            blackboxes(1,color);
        }
         setLoc(counter+row,col);
    }
}
//This function prints frame + identification squares for the short version
void struS(int color){
    frameS();
    isquare(2,3,color);
    isquare(14,3,color);
    isquare(2,27,color);
}
//This function prints frame + identification squares for the long version
void struL(int color){
    frameL();
    isquare(2,3,color);
    isquare(32,3,color);
    isquare(2,63,color);
}
//=========================================================================================================================


//Printing character patterns functions>>>>================================================================================

//This function prints the pattern for a character in a specified location
void charbox(int numarray[],int row,int col,int color){
    int counter1,counter2;
    setLoc(row,2*col-1);
    for(counter1=0;counter1<3;counter1++){
        for(counter2=0;counter2<3;counter2++){
            if(numarray[counter1*3+counter2]==1){
                blackboxes(1,color);
            }else{
                whiteboxes(1);
            }
        }
    setLoc(row+counter1+1,2*col-1);
    }
}
//This function prints character pattern for the short version
void complementS(char url[],int len,int color){
    int counter1,counter2;
    //This part prints out the big block of characters(1-16)
    for(counter1=0;counter1<4;counter1++){
        for(counter2=0;counter2<4;counter2++){
            charbox(bits(hashs(url,len)[4*counter1+counter2]),8+3*counter1,8+counter2*3,color);
        }
    }
    //This part prints out the small block of characters(17-20)
    for(counter1=0;counter1<2;counter1++){
        for(counter2=0;counter2<2;counter2++){
            charbox(bits(hashs(url,len)[16+counter1*2+counter2]),2+counter1*3,8+counter2*3,color);
        }
    }
    //This part prints out the small block of characters(21-24)
      for(counter1=0;counter1<2;counter1++){
        for(counter2=0;counter2<2;counter2++){
            charbox(bits(hashs(url,len)[20+counter2*2+counter1]),8+counter2*3,2+counter1*3,color);
        }
    }
}
//This function prints character pattern for the long version
void complementL(char url[],int len,int color){
    int counter1,counter2;
    //This part prints out the big block of characters(1-16)
    for(counter1=0;counter1<10;counter1++){
        for(counter2=0;counter2<10;counter2++){
            charbox(bits(hashl(url,len)[10*counter1+counter2]),8+counter1*3,8+counter2*3,color);
        }
    }
    //This part prints out the small block of characters(17-20)
    for(counter1=0;counter1<2;counter1++){
        for(counter2=0;counter2<8;counter2++){
            charbox(bits(hashl(url,len)[100+counter1*8+counter2]),2+counter1*3,8+counter2*3,color);
        }
    }
    //This part prints out the small block of characters(21-24)
      for(counter1=0;counter1<8;counter1++){
        for(counter2=0;counter2<2;counter2++){
            charbox(bits(hashl(url,len)[116+counter2+counter1*2]),8+counter1*3,2+counter2*3,color);
        }
    }
}
//This function prints QR code for a given URL
void fullS(char url[],int len,int color){
    struS(color);
    complementS(url,len,color);
    setLoc(21,1);
}
//This function prints QR code for a given URL
void fullL(char url[],int len,int color){
    struL(color);
    complementL(url,len,color);
    setLoc(39,1);
}
//===========================================================================================================================


////Finalized function>>>>===================================================================================================

//This function executes the whole functionality of the program for a given color
void finalQR(int color){

    unsigned char url[255];

    printf("Enter the URL: ");
    scanf("%s",url);

    int len = strlen(url);

        if(len<=3){
            printf("String is too short. Not supported by available QR versions");
        }else if(len>3 && len<=20){
            fullS(url,len,color);
        }else if(len>20 && len<120){
            fullL(url,len,color);
        }else if(len>=120){
            printf("String is too long. Not supported by available QR versions");
        }
        defaultset();
}
//=========================================================================================================================


//Argument handling functions>>>>==========================================================================================

//This function prints the error message
void error(char arg[]){
    printf("Incorrect usage of arguments.\n");
    printf("usage :\n");
    printf("%s -c [black|red|green|yellow|blue|magenta|cyan]\n",arg);
    printf("%s -h for the help about the program\n",arg);
}


//This function prints the manual
void help(char arg[]){
    printf("usage :\n");
    printf("%s -c [black|red|green|yellow|blue|magenta|cyan]\n",arg);
    printf("%s -h for the help about the program\n",arg);
}

//==========================================================================================================================


































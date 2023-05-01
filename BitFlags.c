#include <stdio.h> //input and output (pritnf)
#include <stdlib.h> //contains memory management (malloc & free) & atoi

//prior to using a function, we should declare it.
//Note we only need to declare the parameter types, not the paramter names!
void printBits(int);

/*BitFlags - Program to showcase how numbers are represented in binary*/
//Note that in this program, main has two new parameters: argc & argv
//argc stores the number of command line arguments supplied to the program
//argv is a 2-dimension character array (1-dimensional array of strings) that stores the values of the arguments
//argc will ALWAYS be atleast 1, with the first argument being the name used to invoke the program
//EXAMPLE:
// ./Bits 5 10
// argc = 3
// argv[0] = "./Bits"
// argv[1] = "5"
// argv[2] = "10"
int main(int argc, char** argv){

    //If the program is not supplied the correct # of arguments, we end early and print out the usage format
    if(argc != 3){
        printf("[!]USAGE: %s <num1> <num2>\n", argv[0]);
        return 0;
    }
    //The numbers we receive from the command line are strings.
    //atoi converts ascii text (the a) to an integer (the i)
    //other versions exist for other data types, such as atol (ascii to long)
    int num1 = atoi(argv[1]);
    int num2 = atoi(argv[2]);

    printBits(num1);
    printBits(num2);


    printf("[*]%d | %d\n",num1,num2);
    printBits(num1 | num2);
    printf("[*]%d & %d\n",num1,num2);
    printBits(num1 & num2);
    printf("[*]%d ^ %d\n",num1,num2);
    printBits(num1 ^ num2);
    printf("[*]~%d \n",num1);
    printBits(~num1);

    printf("[*]%d || %d\n",num1,num2);
    printBits(num1 || num2);
    printf("[*]%d && %d\n",num1,num2);
    printBits(num1 && num2);
    printf("[*]!%d \n",num1);
    printBits(!num1);


    int shift = num2 % 10;

    printf("[*]%d << %d\n",num1,shift);
    printBits(num1 << shift);
    printf("[*]%d >> %d\n",num1,shift);
    printBits(num1 >> shift);
}

//The definition of printBits
//@param num -> the number to print out the bits for
void printBits(int num){
    int numbits = sizeof(int) * 8; // We use sizeof since we don't assume the size of integers! ;)
    int original = num;
    //below we create a character array (string) to store the bits
    //The call to malloc allocates memory for the string at runtime (rather than at compile time)
    //malloc gives a pointer to the memory allocated (Which in this context is the start of the string/char array)
    char* bits = malloc(sizeof(char) * numbits);
    //for loop populates our character array with either 1 or 0 for a particular digit
    for(int i = 0; i < numbits; i++){
        //since we count up from 0 to numbits, we place the digits in the array in reverse order
        bits[numbits-(1+i)] = (char) num & 1; //bits = 1 if the 1st bit = 1, 0 otherwise
        num = num >> 1;//shift the bits to the right by 1 so we can process the next bit on the following loop
    }
    printf("[*]%d\t",original);//print out the orginal number processed
    printf("(");//formatting :)
    //We go through the array 4 bits at a time to print them
    for(int i = 0; i < numbits; i+=4){
        printf("%d%d%d%d ", bits[i],bits[i+1],bits[i+2],bits[i+3]);
    }
    printf(")\n");

    //C doesn't have garbage collection
    //So since we manually asked for the memory to store the varaible bits
    //We must also manually free up the memory so it can be used later
    free(bits); 
}
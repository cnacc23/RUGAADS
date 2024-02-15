#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n= 0;
char inpString[100]; 
char *input= inpString;

int main(){

    //declare pointer to head of LL
    TransportNode *head= NULL;

    char *sepString, *start, *end, *mode;
    int field= 0; 
    int listLength(head);
          
    // read in stdin 
    while(input != NULL){
        
        scanf("%[^\n]%*c", inpString);

        // read in integer 
        if(n == 0) {
            n= atoi(inpString);
            printf("n %d\n", n);
        // read in transport modes and dates     
        } else {
    
            while((sepString= strsep(&input, " ")) != NULL){
            
                //store each seperated value 
               
                 if(field == 0) {
                    start= sepString;
                      
                } else if(field == 1){
                    end= sepString;
                   
                } else if(field == 2){
                    mode= sepString;                       
                }
                field ++; 

            }

            printf("start %s end %s mode %s\n", start, end, mode);

            //store values in new linked list node 
           addNode(&head, start, end, mode);
        }
    }
    
    printList(head);

    return 0; 
}
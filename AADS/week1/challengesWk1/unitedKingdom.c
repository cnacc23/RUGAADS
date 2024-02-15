#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TransportNode
{
    char startDate[20];
    char endDate[20];
    char *mode;
    struct TransportNode *next;
}TransportNode;


void addNode(TransportNode** head, char *start, char *end, char *tm){

    //allocate memory for new node 
    TransportNode *newEntry= (TransportNode*)malloc(sizeof(TransportNode));

    // add data to new node
    strcpy(newEntry->startDate, start);
    strcpy(newEntry ->endDate, end);
    newEntry->mode= tm;

    //if head is null, new node is head 
    if(*head != NULL) newEntry->next= *head;

    //new node is start of list 
   *head=newEntry;
}

void printList(TransportNode *head){
    TransportNode *current= head;

    while(current != NULL)
    {
        printf(" %s %s %s\n", current->startDate, current->endDate, current->mode);
    }
}

int listLength(TransportNode *head){
    TransportNode *current= head;
    int length;

    while(current != NULL){
        length ++;
        current= current->next;
    }
    return length;
}

void freeList(TransportNode *head){
    TransportNode *current= head;
    
    while(current != NULL){
        free(current);
    }
}



int main() {
    int n, i;
    int field= 0;
    char inputLine[100];
    char *input= inputLine;
    char *sepString, *start, *end, *mode;

    // scan in how many transportation lines to read in
    scanf("%d", &n); 


    //scan in transportation modes 
    for (i = 1; i <= n; i++) {
        
        scanf(" %[^\n]", inputLine);  

        while((sepString = strsep(&input, " ")) != NULL){
            
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
        
    }


    return 0;
}


/*int main(){

    //declare pointer to head of LL
    TransportNode *head= NULL;

    char *sepString, *start, *end, *mode;
    int field= 0; 
    int currLen= listLength(head);
   
    
    //scan in # transports
    scanf("%d", &n); 
    

    for (int i= 1; i <= n; i++){
            scanf("%[^\n]%*c", inpString);

        // read in transport modes and dates     
       
    
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
            // printf("out of while\n");
            //store values in new linked list node 
            //addNode(&head, start, end, mode);
            //printf("%d\n", currLen);
        }
    }
   // printList(head);
    //freeList(head);
    return 0;
           
}*/
    

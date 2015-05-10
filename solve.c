//
//  solve.c
//  Panama Canal Puzzle
//  Created by Isaac Godfried on 11/26/14.
//  Copyright (c) 2014 Isaac Godfried. All rights reserved.
#include <stdio.h>
#include <stdlib.h>
//Data types
typedef struct pnode {
    struct pnode *next;
    struct pnode *back;
    int cost;
    char piece;
    char dir;
    int space;                                      //Position of the space
    char board[12];
} pnode;
typedef struct hashNode
{
    pnode pos;
    struct hashNode *nextStep;

} hashNode;
//Function declarations
int hashNumber(char* word);
void enqueue (struct pnode * position);
pnode * dequeue ();
void swap (char string[12], int a, int b);          //Swaps two board pieces
pnode * hashInsert (pnode newPosition);             //Inserts position into hashtable 
hashNode * newNodeHash(pnode newNod);                //Allocates a new node
int searchHash(pnode * position);                    //Searches hashtable to see if position already exists
void positionWork(pnode *position, int var, char e); //Determines if moves are valid, creates new positions
void printPosition(pnode *position);                 //Prints the solution
int stringCompare(char string1[12], char string2[12]); //Compares to board positions
//Variables
int front = -1;
int rear = -1;
hashNode * hashTable[1000000];
pnode * queu4e[50000];
int main(int argc, const char * argv[]) {
    pnode initialPosition;                              //Enqueue and insert the initial
    initialPosition.cost= 0;
    initialPosition.dir = 'I';
    initialPosition.space = 11;
    char temp[12] ="CanamaPanal ";
    
    for(int i=0; i<12; i++)
    {
        initialPosition.board[i] = temp[i];
    }
    initialPosition.back =NULL;
    pnode* h= hashInsert(initialPosition);
    enqueue(h);
    int x=2;
    while(x==2)
    {

         pnode * position = dequeue();
       
        if (stringCompare(position->board,"PanamaCanal ")==0) {
            x=0;
            printPosition(position);
        }
         int p1;
         int p2;
         int p3;
         int p5;
         char a = 'W';
         char b = 'E';
         char c = 'N';
         char s = 'S';

         p1 = position->space +6;
         p2 = position->space -6;
         p5 = position->space -1;
         p3 = position->space +1;
        
         positionWork(position, p1, c);
         positionWork(position,p2, s);
        if(position->space!=5)
        {
         positionWork(position, p3, a);
        }
        if(position->space!=6)
           {
         positionWork(position, p5, b);
           }
    }
    return 0;
}
int hashNumber(char* word)
{   int sum = 0;
    int i = 0;
    while ( i<12)
    {
        sum+=word[i]*i*i;
        //printf("%d\n", sum);
        i++;
    }
    sum = sum % 500000;
  
    return sum;
}
pnode * hashInsert(pnode newPosition)
{
    int i = hashNumber(newPosition.board);
    hashNode * newNode = newNodeHash(newPosition);
    hashNode *entry = hashTable[i];
    
    //Insert at begining
    if(entry==NULL)
    {
    
        newNode->nextStep =hashTable[i];
        hashTable[i] =newNode;
        return &newNode->pos;
    }
    else
    {   int check = 0;
        while (entry->nextStep!=NULL)                                              //Traverse Hash Table
        {
            entry = entry->nextStep;
            
            
            
        }
        if(check==0)
        {
            newNode->nextStep=entry->nextStep;
            entry->nextStep=newNode;
             return &newNode->pos;
        
            
        }
        else
        {
            return NULL;
        }
        
    }
    
    
    
}
void enqueue (struct pnode * position)
{
    
        if (front == -1 && rear == -1)
    {
        front++; rear++;
    }
    else{
        rear++;
        if(rear==49999)
        {
            rear=0;
        }
    }
    queu4e[rear] = position;
    
    
}
pnode * dequeue()
{;
    
    pnode * temp;
    
    if (front==-1)
    {
        return 0;
    }
    else {
        temp = queu4e[front];
        front++;
        if (front==49999)
        {
            front =0;
        }
        
    }
    return temp;

}
void swap(char string[12], int a, int b)            // Swaps two characters in a string.
{
    char temp = string[a];
    string[a]=string[b];
    string[b]= temp;
    a = b;
    
}
hashNode *newNodeHash(pnode newNod)
{
    struct hashNode*new_node = (struct hashNode *)malloc(sizeof(hashNode));
    new_node->pos =newNod;
    new_node->nextStep =NULL;
    return new_node;
    
}

void positionWork (pnode * position, int var, char e)
{
   
    if (0<=var &&var<12)                            //Check if move is valid
    {
    //Allocate new postion
        pnode newNode;
    newNode = *position;
    int space =newNode.space;
    newNode.board[space]=newNode.board[var];
    newNode.board[var] =' ';
    newNode.cost = position->cost + 1;
    newNode.back=position;
    newNode.space =var;
    newNode.piece = position->board[var];
    newNode.dir = e;
        
    
    if( searchHash(&newNode)==0)
        {
            pnode * c= hashInsert(newNode);
            position->next =c;
            enqueue(c);
        } }

}
int searchHash(pnode * position)
{
    int c = hashNumber(position->board);
    int x = 0;
    hashNode * head;
    head = hashTable[c];
    while(head!=NULL)
    {
    if (stringCompare(head->pos.board,position->board)==0)
    {
        return 1;
    }
        head = head->nextStep;
    }
    
    return x;
}
int stringCompare(char string1[12], char string2[12])
{
    int t = 0;
    for (int i =0; i<12; i++)
    {
        if(string2[i]!=string1[i])
        {
            t=3;
        }
    }
    return t;
 
}
void printPosition(pnode *position)
{
    position->next =NULL;
    while (position->back!=NULL) {
        pnode * temp = position;
        position =position ->back;
        position ->next = temp;
     
    }
    while(position!=NULL)
    {
        printf("%s", "Step ");
        printf("%i", position->cost);
        printf("%s", " Move ");
        printf("%c ", position->piece);//shit
        switch(position->dir)
        {
            case 'E':
             printf("%s\n","East");
                break;
            case 'W':
             printf("%s\n", "West");
                break;
            case 'S':
             printf("%s\n","South");
                break;
            case 'N':
            printf("%s\n","nortH");
                break;
            case 'I':
                printf("%s\n","Initial Position");
            
                break;
        }
      
        printf("%.06s\n",position->board);
        
       printf("%.06s\n",&position->board[6]);
        position = position->next;
        
    }
}

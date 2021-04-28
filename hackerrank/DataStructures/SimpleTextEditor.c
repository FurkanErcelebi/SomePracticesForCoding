#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

struct stack{
      int type;
      char *opd;
      struct stack *next;
      struct stack *pre;    
};

struct stack *opr_stack,*head;
int size;

int pushStack(int ,char* );

void popStack();

int main() {

    opr_stack =  NULL;
    head = NULL;
    size = 0;
    char *str = (char *)malloc(100000 * sizeof(char));
    int i,j,len,len1,opr,num_of_opr;
    
    scanf("%d",&num_of_opr);
    
    
    i = 0;
    do{
        scanf("%d",&opr);
        switch(opr){
            case 1:{
                len  = strlen(str);
                memset(str,'\0',len);
                
                scanf("%s",str);
                        
                pushStack(1,str);
                
            }break;
            case 2:{
                len  = strlen(str);
                memset(str,'\0',len);
                
                scanf("%s",str);
                
                pushStack(0,str);
                
            }break;
            case 3:{
                
                scanf("%d",&j);
                len  = strlen(str);
                memset(str,'\0',len);
                struct stack *itr = head;
                
                while(itr != NULL){
                    if(itr->type){
                        
                        if(!strlen(str)){
                            len1 = strlen(itr->opd);
                            str= (char *)malloc((len1 +1));
                            strcpy(str,itr->opd);
                        }
                        else{
                            len  = strlen(str);
                            len1 = strlen(itr->opd);
                            str= (char *)realloc(str , (len + len1 + 1));
                            strcat(str,itr->opd);
                        }
                        
                            
                    }
                        
                    else{
                            
                        len = atoi(itr->opd);
                        len1 = strlen(str) ;
                        if(len1 > 0){
                            str[len1 - len] = '\0';
                        }
                        else {
                            memset(str,'\0',len);;
                        }
                        
                    }
                    
                    itr = itr->pre;
                }
                    
                printf("%c\n",str[j - 1]);
                
            }break;
            case 4:{
                
                popStack();
                
            }break;
        }
        
        i++; 
    }while(i < num_of_opr);

    return 0;
}

int pushStack(int a,char *str){
    if(size == 0){
        opr_stack =  (struct stack*)malloc(1*sizeof(struct stack));
        opr_stack->type = a;
        opr_stack->opd = (char *)malloc(strlen(str)*sizeof(char));
        strcpy(opr_stack->opd,str);
        opr_stack->next = NULL;
        opr_stack->pre = NULL;
        head = (struct stack*)malloc(1*sizeof(struct stack));
        head = opr_stack;
        size++;
        return 1;
    }
    
    struct stack* temp = (struct stack*)malloc(1*sizeof(struct stack));
    temp->type = a;
    temp->opd = (char *)malloc(strlen(str) * sizeof(char));
    strcpy(temp->opd,str);
    temp->next = opr_stack;
    temp->pre = NULL;
    opr_stack->pre = temp;
    size++;
    if(size == 1){
             head = opr_stack;
    } 
    opr_stack = temp;
    
    return 1;
    
}

void popStack(){
    if(size == 0){
        printf("Stack is empty!\n");
        return ;
    }
    

    struct stack* other_stack = opr_stack;
    other_stack = other_stack->next;
    free(opr_stack);
    if(size == 1){
             head = NULL;
    }
    else{
        other_stack->pre = NULL;
        
    }
    opr_stack = other_stack;
    size--;
}

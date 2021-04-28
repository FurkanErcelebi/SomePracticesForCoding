/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


struct ListNode* removeNthFromEnd(struct ListNode* head, int n){

    int i,size = 0;
    
    struct ListNode *temp,*prev = NULL;
    
    for(temp = head;temp != NULL;temp = temp->next){
            size++;
    }
    
    temp = head;
    
    for(i = 0;i < size - n ;i++){
        prev = temp;
        temp = temp->next;
    }
    
    if(prev == NULL){
        head = temp->next;
    }
    else{
        prev->next = temp->next; 
    }
    
    temp->next = NULL;
    temp->val = -1;
    free(temp);
    
    return head;
    
}

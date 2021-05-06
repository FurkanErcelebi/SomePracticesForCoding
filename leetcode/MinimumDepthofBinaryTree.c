/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
#define MAX 50000
    
int levels[MAX];    
int size = 0;

void preTrevarsal(struct TreeNode* root,int level){
    
    if(root == NULL){
        return;
    }
    else{
        if(root->right == NULL && root->left == NULL){
            //printf("(%d)\n",level);
            levels[size] = level;
            size++;  
        }
    }
    
    preTrevarsal(root->right,level + 1);
    
    preTrevarsal(root->left,level + 1);
}

int minDepth(struct TreeNode* root){
    
    int i,min = 0,result;
    
    for(i = 0;i < MAX;i++){
        levels[i] = 0;
    }
    
    preTrevarsal(root,1);
    
    for(i = 1;i < size;i++){
        if(levels[min] > levels[i]){
            min = i;
        }
    }
    result = levels[min];
    
    for(i = 0;i < size;i++){
        levels[i] = 0;
    }
    
    size = 0;
    
    return result;
}

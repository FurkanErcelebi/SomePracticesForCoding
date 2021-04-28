/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


#define MAXSIZE 100 

typedef struct qnode{
	int data;
	int level;
	struct qnode *next;
}QNode;

typedef struct queue{
	int count;
	QNode *front;
	QNode *rear;
}Queue;

void initialize(Queue *q)
{
	q->count = 0;
	q->front = NULL;
	q->rear = NULL;
}

int isempty(Queue *q)
{
	return (q->rear == NULL);
}

void enqueue(Queue *q, int value,int level){
	if (q->count < MAXSIZE){
		QNode *tmp = (QNode *)malloc(sizeof(QNode));
		tmp->data = value;
		tmp->level = level;
		tmp->next = NULL;
		if(!isempty(q)){
			q->rear->next = tmp;
			q->rear = tmp;
		}
		else{
			q->rear = tmp;
			q->front = q->rear;
		}
		q->count++;
	}
	else{
		printf("List is full\n");
	}
}

QNode* dequeue(Queue *q)
{
	QNode *ret = (QNode*)malloc(sizeof(QNode));
	ret->data = q->front->data;
	ret->level = q->front->level;
	ret->next = NULL;
	
	QNode *tmp = q->front;
	q->front = q->front->next;
	q->count--;
	if(q->count == 0){
		q->rear = NULL;
	}
	free(tmp);
	
	return(ret);
}

void travelPostTree(struct TreeNode *node,Queue *q,int level){
	
	if(node == NULL){
		return;
	}
	
	level++;
	
	travelPostTree(node->left,q,level);
	
	travelPostTree(node->right,q,level);
	
	
	if(!isempty(q)){
		int exit = 0,assign = 0,newdata,newlevel,i = 0;
		QNode *queue_node;
		while(!assign &&!exit && !isempty(q)){
			queue_node = dequeue(q);
			newlevel = queue_node->level;
			newdata = queue_node->data;
			if(newlevel == level){
				newdata = node->val;
				assign = 1;
			}
			
			enqueue(q,newdata,newlevel);
			
			i++;
			if(i == q->count){
				exit = 1;
			}
		}
		
		if(assign == 0){
			enqueue(q,node->val,level);	
		}
	}
	else{
		enqueue(q,node->val,level);
	}
	
}

int* rightSideView(struct TreeNode* root, int* returnSize){
	
	Queue *q = (Queue *)malloc(sizeof(Queue));
	initialize(q);
	travelPostTree(root,q,0);
	
	int *result = (int *)malloc(MAXSIZE * sizeof(int)),i;
	*returnSize = q->count;
	QNode *queue_node;
	for(i = q->count - 1;i > -1;i--){
		queue_node = dequeue(q);
		result[queue_node->level - 1] = queue_node->data;
	}
	
	return result;
}

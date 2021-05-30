#define MAX 100

int stack[MAX];
int head = -1;

bool isEmpty(){
    return head == -1? true : false;
}

bool isFull(){
    return head == MAX ? true : false;
}

void push(int val){
    
    if(!isFull()){
        head++;
        stack[head] = val;
    } 
}

int pop(){
    
    int result = -1;
    if(!isEmpty()){
        result = stack[head];
        head--;
    }
    
    return result;
    
}

void findPrerequisites(bool **requirement,bool *reachable,int requirementSize,int find){
    
    int i,index;
    
    push(find);
    reachable[find] = true;
    while(!isEmpty()){
        
        index = pop();
        
        for(i = 0;i < requirementSize;i++){
            if(!reachable[i] && requirement[index][i]){
                reachable[i] = true;
                push(i);
            }
        }
    }
    
}

bool* checkIfPrerequisite(int numCourses, int** prerequisites, int prerequisitesSize, int* prerequisitesColSize, int** queries, int queriesSize, int* queriesColSize, int* returnSize){
    
    int i,j,a,b,req,req_index;
    bool *result = (bool*)malloc(queriesSize * sizeof(bool));
    bool *reachable =  (bool*)malloc(numCourses * sizeof(bool));
    bool **requirement = (bool**)malloc(numCourses * sizeof(bool*));
    
    for(i = 0;i < numCourses;i++){
        requirement[i] = (bool*)malloc(numCourses * sizeof(bool));
    }
        
    for(i = 0;i < numCourses;i++){
        for(j = 0;j < numCourses;j++){
           requirement[i][j] = false; 
        }
        reachable[i] = false;
    }
    
    for(i = 0;i < prerequisitesSize;i++){
        for(j = 1;j < prerequisitesColSize[i];j++){
            a = prerequisites[i][0];
            b = prerequisites[i][j];
            requirement[a][b] = true; 
        }
    }
    
    req_index = 0;
    for(i = 0;i < queriesSize;i++){
        
        findPrerequisites(requirement,reachable,numCourses,queries[i][0]);
        req = 0;
        for(j = 1;j < queriesColSize[i];j++){
            if(reachable[queries[i][j]]){
                req++;
            }
        }
        if(j - 1 == req){
            result[req_index] = true;
            req_index++;
        }
        else{
            result[req_index] = false; 
            req_index++;
        }
        for(j = 0;j < numCourses;j++){
        	reachable[j] = false;	
		}
    }
    
    (*returnSize) = req_index;
    return result;
}

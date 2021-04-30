#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char** split_string(char*);

/*
 * Complete the cookies function below.
 */
void MinHeapInsertOrder(int i,int *A){
    int tmp;
    
    if(i >= 0 && A[(i - 1)/2] > A[i]){
        tmp = A[i];
        A[i] = A[(i - 1)/2]; 
        A[(i - 1)/2] = tmp;
        
        MinHeapInsertOrder((i - 1)/2,A);
    }
    
}

void MinHeapExtractOrder(int i,int size,int *A){
    
    int r,l,tmp,maxind = i;
                
    l = 2*i + 1;
                
    if(l < size && A[i] > A[l])
    {
        maxind = l;
    }
                
    r = 2*i + 2;
                
    if (r < size && A[i] > A[r]) 
    {
        maxind = r;
    }
                
    if(i != maxind){
        tmp = A[i];
        A[i] = A[maxind];
        A[maxind] = tmp;
        MinHeapExtractOrder(maxind,size,A);
    }
    
}

int cookies(int k, int A_count, int* A) {// 13,47,74,12,89,74,18,38

    int a,b,c,tmp,end,temp,i,j,sum=0,ordered = 1;
    
    for(i = 0;i < A_count && k<=A[i];i++);
    
    if(i == A_count){
        return 0;
    }
    
    for(i = 0;i < A_count - 1 && ordered == 1;i++){
        if(A[i] > A[i+1]){
            ordered = 0;
        }
    }
     
    if(ordered == 0){
       for(i = 1;i < A_count;i++){
           
           temp = A[i];
           j = i - 1;
           while (0 <= j && temp < A[j]) {
               
               tmp = A[j];
               A[j] = A[j + 1];
               A[j + 1] = tmp;
               j--;
           }
           
       } 
    }
    
    
//    for(j = 0;j < A_count; j++){
//        printf("%d\t",A[j]);
//    }
//        printf("\n");

    
    i = 0;
    while (i != A_count && A_count > 1){    
        
        for(i = 0;k <= A[i] && i < A_count;i++);
        
        if(i < A_count){
            a = A[0];
            A_count--;
            for(j = 0;j < A_count;j++){
                A[j] = A[j+1];
            }
            MinHeapExtractOrder(0,A_count,A);
            
            b = A[0];
            A_count--;
            for(j = 0;j < A_count;j++){
                A[j] = A[j+1];
            }
            MinHeapExtractOrder(0,A_count,A);
            
            c = a + 2*b;
            A_count++;
            A[A_count - 1] = c;
            A[A_count] = 0;
            
            MinHeapInsertOrder(A_count - 1,A);
            
            sum++;
            
            
//            for(j = 0;j < A_count; j++){
//                printf("%d\t",A[j]);
//            }
//            printf("\n");
            
        }  
    }
      
    if(i == A_count) {
        return sum;
    }
    else {
        if(A_count == 1){
            if(A[0] >= k){
            return sum;
            }
        }
        
        return -1;
    }
}

 
int main()
{
//    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char** nk = split_string(readline());

    char* n_endptr;
    char* n_str = nk[0];
    int n = strtol(n_str, &n_endptr, 10);

    if (n_endptr == n_str || *n_endptr != '\0') { exit(EXIT_FAILURE); }

    char* k_endptr;
    char* k_str = nk[1];
    int k = strtol(k_str, &k_endptr, 10);

    if (k_endptr == k_str || *k_endptr != '\0') { exit(EXIT_FAILURE); }

    char** A_temp = split_string(readline());

    int A[n];
	
	int A_itr;
    for (A_itr = 0; A_itr < n; A_itr++) {
        char* A_item_endptr;
        char* A_item_str = A_temp[A_itr];
        int A_item = strtol(A_item_str, &A_item_endptr, 10);

        if (A_item_endptr == A_item_str || *A_item_endptr != '\0') { exit(EXIT_FAILURE); }

        A[A_itr] = A_item;
    }

    int result = cookies(k, n, A);

//    fprintf(fptr, "%d\n", result);
    printf("%d", result);

//    fclose(fptr);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) { break; }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') { break; }

        size_t new_length = alloc_length << 1;
        data = realloc(data, new_length);

        if (!data) { break; }

        alloc_length = new_length;
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';
    }

    data = realloc(data, data_length);

    return data;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);
        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}


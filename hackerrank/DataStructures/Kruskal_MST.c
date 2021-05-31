#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char* ltrim(char*);
char* rtrim(char*);
char** split_string(char*);

int parse_int(char*);


int* createFlagArray(int size, int flag) {
    int* arr = (int*)malloc(sizeof(int) * size);
    int i;
    for (i = 0; i < size; i++)
        arr[i] = flag;
    return arr;
}

void interchange(int *array1,int a,int b){
    int tmp;
    
    tmp = array1[a];
    array1[a] = array1[b];
    array1[b] = tmp;
    
}

int find(int* set, int u) {

    int x = u - 1;
    while (set[x] >= 0)
        x = set[x];
    return x;

}

void merge(int* set, int u1, int v1) {
    if (set[u1] < set[v1]) {
        set[v1] += set[u1];
        set[u1] = v1;
    }
    else {
        set[u1] += set[v1];
        set[v1] = u1;
    }
}

void sortEdges(int *edge_weight,int *array1,int *array2,int edges){
    
    int i,j,tmp;
    for (i = 0; i < edges - 1; i++) {
        for (j = 0; j < edges - 1 - i; j++) {
            if (edge_weight[j + 1] < edge_weight[j]){
                interchange(edge_weight,j,j+1);
                interchange(array1,j,j+1);
                interchange(array2,j,j+1);
            }
        }
    }
    
} 

int kruskals(int g_nodes, int g_edges, int* g_from, int* g_to, int* g_weight) {
    
    int* set = createFlagArray(g_nodes,-1);
    int i,j,a,b,from,to,sum,min_weigth,min_index;
    
    sortEdges(g_weight,g_from,g_to,g_edges);
    
    j = 0;
    i = 0;
    sum = 0;
    while(i < g_nodes - 1){
        
        from = g_from[j];
        to = g_to[j];
        min_weigth = g_weight[j];
        j++;
    
        a = find(set,from);
        b = find(set,to);
        
        if(a != b){
            merge(set,a,b);
            sum += min_weigth;
            i++;
        }
        
    }
    
    free(set);
    return sum;
}

int main()
{
    FILE* fptr = fopen("C:\\Users\\Lenovo\\Documents\\DataStructuresandAlgorithms\\output.txt", "w");
	
	if(fptr == NULL){
		printf("File cannot opened\n");
		return 1;
	}
    char** g_nodes_edges = split_string(rtrim(readline()));

    int g_nodes = parse_int(*(g_nodes_edges + 0));
    int g_edges = parse_int(*(g_nodes_edges + 1));

    int* g_from = malloc(g_edges * sizeof(int));
    int* g_to = malloc(g_edges * sizeof(int));
    int* g_weight = malloc(g_edges * sizeof(int));
	int i;
    for (i = 0; i < g_edges; i++) {
        char** g_from_to_weight = split_string(ltrim(readline()));

        int g_from_temp = parse_int(*(g_from_to_weight + 0));
        int g_to_temp = parse_int(*(g_from_to_weight + 1));
        int g_weight_temp = parse_int(*(g_from_to_weight + 2));

        *(g_from + i) = g_from_temp;
        *(g_to + i) = g_to_temp;
        *(g_weight + i) = g_weight_temp;
    }

    int res = kruskals(g_nodes, g_edges, g_from, g_to, g_weight);

	fprintf(fptr,"%d",res);
	
    fclose(fptr);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;

    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!data) {
            data = '\0';

            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);

        if (!data) {
            data = '\0';
        }
    } else {
        data = realloc(data, data_length + 1);

        if (!data) {
            data = '\0';
        } else {
            data[data_length] = '\0';
        }
    }

    return data;
}

char* ltrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    while (*str != '\0' && isspace(*str)) {
        str++;
    }

    return str;
}

char* rtrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    char* end = str + strlen(str) - 1;

    while (end >= str && isspace(*end)) {
        end--;
    }

    *(end + 1) = '\0';

    return str;
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

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}


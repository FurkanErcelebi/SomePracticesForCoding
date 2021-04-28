#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <set>
#include <algorithm>
using namespace std;


int main() {
    
    string line;
    char str[20];
    int i,j,count = 0,num,size;
    getline(cin,line);
    count = atoi(line.c_str());
    
    set<int> set_num;
    set<int>::iterator itr;
    for (i = 0;i < count;i++) {
        getline(cin,line);
        size = line.size() - 2;
        line.copy(str, size,2);
        num = atoi(str);
        switch (line[0]) {
            case '1': set_num.insert(num);
            break;
            
            case '2':
            itr=set_num.find(num);
            if (itr != set_num.end()) {
                set_num.erase(itr);
            }
            break;
            
            case '3':
            itr=set_num.find(num);
            if (itr == set_num.end()) {
            cout << "No" << endl; 
            }
            else {
            cout << "Yes" << endl;
            }
            break;
        } ;
        j = 0;
        while(j < size){
            str[j] = '\0';
            j++;
        }
        
    }
    
    return 0;
}

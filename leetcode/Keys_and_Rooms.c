

bool canVisitAllRooms(int** rooms, int roomsSize, int* roomsColSize){

    int i,j,k,head = -1,key;
    int openrooms[roomsSize];
    int keystack[roomsSize];
    head++;
    keystack[head] = 0;
    openrooms[keystack[head]] = 1;
    for(i = 1;i < roomsSize;i++){
            openrooms[i] = 0;
    }
    
    do{
        i = keystack[head];
        head--;
        for(j = 0;j < roomsColSize[i];j++){
            key = rooms[i][j];
            if(openrooms[key] == 0){
                openrooms[key] = 1;
                head++;
                keystack[head] = key;
                
            }
            
        }
        
    }while(head != -1);
    
    
    for(i = 1;i < roomsSize;i++){
            if(openrooms[i] == 0){
                return false;
            }
    }
    
    return true;
    
}

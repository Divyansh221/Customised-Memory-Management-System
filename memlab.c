// Assignment 5
// Hands on experience for creating better memory management systems
// Operating Systems Laboratory (CS39002)
// Group 34
// Amartya Mandal 19CS10009
// Divyansh Bhatia 19CS10027

#include "memlab.h"
#define MIN(x, y) ((x < y) ? x : y)

struct symbolTableEntry{
    int type;
    int localCounter;
    int size;
    bool mark;
    char name[MAX_CHAR];
};

struct pageTableEntry{
    int localAddress;
    char name[MAX_CHAR];
};

struct stack{
    char name[MAX_VAR][MAX_CHAR];
    int count;
};

struct freeSegment{
    int count;
    int array[MAX_VAR];
};

int totalCounter;
int totalMemorySize;
bool force = 1;
bool thread = 0;
unsigned char *memPtr;

struct freeSegment *freeSegments;
struct symbolTableEntry *ste;
struct pageTableEntry *pte;
struct stack* st;

pthread_t gcid;
pthread_mutex_t mutex_lock;

void push(char* name){
    strcpy(st->name[st->count],name);
    st->count++;
}

void init_stack(){
    st = (struct stack*) malloc(sizeof(struct stack));
    st->count = 0;
}

void top(char* s){
    strcpy(s,st->name[st->count-1]);
}

void pop(){
    st->count--;
}

int search_symbolTableEntry(char *name){
    for(int i = 0; i < MAX_SIZE; i++){
        if(strcmp(name, ste[i].name) == 0) return i;
    }
    return -1;
}

void insert_symbolTableEntry(char *name, int type, int counter, int size){
    for(int i = 0; i < MAX_SIZE; i++){
        if(ste[i].type == -1){
            pthread_mutex_lock(&mutex_lock);
            strcpy(ste[i].name, name);
            ste[i].type = type;
            ste[i].localCounter = counter;
            ste[i].size = size;
            ste[i].mark = 0;
            pthread_mutex_unlock(&mutex_lock);
            return;
        }
    }
}

void sweepPhase(int n){
    int type = ste[n].type;
    int logicalAddress = ste[n].localCounter;
    pthread_mutex_lock(&mutex_lock);
    ste[n].size = 0;
    ste[n].type = -1;
    ste[n].localCounter = -1;
    ste[n].mark = 0;
    memset(ste[n].name, '\0', sizeof(ste[n].name));
    pthread_mutex_unlock(&mutex_lock);
    memset(pte[logicalAddress].name, '\0', sizeof(pte[logicalAddress].name));
    int size = ste[n].size;
    if(size != 1){
        for(int i = 0; i < size; i++){
            freeSegments->array[freeSegments->count] = pte[logicalAddress + i].localAddress;
            freeSegments->count++;
            pte[logicalAddress + i].localAddress = -1;
        }
    }
    else{
        freeSegments->array[freeSegments->count] = pte[logicalAddress].localAddress;
        freeSegments->count++;
        pte[logicalAddress].localAddress = -1;
    }
}

void compactPhase(){
    printf("\t***In Compact Phase***\n");
    int f = -1;
    int h = 0;
    for(int i = 0; i < totalCounter/4; i++){
        if(pte[i].localAddress == -1) {
            if(f == -1) f = i;
            h++;
        }
    }
    if(f == -1) return;
    int start = f;
    for(int i = f + 1; i < totalCounter/4; i++){
        if(pte[i].localAddress == -1) continue;
        char *varName = pte[i].name;
        int found = search_symbolTableEntry(varName);
        pthread_mutex_lock(&mutex_lock);
        ste[found].localCounter = start;
        pthread_mutex_unlock(&mutex_lock);
        pte[start].localAddress = pte[i].localAddress;
        strcpy(pte[start].name, varName);
        pte[i].localAddress = -1;
        start++;
        int size = ste[found].size;
        if(size != 1){
            i++;
            for(int j = 0; j < size - 1; j++){
                pte[start].localAddress = pte[i].localAddress;
                pte[i].localAddress = -1;
                start++;
                i++;
            }
            i--;
        }
    }
    totalCounter -= 4*h;
}

void gc_run(){
    printf("\tRunning Garbage Collection...\n");
    printf("\t***In Sweep Phase***\n");
    for(int i = 0; i < MAX_SIZE; i++){
        if(ste[i].mark == 1){
            sweepPhase(i);
        }
    }
    compactPhase();
}

void *gc_initialize(void *param){
    printf("\tRunning gc_initialize\n");
    while(1){
        if(thread){
            thread = 0;
            break;
        }
        usleep(1000);
        gc_run();
    }
    return NULL;
}

void createMem(int size){
    printf("\tRunning createMem\n");
    totalMemorySize = size;
    memPtr = (unsigned char *) malloc(size);

    ste = (struct symbolTableEntry *) malloc(sizeof(struct symbolTableEntry)*MAX_SIZE);
    for(int i = 0; i < MAX_SIZE; i++){
        ste[i].size = 0;
        ste[i].type = -1;
        ste[i].localCounter = -1;
        ste[i].mark = 0;
        memset(ste[i].name, '\0', sizeof(ste[i].name));
    }

    pte = (struct pageTableEntry *) malloc(sizeof(struct pageTableEntry)*MIN(MAX_VAR, size/4));
    for(int i = 0; i < MIN(MAX_VAR, size/4); i++){
        pte[i].localAddress = -1;
        memset(pte[i].name, '\0', sizeof(pte[i].name));
    }

    freeSegments = (struct freeSegment *) malloc(sizeof(struct freeSegment));
    freeSegments->count = 0;
    for(int i = 0; i < MIN(MAX_VAR, size/4); i++){
        freeSegments->array[freeSegments->count] = i;
        freeSegments->count++;
    }
    
    init_stack();
    
    pthread_mutex_init(&mutex_lock,NULL);
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    int GC = pthread_create(&gcid, &attr, gc_initialize, NULL);
    if(GC < 0){
        printf("Error: Cannot create thread\n");
        exit(1);
    }
}

void createVar(char *name, int type){
    int found = search_symbolTableEntry(name);
    if(totalCounter >= totalMemorySize) {
        printf("Memory limit exceeded\n");
        return;
    }
    if(found != -1) {
        printf("Variable with same name exists\n");
        return;
    }
    printf("\tRunning createVar for %s\n", name);
    if(type != INTEGER){
        printf("\tWord alignment is done!\n");
    }
    insert_symbolTableEntry(name, type, totalCounter/4, 1);
    push(name);
    int freeF = freeSegments->array[freeSegments->count - 1];
    pte[totalCounter/4].localAddress = freeF;
    strcpy(pte[totalCounter/4].name, name);
    freeSegments->count--;
    totalCounter += 4;
}

void createArr(char *name, int type, int size){
    int found = search_symbolTableEntry(name);
    if(totalCounter + (size - 1)*4 >= totalMemorySize){
        printf("Memory exceeded\n");
        return;
    }
    if(found != -1){
        printf("Variable name exists\n");
        return;
    }
    printf("\tRunning createArr for %s\n", name);
    if(type != INTEGER){
        printf("\tWord alignment is done!\n");
    }
    insert_symbolTableEntry(name, type, totalCounter/4, size);
    push(name);
    strcpy(pte[totalCounter/4].name, name);
    if(type == INTEGER || type == MEDIUM_INT)
        for(int i = 0; i < size; i++){
            int freeF = freeSegments->array[freeSegments->count - 1];
            pte[totalCounter/4].localAddress = freeF;
            totalCounter += 4;
            freeSegments->count--;
        }
    else{
        int t_size = size/4;
        int offset = size%4;
        if(offset) t_size++;
        for(int i = 0; i < t_size; i++){
            int freeF = freeSegments->array[freeSegments->count - 1];
            pte[totalCounter/4].localAddress = freeF;
            totalCounter += 4;
            freeSegments->count--;
        }
    }   
}

void assignVar(char *name, int type, int val){
    int found = search_symbolTableEntry(name);
    if(found == -1){
        printf("No such variable exists\n");
        return;
    }
    printf("\tRunning assignVar for %s\n", name);
    int my_type = ste[found].type;
    if(my_type != type){
        printf("Variable types do not match\n");
        return;
    }
    int logicalAddress = ste[found].localCounter;
    int frameAddress = pte[logicalAddress].localAddress;

    if(type == INTEGER){
        for(int i = 0; i < 4; i++){
            *(memPtr + frameAddress*4 + 3 - i) = val & 255;
            val >>= 8; 
        }
    }
    else if(type == MEDIUM_INT){
        for(int i = 0; i < 3; i++){
            *(memPtr + frameAddress*4 + 2 - i) = val & 255;
            val >>= 8; 
        }
    }
    else if(type == CHARACTER){
        *(memPtr + frameAddress) = val;
    }
    else *(memPtr + frameAddress*4) = val;
}

void assignArr(char *name, int type, int offset, int val){
    int found = search_symbolTableEntry(name);
    if(found == -1){
        printf("No such variable exists\n");
        return;
    }
    printf("\tRunning assignArr for %s[%d]\n", name, offset);
    int my_type = ste[found].type;
    if(my_type != type){
        printf("Variable types do not match\n");
        return;
    }
    int of;
    if(type == CHARACTER || type == BOOLEAN){
        of = offset%4;
        offset/=4;
    }
    int logicalAddress = ste[found].localCounter + offset;
    int frameAddress = pte[logicalAddress].localAddress;

    if(type == INTEGER){
        for(int i = 0; i < 4; i++){
            *(memPtr + frameAddress*4 + 3 - i) = val & 255;
            val >>= 8; 
        }
    }
    else if(type == MEDIUM_INT){
        for(int i = 0; i < 3; i++) {
            *(memPtr + frameAddress*4 + 2 - i) = val & 255;
            val >>= 8; 
        }
    }
    else if(type == CHARACTER){
        *(memPtr + frameAddress*4+of) = val;
    }
    else *(memPtr + frameAddress*4+of) = val;
}

int getVar(char *name){
    int found = search_symbolTableEntry(name);
    if(found == -1){
        printf("No such variable exists\n");
        return -1;
    }
    if(ste[found].size!=1){
        printf("%s is an array\n", name);
        return -1;
    }
    printf("\tRunning getVar for %s\n", name);
    int logicalAddress = ste[found].localCounter;
    int frameAddress = pte[logicalAddress].localAddress;
    int num_val = 0;
    int type = ste[found].type;
    if(type == INTEGER){
        for(int i = 0; i < 4; i++){
            num_val <<= 8;
            num_val += *(memPtr + frameAddress*4 + i);
        }
    }
    else if(type == MEDIUM_INT){
        for(int i = 0; i < 3; i++) {
            num_val <<= 8;
            num_val += *(memPtr + frameAddress*4 + i); 
        }
    }
    else if(type == CHARACTER){
        num_val = *(memPtr + frameAddress*4);
    }
    else num_val = *(memPtr + frameAddress*4);
    return num_val;
}

int getArrElem(char *name, int offset){
    int found = search_symbolTableEntry(name);
    if(found == -1){
        printf("No such variable name exists\n");
        return -1;
    }
    printf("\tRunning getArrElem for %s[%d]\n", name, offset);
    int type = ste[found].type;
    int of;
    if(type == CHARACTER || type == BOOLEAN){
        of = offset%4;
        offset/=4;
    }
    int logicalAddress = ste[found].localCounter + offset;
    int frameAddress = pte[logicalAddress].localAddress;
    int num_val = 0;
    if(type == INTEGER){
        for(int i = 0; i < 4; i++){
            num_val <<= 8;
            num_val += *(memPtr + frameAddress*4 + i);
        }
    }
    else if(type == MEDIUM_INT){
        for(int i = 0; i < 3; i++){
            num_val <<= 8;
            num_val += *(memPtr + frameAddress*4 + i); 
        }
    }
    else if(type == CHARACTER){
        num_val = *(memPtr + frameAddress*4+of);
    }
    else num_val = *(memPtr + frameAddress*4+of);
    return num_val;
}

void freeElem(char *name){
    if(force)printf("\tRunning freeElem for %s\n", name);
    int found = search_symbolTableEntry(name);
    if(found == -1){
        if(force)printf("No such variable exists\n");
        return;
    }
    ste[found].mark = 1;
    usleep(2000);
    force = 1;
}

void newFunc(){
    printf("\tCreating new function...\n");
    push("#");
}

void endFunc(){
    printf("\tClearing stack after function exit...\n");
    printf("\t***Mark Phase***\n");
    char name[MAX_CHAR];
    while(1){
        top(name);
        pop();
        if(strcmp(name,"#")==0 || st->count<0) break;
        force = 0;
        freeElem(name);
    }
}

void freeMem(){
    printf("\tFreeing all memory\n");
    thread = 1;
    while(1)
        if(thread==0) break;
    pthread_cancel(gcid);
    free(memPtr);
}

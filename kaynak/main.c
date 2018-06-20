#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#define MEMORY_ERROR printf("Cannot allocate memory. Exiting.");exit(-1);

//WARNING
//THIS PROGRAM ONLY RUNS ON WINDOWS.
//IF YOU WANT TO RUN ON LINUX
//PLEASE REMOVE WINDOWS.H, CONIO.H AND
//GETMAXMAZESIZE FUNCTION ENTIRELY.

//STRUCTS
struct mazeBlock{
    int veri;
    int index;
    struct mazeBlock* next;
};

struct block{
    struct mazeBlock *mazePointer;
    int x;
    int y;
    struct block* nextBlock;
};

struct block* lastBlock = NULL;
struct mazeBlock *lastMazeBlock = NULL;
struct mazeBlock *maze = NULL;

//SETTINGS
int printEachStep = 0;
int enterBeforeUpdate = 1;

//VARIABLES
int mouse[2]    = {-1,-1},
    startAt[2]  = {-1,-1},
    endAt[2]    = {-1,-1},
    mazeSize[2] = {-1,-1},
    maxSize[2]  = {99,99},
    state       = 0;

//FUNCTIONS
struct mazeBlock *getMazeBlock(int index);
void push(struct mazeBlock *mazePointer, int x, int y);
void pop();
void lookAround();
void getMaxMazeSize();
void getMazeSize();
void createMaze();
void printMaze();
void getMazePoints();
void findPath();

//MAIN
int main(){
    //Randomize numbers each start
    srand(time(NULL));

    //Get window dimensions
    getMaxMazeSize();

    //Get maze dimensions from user
    getMazeSize();

    //Create random maze
    createMaze();

    //Print randomized maze
    printMaze();

    //Get start and end points from user
    getMazePoints();

    //Start searching through maze
    findPath();

    return 0;
}

/*
 * Function: getMazeBlock
 * --------------
 * Gets pointer of nth node of link list.
 *
 * index: How many times should it call the next node.
 */
struct mazeBlock *getMazeBlock(int index){
    if(index<mazeSize[0]*mazeSize[1] && index>=0){
        int i;
        struct mazeBlock *returnBlock = maze;
        for(i=0;i<index;i++){
            returnBlock = returnBlock->next;
        }
        return returnBlock;
    }
    struct mazeBlock* errorBlock = (struct mazeBlock*) malloc(sizeof(struct mazeBlock));
    if(!errorBlock){MEMORY_ERROR}
    errorBlock->index = -1;
    errorBlock->next = NULL;
    errorBlock->veri = 0;
    return errorBlock;
}

/*
 * Function: push
 * --------------
 * Allocates new memory block, sets it and connects it with last block.
 *
 * mazePointer: Block's pointer from maze matrix.
 *           x: Block's X Axis.
 *           y: Block's Y Axis.
 */
void push(struct mazeBlock *mazePointer, int x, int y){
    struct block* block = (struct block*) malloc(sizeof(struct block));
    if(!block){MEMORY_ERROR}
    block->nextBlock = lastBlock;
    block->mazePointer = mazePointer;
    block->x = x;
    block->y = y;
    lastBlock = block;
}

/*
 * Function: pop
 * -------------
 * Removes last element from linked list stack. If there is nothing to remove,
 *           makes state -1 (Cannot find maze path)
 */
void pop(){
    struct block* alinacak = lastBlock;
    mouse[0] = lastBlock->x;
    mouse[1] = lastBlock->y;
    lastBlock = (lastBlock)->nextBlock;
    free(alinacak);
    if(lastBlock==NULL){state=-1;printMaze();}
}

/*
 * Function: lookAround (Recursive)
 * --------------------------------
 * Looks what it stands on and around it (linear, not diagonal). If it already
 *           visited them all, goes back.
 */
void lookAround(){
    if(lastBlock->mazePointer==getMazeBlock(endAt[0]*mazeSize[1]+endAt[1])){
        lastBlock->mazePointer->veri = 2;
        state = 1;
        if(!printEachStep){printMaze();}
    }else if(getMazeBlock(lastBlock->mazePointer->index-mazeSize[1])->veri==1){
        lastBlock->mazePointer->veri = 2;
        push(getMazeBlock(lastBlock->mazePointer->index-mazeSize[1]),mouse[0], mouse[1]);
        mouse[1]--;
    }else if(getMazeBlock(lastBlock->mazePointer->index+1)->veri==1 && mouse[0]!=mazeSize[1]-1){
        lastBlock->mazePointer->veri = 2;
        push(getMazeBlock(lastBlock->mazePointer->index+1),mouse[0], mouse[1]);
        mouse[0]++;
    }else if(getMazeBlock(lastBlock->mazePointer->index+mazeSize[1])->veri==1){
        lastBlock->mazePointer->veri = 2;
        push(getMazeBlock(lastBlock->mazePointer->index+mazeSize[1]),mouse[0], mouse[1]);
        mouse[1]++;
    }else if(getMazeBlock(lastBlock->mazePointer->index+-1)->veri==1 && mouse[0]!=0){
        lastBlock->mazePointer->veri = 2;
        push(getMazeBlock(lastBlock->mazePointer->index+-1),mouse[0], mouse[1]);
        mouse[0]--;
    }else{
        lastBlock->mazePointer->veri = 3;
        pop();
    }
    if(state==0){
        if(printEachStep){
            printMaze();
            if(enterBeforeUpdate){getch();}
        }
        lookAround();
    }
}

/*
 * Function: getMaxMazeSize
 * --------------------
 * Gets window size and prepares it for maze if program runs on Windows.
 */
void getMaxMazeSize(){
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    maxSize[0] = csbi.srWindow.Bottom - csbi.srWindow.Top - 1;
    maxSize[1] = (csbi.srWindow.Right - csbi.srWindow.Left - 1)/2;
}

/*
 * Function: getMazeSize
 * ---------------------
 * Gets Maze size from user & allocates memory for maze.
 */
void getMazeSize(){
    int readError = 0;
    do{
        mazeSize[0] = 0;mazeSize[1] = 0;
        printf("Labirent boyutunu girin (MAX %dx%d) [SATIRxSUTUN]: ", maxSize[0], maxSize[1]);
        readError = scanf(" %dx%d", &mazeSize[0], &mazeSize[1]);
    }while((mazeSize[0]>maxSize[0] || mazeSize[1]>maxSize[1]) ||
           (mazeSize[0]<1 || mazeSize[1]<1) || !readError);
    maze = malloc(sizeof(int)*mazeSize[0]*mazeSize[1]);
    if(!maze){MEMORY_ERROR}
}

/*
 * Function: createMaze
 * --------------------
 * Creates randomized maze.
 */
void createMaze(){
    int i;
    for(i=0; i<mazeSize[0]*mazeSize[1]; i++){
        struct mazeBlock* newBlock = (struct mazeBlock*) malloc(sizeof(struct mazeBlock));
        if(!newBlock){MEMORY_ERROR}
        newBlock->veri = rand() % 2;
        newBlock->index = i;
        if(lastMazeBlock!=NULL){
            lastMazeBlock->next = newBlock;
        }
        lastMazeBlock = newBlock;
        if(i==0){maze = newBlock;}
    }
}

/*
 * Function: printMaze
 * --------------------
 * Prints maze to the terminal.
 */
void printMaze(){
    int i,j;
    system("cls");
    printf("  ");
    for(i=1;i<=mazeSize[1];i++){printf("%-2d",i);}
    printf("\n");
    for(i=0;i<mazeSize[0];i++){
        printf("%2d",i+1);
        for(j=0;j<mazeSize[1];j++){
            if(j==mouse[0] && i==mouse[1]){
                printf("%c%c",60,62);
            }else if(i==endAt[0] && j==endAt[1]){
                printf("%c%c",247,247);
            }else{
            	int tr = getMazeBlock(i*mazeSize[1]+j)->veri;
            	int rt = tr==1?32:tr==2?176:tr==3?250:219;
            	printf("%c%c",rt,rt);
            }
        }
        printf("\n");
    }
}

/*
 * Function: getMazePoints
 * -----------------------
 * Gets Maze start and end points from user.
 */
void getMazePoints(){
    do{
        printf("Labirent girisini girin [SATIRxSUTUN]: ");
        scanf(" %dx%d", &startAt[0], &startAt[1]);
        startAt[0]--;startAt[1]--;
        mouse[1]=startAt[0];
        mouse[0]=startAt[1];
    }while(!(startAt[0]==0 || startAt[1]==0 || startAt[0] == mazeSize[0]-1
    	|| startAt[1] == mazeSize[1]-1) || getMazeBlock(startAt[0]*mazeSize[1]+startAt[1])->veri==0);
    printMaze();
    do{
        printf("Labirent cikisini girin [SATIRxSUTUN]: ");
        scanf(" %dx%d", &endAt[0], &endAt[1]);
        endAt[0]--;endAt[1]--;
    }while(!(endAt[0]==0 || endAt[1]==0 || endAt[0] == mazeSize[0]-1
    	|| endAt[1] == mazeSize[1]-1) || getMazeBlock(endAt[0]*mazeSize[1]+endAt[1])->veri==0);
}

/*
 * Function: findPath
 * ------------------
 * Runs lookAround function recursively and waiting it to finish. After it
             finishes, looks at state and prints the final result.
 */
void findPath(){
    push(getMazeBlock(startAt[0]*mazeSize[1]+startAt[1]), startAt[1], startAt[0]);
    lookAround();
    if(state==-1){printf("Bu labirentin cozumu yoktur.");}
    else{printf("Labirent basariyla cozuldu.");}
    printf(" Cikmak icin bir tusa basin.");
    getch();
}

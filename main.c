// Mumen Anbar
// 1212297
// S3

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct node* Graph;
typedef struct qnode* Queue;
typedef struct tnode* Table;
typedef struct hnode* Heap;

int NumOfNodes;
int NumOfTableNodes;
int Qsize;
char fs[10000];

struct node{    // the struct of each node of the numbers
     char Key[30];
    char u[30];
    int Weight;
    bool visited;
    Graph Next;  // pointer points to the next node if exists
    Graph Pre;   // pointer points to the previous node if exists
};
struct qnode{    // the struct of each node of the numbers
    Graph G;
    int size;
    Queue Next;  // pointer points to the next node if exists
};
struct tnode{
    // Data Members
    char Key[30];  // pointer to point to node of type List
    char Previous[30];  // pointer to point to node of type List
    int Cost;
};
struct hnode{
    Graph* heapArray;
    int capacity;
    int size;
};
void initialize(Graph G[], Table T[]){
    for(int i = 0;i < NumOfNodes; i++){
        Graph cur = G[i];
        while(cur != NULL){
            cur->visited = 0;
            cur = cur->Next;
        }
    }for(int i = 0;i < NumOfTableNodes; i++){
        T[i]->Cost = 1e7;
    }

}

Heap createHeap(int capacity) { // create a heap
    Heap heap = (Heap)malloc(sizeof(struct hnode)); // create a heap node in the memory
    heap->capacity = capacity; // initialize
    heap->size = 0; // initialize
    heap->heapArray = (Graph*)malloc(capacity * sizeof(Graph)); // initialize
    return heap; // return the new heap
}
void swap(Graph* a, Graph* b) { // swapping two nodes
    Graph temp = *a;    // swapping two nodes
    *a = *b;    // swapping two nodes
    *b = temp;  // swapping two nodes
}
void heapifyUp(Heap heap, int index) { // function to move nodes to have
    // Calculate the parent index
    int parent = (index - 1) / 2;
    // Compare the current node with its parent and swap them if necessary
    while (index > 0 && heap->heapArray[parent]->Weight > heap->heapArray[index]->Weight) {
        swap(&(heap->heapArray[parent]), &(heap->heapArray[index]));
        index = parent;
        parent = (index - 1) / 2;
    }
}

void heapifyDown(Heap heap, int index) {
    // Initialize the smallest index as the current index
    int smallest = index;
    int leftChild = 2 * index + 1;  // Calculate the index of the left child
    int rightChild = 2 * index + 2; // Calculate the index of the right child

    // Check if the left child exists and has a smaller weight than the current smallest
    if (leftChild < heap->size && heap->heapArray[leftChild]->Weight < heap->heapArray[smallest]->Weight)
        smallest = leftChild;

    // Check if the right child exists and has a smaller weight than the current smallest
    if (rightChild < heap->size && heap->heapArray[rightChild]->Weight < heap->heapArray[smallest]->Weight)
        smallest = rightChild;

    // If the smallest index has changed, swap the elements and recursively heapify down
    if (smallest != index) {
        swap(&(heap->heapArray[index]), &(heap->heapArray[smallest]));
        heapifyDown(heap, smallest);
    }
}
void enqueue(Heap heap, Graph V) { // add elements to the heap
    // Check if the heap is already full
    if (heap->size == heap->capacity) {
        printf("Heap is full. Cannot insert more elements.\n");
        return;
    }
    // Insert the graph into the heap
    heap->heapArray[heap->size] = V;
    heap->size++;
    // Perform heapifyUp to maintain the heap property
    heapifyUp(heap, heap->size - 1);
}
Graph Top(Heap H) {
    // Check if the heap is empty
    if (H->size == 0) {
        printf("Empty!!\n");
        return NULL;
    }
    // Return the graph at the top of the heap (index 0)
    return H->heapArray[0];
}
void dequeue(Heap heap) {
    // Check if the heap is empty
    if (heap->size == 0) {
        printf("Heap is empty. Cannot delete minimum element.\n");
        return;
    }

    // Replace the root element with the last element in the heap
    heap->heapArray[0] = heap->heapArray[heap->size - 1];
    heap->size--;

    // Perform heapifyDown to maintain the heap property
    heapifyDown(heap, 0);
}

void printHeap(Heap heap) {
    printf("Heap: ");

    // Iterate over the elements of the heap
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->heapArray[i]->Weight);
    }

    printf("\n");
}

void deleteHeap(Heap heap) {
    for (int i = 0; i < heap->size; i++) {
        free(heap->heapArray[i]);
    }

    free(heap->heapArray);
    free(heap);
}
void insert(Graph G[], char u[], char v[], int weight, Table T[]){ // function to insert a node to the front of the list
    Graph V = (Graph)malloc(sizeof(struct node)); // allocating a space for the new node
    strcpy(V->Key, v); // initialize
    strcpy(V->u, u);    // initialize
    V->Next = NULL; // initialize
    V->Pre = NULL;  // initialize
    V->Weight = weight;     // give the node a value
    InsertToMain(G, V, u, T);   // insert to the main one
}
void InsertToMain(Graph G[], Graph V, char u[], Table T[]){
    bool found = 0;
    Graph temp;
    for(int i = 0; i < NumOfNodes; i++) {
        if(strcmp(G[i]->Key , u) == 0){
            found = 1;
            temp = G[i];
            break;
        }
    }
    if(!found){
        // If 'u' is not found in G, create a new node and add it to G
        G[NumOfNodes] = (Graph)malloc(sizeof(struct node));
        strcpy(G[NumOfNodes]->Key, u);  // initialize
        temp = G[NumOfNodes];   // initialize
        temp->Next = NULL;  // initialize
        temp->Weight = 0;   // initialize
        temp->Pre = NULL;   // initialize

        // Also, create a corresponding entry in T
        T[NumOfTableNodes] = (Table)malloc(sizeof(struct tnode));
        strcpy(T[NumOfTableNodes]->Key, u); // initialize
        T[NumOfTableNodes]->Cost = 1e7; // initialize

        NumOfNodes++;   // increament
        NumOfTableNodes++;  // increament
    }

    found = 0;
    // Search for a node in T with the same key as V
    for(int i = 0; i < NumOfTableNodes; i++) {
        if(strcmp(T[i]->Key , V->Key) == 0){
            found = 1; // found element
            break;
        }
    }
    if(!found){
        // If no such node is found, create a new entry in T for V
        T[NumOfTableNodes] = (Table)malloc(sizeof(struct tnode));
        strcpy(T[NumOfTableNodes]->Key, V->Key);    // initialize
        T[NumOfTableNodes]->Cost = 1e7; // initialize
        NumOfTableNodes++;  // increament
    }

    // Connect V to the main list represented by temp
    V->Pre = temp;  // initialize
    V->Next = temp->Next;   // initialize
    temp->Next = V; // initialize
}

Graph GetNode(Graph G[], char u[]){ // get the target node
    for(int i = 0;i < NumOfNodes; i++) {
        if(!strcmp(G[0]->Key, u)) return G[i];
    }
    printf("NOT FOUND\n\n");
    return NULL;
}
Graph GetParent(Graph G[], char u[]){   // get the parent of the target node
    for(int i = 0;i < NumOfNodes; i++) {
        Graph cur = G[i];
        if(!strcmp(cur->Key, u)) return G[i];
    }
    return NULL;
}
Graph GetVertix(Graph G[], char v[]){ // get the target vertix
     for(int i = 0;i < NumOfNodes; i++) {
        Graph cur = G[i];
        while(cur != NULL){
            if(!strcmp(cur->Key, v)) return cur;
            cur = cur->Next;
        }
    }
    return NULL;
}
bool visited(Graph G[], char u[], char v[]){
    // Iterate over the nodes in G
    for(int i = 0; i < NumOfNodes; i++) {
        Graph cur = G[i];
        // Check if the current node's key matches 'u'
        if(strcmp(cur->Key, u)) continue;
        // Traverse the linked list starting from the current node
        while(cur != NULL){
            // Check if the current node's key matches 'v'
            if(!strcmp(cur->Key, v)){
                // Return the visited status of the edge
                return cur->visited;
            }
            cur = cur->Next;
        }
    }
    // If the edge (u, v) is not found, return false (not visited)
    return false;
}
int getCost(Table T[], char K[]){ // get cost of the node
    for(int i = 0;i < NumOfTableNodes; i++){
        if(!strcmp(T[i]->Key, K)) return T[i]->Cost;
    }
}
Table GetTable(Table T[], char K[]){ // get the pointer of the node
    for(int i = 0;i < NumOfTableNodes; i++){
        if(!strcmp(T[i]->Key, K)) return T[i];
    }
}
void update(Graph tmp, Graph Parent, Table T[]){
    // Mark the current graph node as visited
    tmp->visited = 1;
    // Get the table entry corresponding to the current graph node
    Table New = GetTable(T, tmp->Key);
    // Update the cost of reaching the current node
    New->Cost = (tmp->Weight + getCost(T, Parent->Key));
    // Update the previous city in the path to the current node
    strcpy(New->Previous, Parent->Key);
}

void Dijkistra(Graph G[], char src[], char dist[], Table T[]){
    // Initialize the graph and table
    initialize(G, T);
    // Get the parent node of the source city
    Graph V = GetParent(G, src);
    // Set the cost of the source city to 0 in the table
    GetTable(T, V->Key)->Cost = 0;
    // Create a heap and enqueue neighboring cities of the source city
    Heap H = createHeap(100);
    Graph E = V->Next;
    while (E) {
        enqueue(H, E);
        E = E->Next;
    }
    // Dijkstra's algorithm
    while (H->size != 0) {
        Graph tmp = Top(H);
        dequeue(H);
        V = GetParent(G, tmp->u);
        if (V == NULL) continue;
        while (tmp != NULL) {
            if (tmp->Weight + getCost(T, V->Key) < getCost(T, tmp->Key) && !visited(G, V->Key, tmp->Key)) {
                // Update the table entry for the current node if a shorter path is found
                update(tmp, V, T);

                V = GetParent(G, tmp->Key);
                if (V == NULL) break;

                // Enqueue neighboring cities of the current node
                E = V->Next;
                while (E) {
                    enqueue(H, E);
                    E = E->Next;
                }
                break;
            }
            tmp = tmp->Next;
        }
    }
}

void printPath(Table T[], char src[], char dist[]){
    if(getCost(T, dist) == 1e7 || (!getCost(T, dist) && strcmp(src, dist))){
        printf("There Is NO Path Between The Two Given Cities.\n");
        strcpy(fs, "There Is NO Path Between The Two Given Cities.\n");
        return;
    }
    // Print the cost to move from the source city to the destination city
    printf("The Cost To Move From The Given Cities = %d\nThe Path Is: ", getCost(T, dist));
    strcat(fs, "The Cost To Move From The Given Cities = ");
    char snum[5];
    // Convert Distance  to string
    itoa(getCost(T, dist), snum, 10);
    strcat(fs, snum);
    strcat(fs, "\nThe Path Is: ");

    // Create a temporary variable to store the current city
    char cur[30];
    // Set the current city to the destination city
    strcpy(cur, dist);
    // Iterate until reaching the source city
    while(true){
        // Iterate over the table entries
        for(int i = 0; i < NumOfTableNodes; i++){
            // Check if the current entry matches the current city
            if(!strcmp(T[i]->Key, cur)){
                // Print the current city
                printf("%s <- ", T[i]->Key);
                strcat(fs, T[i]->Key);
                strcat(fs, " <- ");
                // Update the current city to the previous city in the path
                strcpy(cur, T[i]->Previous);
                // Exit the loop
                break;
            }
        }
        // Check if the current city is the source city
        if(!strcmp(cur, src)) break;
    }
    // Print the source city
    printf("%s\n", src);
    strcat(fs, src);
    strcat(fs, "\n");
}

void printGraph(Graph G[]){
    // Iterate over the nodes in G
    for(int i = 0; i < NumOfNodes; i++){
        Graph cur = G[i];
        // Traverse the linked list starting from the current node
        while(cur != NULL){
            // Print the key of the current node
            printf("  %s  ", cur->Key);
            cur = cur->Next;
        }
        printf("\n");
    }
}
// Function to create a new empty queue
Queue CreateQueue() {
    // Allocate memory for a new queue node
    Queue Q = (Queue)malloc(sizeof(struct qnode));

    // Initialize the queue node
    Q->Next = NULL; // Set the next pointer to NULL (as it's empty)
    Q->G = NULL;    // Set the graph pointer to NULL

    // Return the newly created queue
    return Q;
}

// Function to enqueue a graph node into the queue
void EnQ(Queue Q, Graph V) {
    // Create a temporary node and allocate memory for it
    Queue tmp = (Queue)malloc(sizeof(struct qnode));

    // Point the temporary node to the current first node in the queue
    tmp->Next = Q->Next;

    // Set the queue's next pointer to the temporary node
    Q->Next = tmp;

    // Set the temporary node's graph pointer to the input graph node
    tmp->G = V;

    // Increase the queue size (assuming Qsize is a global variable)
    Qsize++;
}

// Function to dequeue a node from the queue
void DeQ(Queue Q) {
    // Traverse the queue until the second last node
    while (Q->Next->Next != NULL) {
        Q = Q->Next;
    }

    // Set the next pointer of the second last node to NULL (removing the last node)
    Q->Next = NULL;

    // Decrease the queue size
    Qsize--;
}

// Function to get the front node of the queue (without dequeueing)
Queue Front(Queue Q) {
    // Traverse the queue to reach the last node
    while (Q->Next != NULL) {
        Q = Q->Next;
    }

    // Return the last node (which is the front node in this implementation)
    return Q;
}

void BFSupdate(Graph tmp, Graph Parent, Table T[]){
    // Mark the current graph node as visited
    // Get the table entry corresponding to the current graph node
    Table New = GetTable(T, tmp->Key);
    // Update the cost of reaching the current node
    New->Cost = (1 + getCost(T, Parent->Key));
    // Update the previous city in the path to the current node
    strcpy(New->Previous, Parent->Key);
}

void BFS(Graph G[], char src[], Table T[]){
    for(int i = 0;i < NumOfNodes; i++){
        Graph cur = G[i];
        while(cur != NULL){
            cur->visited = 0;
            cur = cur->Next;
        }
    }
    for(int i = 0;i < NumOfTableNodes; i++){
        T[i]->Cost = 0;
    }

    Queue Q = CreateQueue();
    Graph s = GetParent(G, src);
    Graph Parent = s;
    s->visited = 1;
    EnQ(Q, s);
    while(Qsize > 0){
        s = Front(Q)->G;
        Parent = s;
        DeQ(Q);
        if(s == NULL) continue;
        s = s->Next;
        while(s != NULL){
            Graph S = GetParent(G, s->Key);
            if(S == NULL) {
                BFSupdate(s, Parent, T);
                s = s->Next;
                continue;
            }
            if(!S->visited){
                S->visited = 1;
                BFSupdate(S, Parent, T);
                EnQ(Q, S);
            }
            s = s->Next;
        }
    }
}

int main()
{   // creating a big list to have the expressions

    FILE* FileIn; // input file
    FILE* FileOut; // output file
    Graph G[1000], BG[1000];
    Table T[1000], BT[1000];
    char src[30];
    char dist[30];
    while(true){ // repeat until get choice = 7;
        // showing the menu
        printf("Please Choose One Of The Following:\n");
        printf("1- Load Cities From The File.\n2- Enter Source City.\n");
        printf("3- Enter Destination City.\n");
        printf("4- Exit.\n\n");
        int Choice;
        scanf("%d", &Choice); // the choice of the user
        if(Choice == 1){

            FileIn = fopen("cities.txt", "r"); // inisialize the input file
            char line[100];
            char city1[30];bool W1 = 0;
            char city2[30];bool W2 = 0;
            int D = 0;
            while (fscanf(FileIn, "%99s", line) == 1) {
                D = 0;
                if(!W1){
                    strcpy(city1, line);
                    W1 = 1;
                }
                else if(W1 && !W2){
                    strcpy(city2, line);
                    W2 = 1;
                }
                else if(W2){
                    for(int i = 0;i < strlen(line); i++){
                        if(line[i] >= '0' && line[i] <= '9'){
                            D *= 10;
                            D += (line[i] - '0');
                        }
                    }
                    insert(G, city1, city2, D, T);
                    //insert(BG, city1, city2, D, BT);
                    W2 = 0;
                    W1 = 0;
                }
            }
            fclose(FileIn);
            printf("DONE!\n\n");
        }
        else if(Choice == 2){
            scanf("%s", src);
        }
        else if(Choice == 3){
            scanf("%s", dist);
            printf("For Dijkistra:\n");
            strcat(fs, "For Dijkistra:\n");
            Dijkistra(G, src, dist, T);
            printPath(T, src, dist);
            printf("For BFS:\n");
            strcat(fs, "For BFS:\n");
            BFS(G, src, T);
            printPath(T, src, dist);
        }
        else if(Choice == 4){ // print the details to the output file
            // Save all students in the file (students.data)
            printf("All Answers Are Saved To (output.txt)\n");
            FileOut = fopen("output.txt", "w"); // Open the output file in write mode
            fprintf(FileOut, "%s\n", fs);
            fclose(FileOut); // Close the output file
            break;
        }
    }
    return 0; // BEST RETURN 0 IN THE WORLDDDDDDDD
}

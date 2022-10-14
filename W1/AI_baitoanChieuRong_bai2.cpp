#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Vertex {
   char label;
   bool visited;
};

int queue[5];
int rear = -1;
int front = 0;
int queueItemCount = 0;

struct Vertex* FirstVertices[5];

int adjMatrix[5][5];

int vertexCount = 0;

void insert(int data) {
   queue[++rear] = data;
   queueItemCount++;
}

int removeData() {
   queueItemCount--;
   return queue[front++]; 
}

bool isQueueEmpty() {
   return queueItemCount == 0;
}

void addVertex(char label) {
   struct Vertex* vertex = (struct Vertex*) malloc(sizeof(struct Vertex));
   vertex->label = label;  
   vertex->visited = false;     
   FirstVertices[vertexCount++] = vertex;
}

void addEdge(int start,int end) {
   adjMatrix[start][end] = 1;
   adjMatrix[end][start] = 1;
}

void displayVertex(int vertexIndex) {
   printf("%c ",FirstVertices[vertexIndex]->label);
}       
int getAdjUnvisitedVertex(int vertexIndex) {
   int i;

   for(i = 0; i<vertexCount; i++) {
      if(adjMatrix[vertexIndex][i] == 1 && FirstVertices[i]->visited == false)
         return i;
   }

   return -1;
}

void BFS() {
   int i;
   FirstVertices[0]->visited = true;
   displayVertex(0);   
   insert(0);
   int unvisitedVertex;

   while(!isQueueEmpty()) {
      int tempVertex = removeData();   
      while((unvisitedVertex = getAdjUnvisitedVertex(tempVertex)) != -1) {    
         FirstVertices[unvisitedVertex]->visited = true;
         displayVertex(unvisitedVertex);
         insert(unvisitedVertex);               
      }

   }   
     
   for(i = 0;i<vertexCount;i++) {
      FirstVertices[i]->visited = false;
   }    
}

int main() {
   int i, j;

   for(i = 0; i<MAX; i++) { 
      for(j = 0; j<MAX; j++) 
         adjMatrix[i][j] = 0;
   }

   addVertex('0');   
   addVertex('1');   
   addVertex('2');   
   addVertex('3');   
   addVertex('4');   

   addEdge(0, 1);   
   addEdge(0, 2);    
   addEdge(0, 3);    
   addEdge(1, 4);    
   addEdge(2, 4);    
   addEdge(3, 4);    

   printf("Tìm kiếm theo chiều rộng: ");

   BFS();

   return  0;}

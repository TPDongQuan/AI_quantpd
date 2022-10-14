#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Vertex {
   char label;
   bool visited;
};

int stack[5]; 
int top = -1; 

struct Vertex * FirstVertices[5];

//Sử dụng ma trận kề (adjacency matrix)
int adjMatrix[5][5];

int vertexCount = 0;

void push(int item) { 
   stack[++top] = item; 
} 

int pop() { 
   return stack[top--]; 
} 

int peek() {
   return stack[top];
}

bool isStackEmpty() {
   return top == -1;
}

//Thêm các đỉnh vào danh sách
void addVertex(char label) {
   struct Vertex* vertex = (struct Vertex*) malloc(sizeof(struct Vertex));
   vertex->label = label;  
   vertex->visited = false;     
   FirstVertices[vertexCount++] = vertex;
}

//Thêm cạnh vào mảng
void addEdge(int start,int end) {
   adjMatrix[start][end] = 1;
   adjMatrix[end][start] = 1;
}

//Hiển Thị 
void DisplayVertex(int vertexIndex) {
   printf("%c ",FirstVertices[vertexIndex]->label);
}       

int GetAdjUnvisitedVertex(int vertexIndex) {
   int i;

   for(i = 0; i<vertexCount; i++) {
      if(adjMatrix[vertexIndex][i] == 1 && FirstVertices[i]->visited == false) {
         return i;
      }
   }

   return -1;
}

void DFS() {
   int i;

   //Cho nút dầu tiên first node đã duyệt
   FirstVertices[0]->visited = true;
   DisplayVertex(0);   

   // Đưa vào ngăn sắp
   push(0);

   while(!isStackEmpty()) {
      int unvisitedVertex = GetAdjUnvisitedVertex(peek());
      if(unvisitedVertex == -1) {
         pop();
      }else {
         FirstVertices[unvisitedVertex]->visited = true;
         DisplayVertex(unvisitedVertex);
         push(unvisitedVertex);
      }
   }      
   for(i = 0;i < vertexCount;i++) {
      FirstVertices[i]->visited = false;
   }        
}

int main() {
   int i, j;

   for(i = 0; i<MAX; i++)  { 
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

   printf("Tìm kiếm theo chiều sâu: ");

   DFS(); 

   return 0;}   
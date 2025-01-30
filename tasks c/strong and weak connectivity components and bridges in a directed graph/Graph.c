#include <stdio.h>
#include <stdlib.h>

//структура списка
typedef struct Node{
    int vertex;                 //номер вершины
    struct Node* next;          //указатель на следующий узел
} Node;

//добавление элемента элемента в конец списка
void push(int vertex, Node ** head){ 

    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->next = NULL;

    if (*head == NULL)
        *head = newNode;
    else{
        Node* current = *head;
        while (current->next != NULL)
            current = current->next;
        
        current->next = newNode;
    }
}
 
//достать последний элемент списка и удалить его
int pop(Node** head) { 
    int result;
    
    if ((*head)->next == NULL) {
        result = (*head)->vertex;
        free(*head);
        *head = NULL;
    }
    else{
        Node* current = *head;

        while (current->next->next != NULL)  //current - предпоследний элемент
            current = current->next;

        result = current->next->vertex;
        free(current->next);
        current->next = NULL; 
    }
    return result;
}

// Функция для освобождения памяти, выделенной под список
void free_Stack(Node *head){
    while (head != NULL) {
        Node *p = head;
        head = head->next;
        free(p);        // Освободите память для узла
    }
}

//структура списка смежности
typedef struct adjLists{ 
    Node* adjvertex;              //номер смежной вершины             
    struct adjLists* next;          
} TadjLists;

//структура списка посещенных вершин
typedef struct visited{
    int vertex;                 //номер вершины
    struct visited* next;       //указатель на следующий узел
} Tvisited;

//структура графа
typedef struct Graph{
    int numVertices;            //количество вершин
    TadjLists* adjLists;            //список списков смежности
    Tvisited* visited;               //список посещенных вершин
} Graph;

//Функция создания графа
Graph* create_Graph(int vertices){
    Graph* graph = malloc(sizeof(Graph));
   
    TadjLists* Adj = graph->adjLists = calloc(1, sizeof(TadjLists)); //выделяем память под массив списков смежности
    Tvisited* Vis = graph->visited = calloc(1, sizeof(Tvisited));    //выделяем память под массив посещенных вершин
    
    graph->numVertices = vertices;

    for (int i = 0; i < vertices - 1; ++i){        //инициализируем массивы
        Adj = Adj->next = calloc(1, sizeof(TadjLists)); 
        Vis = Vis->next = calloc(1, sizeof(Tvisited));
    }

    return graph;
}

//Функция добавления ребра
void add_Edge(const Graph* graph, int src, int dest){

    TadjLists * tmp = graph->adjLists; //получаем список смежных вершин для вершины v  
    
    Node* newNode = malloc(sizeof(Node)); 
    newNode->vertex = dest;
    newNode->next = NULL;
    
    for(int i = 0; i < src; ++i)
        tmp = tmp->next;    
    
    newNode->next = tmp->adjvertex;   //добавляем новый узел в начало списка смежности
    tmp->adjvertex = newNode;         //меняем указатель начала списка смежности
    
}

//функция удаления списка
void free_list1(TadjLists* L){
    if(L == NULL) 
        return;
    free_list1(L->next);
    free(L);    
}

void free_list2(Tvisited* L){
    if(L == NULL) 
        return;
    free_list2(L->next);
    free(L);    
}

// Функция освобождения памяти для графа
void free_Graph(Graph* graph){  
 
    TadjLists * tmp_ = graph->adjLists;

    for (int vertex = 0; vertex < graph->numVertices; ++vertex){
        
        Node* adjNode = tmp_->adjvertex;    //получаем список смежных вершин для вершины v

        while (adjNode != NULL){
            Node* tmp = adjNode;
            adjNode = adjNode->next;
            free(tmp);
        }
        tmp_ = tmp_->next;
    }

    free_list1(graph->adjLists);//написать функцию удаления списка(для двух отдельно)
    free_list2(graph->visited);
    free(graph);
}

// Функция удаления ребра
void remove_Edge(Graph* graph, int src, int dest){

    TadjLists * tmp = graph->adjLists;
    Node* current;
    Node* prev = NULL;

    for(int i = 0; i < src; ++i)
        tmp = tmp->next; 

    current = tmp->adjvertex;

    while (current != NULL && current->vertex != dest){// Поиск узла для удаления и его предыдущего узла
        prev = current;
        current = current->next;
    }

    if (current == NULL)// Если узел не найден, выходим из функции
        return;
    
    if (prev == NULL)              // Удаление узла из списка смежности
        tmp->adjvertex = current->next; // Если узел находится в начале списка
    else
        prev->next = current->next;
    
    if(current)
        free(current);
    
}

//Функция создания неориентированного графа из ориентированного
Graph* Directed_To_Undirected(Graph* directedGraph){
    Graph* undirectedGraph = create_Graph(directedGraph->numVertices);

    TadjLists * tmp = directedGraph->adjLists;

    for (int i = 0; i < directedGraph->numVertices; ++i){

        Node* adjNode = tmp->adjvertex;

        while (adjNode != NULL) {
            add_Edge(undirectedGraph, i, adjNode->vertex);
            add_Edge(undirectedGraph, adjNode->vertex, i);
            adjNode = adjNode->next;
        }

        tmp = tmp->next;
    }

    return undirectedGraph;
}

//функция обхода в глубину с исключением ребра excludeEdgeStart-excludeEdgeEnd
void DFS_(const Graph* graph, int vertex, Tvisited* Vis, int EdgeStart, int EdgeEnd){

    TadjLists * tmp = graph->adjLists;
    Tvisited* headVis = Vis;

    for(int i = 0; i < vertex; ++i){
        tmp = tmp->next; 
        Vis = Vis->next;
    }

    Node* adjNode = tmp->adjvertex;     //получаем список смежных вершин
    
    Vis->vertex = 1; 
    
    while (adjNode != NULL){
        Tvisited* nextVis = headVis;

        for(int i = 0; i < adjNode->vertex; ++i)
            nextVis = nextVis->next;

        if (!nextVis->vertex && !(nextVis->vertex == EdgeStart && adjNode->vertex == EdgeEnd))  //если вершина не посещена, то вызываем функцию DFS для нее
            DFS_(graph, adjNode->vertex, headVis, EdgeStart, EdgeEnd);
        
        adjNode = adjNode->next;
    }

}

//Функция обхода в глубину
void DFS(const Graph* graph, int vertex, Tvisited* Vis){
    
    TadjLists * tmp = graph->adjLists;
    Tvisited* headVis = Vis;
    Tvisited* nextVis = headVis;

    for(int i = 0; i < vertex; ++i){
        tmp = tmp->next; 
        Vis = Vis->next;
    }

    Node* adjNode = tmp->adjvertex;     //получаем список смежных вершин
    Vis->vertex = 1; 
    
    while (adjNode != NULL){
        nextVis = headVis;
        for(int i = 0; i < adjNode->vertex; ++i)
            nextVis = nextVis->next;
        
        if (!nextVis->vertex)                         //если вершина не посещена, то вызываем функцию DFS для нее
            DFS(graph, adjNode->vertex, headVis);
        
        adjNode = adjNode->next;
    }
}

//подсчет слабых компонент связности
int countWCC(const Graph* graph){

    Tvisited* Vis = calloc(1, sizeof(Tvisited));
    Tvisited* headVis = Vis;
    int WCCcount = 0;

    for (int i = 0; i < graph->numVertices - 1; ++i)
       Vis = Vis->next = calloc(1, sizeof(Tvisited)); 
    
    Tvisited* current = headVis; 
    for (int i = 0; i < graph->numVertices; ++i){
        if (!current->vertex){
            DFS(graph, i, headVis);
            ++WCCcount;
        }
        current = current->next;
    }
    
    free_list2(headVis);
    
    return WCCcount;
}


//Алгоритм Косарайю

//Функция заполнения стека в порядке убывания времени выхода
void fill_in_Order(const Graph* graph, int vertex, Tvisited* Vis, Node** Stack){ 

    TadjLists * tmp = graph->adjLists;
    Tvisited* headVis = Vis;
    Tvisited* nextVis = headVis;

    for(int i = 0; i < vertex; ++i){
        tmp = tmp->next; 
        Vis = Vis->next;
    }

    Node* adjNode = tmp->adjvertex;     //получаем список смежных вершин
    Vis->vertex = 1;

    while (adjNode != NULL){
        nextVis = headVis;
        for(int i = 0; i < adjNode->vertex; ++i)
            nextVis = nextVis->next;

        if (!nextVis->vertex){
            fill_in_Order(graph, adjNode->vertex, headVis, Stack);
        }

        adjNode = adjNode->next;
    }

    push(vertex, Stack); //добавляем вершину в стек                    
}

//Функция получения транспонированного графа
Graph* get_Transpose_Graph(Graph* graph){   
    Graph* transpose = create_Graph(graph->numVertices);
    TadjLists * tmp = graph->adjLists;

    for (int vertex = 0; vertex < graph->numVertices; ++vertex){

        Node* adjNode = tmp->adjvertex;//получаем список смежных вершин
         
        while (adjNode != NULL){
            add_Edge(transpose, adjNode->vertex, vertex);  //добавляем транспонированное ребро в транспонированный граф
            adjNode = adjNode->next;
        } 

        tmp = tmp->next; 
    }

    return transpose;
}

//Функция подсчета сильно связанных компонент
int countSCC(Graph* graph){

    Node* Stack = NULL;          
    int SCCcount = 0;

    Tvisited* Vis = calloc(1, sizeof(Tvisited));
    Tvisited* headVis = Vis;
    Tvisited* nextVis;

    for (int i = 0; i < graph->numVertices - 1; ++i)
       Vis = Vis->next = calloc(1, sizeof(Tvisited));

    nextVis = headVis;
    for (int i = 0; i < graph->numVertices; ++i){           //заполняем стек
                                     
        if (!nextVis->vertex)
            fill_in_Order(graph, i, headVis, &Stack);

        nextVis = nextVis->next;
    }

    Graph* transpose = get_Transpose_Graph(graph);            //получаем транспонированный граф
    
    nextVis = headVis;
    while(nextVis != NULL){
        nextVis->vertex = 0;
        nextVis = nextVis->next;
    }

    while (Stack){                           //пока стек не пуст
        int vertex = pop(&Stack);                   //извлекаем вершину из стека
        
        nextVis = headVis;
        for(int i = 0; i < vertex; ++i)
            nextVis = nextVis->next;
        
        if (!nextVis->vertex){
            DFS(transpose, vertex, headVis);          //вызываем функцию обхода в глубину для транспонированного графа
            ++SCCcount;
        }
    }

    free_Stack(Stack);
    free_list2(headVis);
    free_Graph(transpose);

    return SCCcount;
}

//подсчет сильных мостов
int countStrongBridges(Graph* graph_d){

    int SBCount = 0;
    int initialSCC = countSCC(graph_d);         

    TadjLists * tmp = graph_d->adjLists;

    for (int i = 0; i < graph_d->numVertices; ++i){

        Node* adjNode = tmp->adjvertex;  //список смежности для вершины i
       
        while (adjNode != NULL){

            Node* nextNode = malloc(sizeof(Node));    // сохраняем копию ребра
            nextNode->vertex = adjNode->vertex;
            nextNode->next = adjNode->next;         
            
            remove_Edge(graph_d, i, adjNode->vertex); // удаляем ребро 
            int newSCC = countSCC(graph_d);           // Подсчитываем количество SCC
           
            if (newSCC > initialSCC){               // Если количество SCC увеличилось, то ребро - мост
                ++SBCount;
            }
            
            add_Edge(graph_d, i, nextNode->vertex);    // Восстанавливаем ребро
            
            adjNode = nextNode ->next;                     // Переходим к следующему узлу
            free(nextNode);
        }

        tmp = tmp->next;
    }
    return SBCount;
}

//подсчет слабых мостов
int countWeakBridges(Graph* graph_u){
    int WBCount = 0;
    int initialSCC = countWCC(graph_u);         
    
    TadjLists * tmp = graph_u->adjLists;

    for (int i = 0; i < graph_u->numVertices; ++i){

        Node* adjNode = tmp->adjvertex;

        while (adjNode != NULL){

            Node* nextNode = malloc(sizeof(Node)); // сохраняем копию ребра
            nextNode->vertex = adjNode->vertex;
            nextNode->next = adjNode->next;         
            
            remove_Edge(graph_u, i, adjNode->vertex); // удаляем ребро
            int newSCC = countWCC(graph_u);           // Подсчитываем количество SCC
           
            if (newSCC > initialSCC){               // Если количество SCC увеличилось, то ребро - мост
                ++WBCount;
            }
            
            add_Edge(graph_u, i, nextNode->vertex);    // Восстанавливаем ребро
            adjNode = nextNode->next;                     // Переходим к следующему узлу
            free(nextNode);       
        }
        tmp = tmp->next;
    }
    return WBCount;
}

//Функция ввода графа
void input_Graph(Graph* graph, int vertices){

    for (int i = 0; i < vertices; ++i){
        int edges;
        scanf("%d", &edges);
        for (int j = 0; j < edges; ++j){
            int dest;
            scanf("%d", &dest);
            add_Edge(graph, i, dest - 1);
        }
    }

}

int main(){
    int vertices;
    scanf("%d", &vertices);
    Graph* graph_d = create_Graph(vertices);

    input_Graph(graph_d, vertices);

    int sccCount = countSCC(graph_d);
    int bridgeCount = countStrongBridges(graph_d);
    
    Graph* graph_u = Directed_To_Undirected(graph_d);

    int weaklyConnectedComponents = countWCC(graph_u);
    int weakBridges = countWeakBridges(graph_u);
    
    printf("%d %d\n%d %d\n", sccCount, bridgeCount, weaklyConnectedComponents, weakBridges);
    fflush(stdout);
    
    free_Graph(graph_d);
    free_Graph(graph_u);
    return 0;
}
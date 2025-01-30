#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define N 101

//тип списка 
typedef struct list { 
    char *name, type;     
    double zn;
    struct list *next;
} list;

//инициализация списка
list *create(const double x, const char *s, const char t) { 
    
    list *tmpl = (list*) calloc(1, sizeof(list));  

    tmpl->zn = x;                                 
    tmpl->name = (char*) calloc(1, strlen(s) + 1);
    strncpy(tmpl -> name, s, strlen(s) + 1);                       
    tmpl->type = t;
    tmpl->next = NULL; 

    return tmpl;
}

//добавление элемента в конец
void add_elem(double x, const char *s, const char t, list ** head){ 

    if(*head == NULL){
        *head = create(x, s, t);
        return;
    }
    else{
        list *i = *head;                                    
        while (i -> next != NULL) i = i -> next;           
        
        list *tmpl = (list*) calloc(1, sizeof(list));    
        tmpl->zn = x;                       
        tmpl->name = (char*) calloc(1, strlen(s) + 1);
        strncpy(tmpl->name, s, strlen(s) + 1);                 
        tmpl->type = t;

        i->next = tmpl;
        tmpl -> next = NULL; 
    }
} 

//проверка существования элемента с определенным именем
int varinlist(const list *head, const char *searchName){

    if (head == NULL || searchName == NULL)
        return 0;
    
    const list *current = head;

    while (current != NULL) {
        if (strncmp(current->name, searchName, N) == 0) {
            return 1; 
        }
        current = current->next;
    }
    return 0; 
}

//удаление элемента списка с именем n
void del(const char *n, list **head)             
{
    list *tmp = *head, *p;                   
    if (head == NULL) return;                 
    while (tmp != NULL && strncmp(tmp -> name, n, N) != 0)         
    {
        p = tmp;
        tmp = tmp -> next;
    }

    if (tmp == *head)                              
    { 
        tmp = tmp -> next;
        free((*head)->name);
        free(*head);
        *head = tmp;
    }
    else if(tmp != NULL){
        p -> next = tmp -> next;
        free(tmp->name);                
        free(tmp);                            
    }       
}

int compareByName(const void* a, const void* b) {
    return strncmp(((list*)a)->name, ((list*)b)->name, N);
}

// Функция для освобождения памяти, выделенной под список
void delete_list(list *head) {
    while (head != NULL) {
        list *p = head;
        head = head->next;
        free(p->name);  // Освободите память для имени
        free(p);        // Освободите память для узла
    }
}

//отсортированный лексикографически список
void out_list_lexicographically(list* head) {
    // Сначала создаем массив указателей на элементы списка
    int count = 0;
    list* current = head;

    while (current != NULL) {
        count++;
        current = current->next;
    }

    list* listArray = (list*)calloc(1, count * sizeof(list));
    current = head;
    int i = 0;
    while (current != NULL) {
        listArray[i] = *current;
        current = current->next;
        i++;
    }

    // Сортируем массив указателей в лексикографическом порядке
    qsort(listArray, count, sizeof(list), compareByName);

    // Выводим отсортированный список
    for (i = 0; i < count; i++) {
        list* current = &listArray[i];
        printf("%s = ", current->name);
        if (current->type == 'i')
            printf("%d", (int)current->zn);
        else if (current->type == 'd') 
            printf("%f", current->zn);
        
        if (i < count - 1)
            printf(", ");
        else 
            printf("\n");
    }

    free(listArray);
}

//посмотреть последний элемент списка
list* peek_list(list* head) { 
    if(head == NULL) 
        return NULL;
          
    list* current = head; 

    while (current->next != NULL)
        current = current->next;

    list* last = malloc(sizeof(list));
    last->name = strdup(current->name);
    last->type = current->type;
    last->zn = current->zn;
    last->next = NULL;

    return last; // Возвращаем копию последнего элемента
}


//достать последний элемент списка и удалить его
list* pop_list(list** head) { 

    if (*head == NULL)
        return NULL; 
    
    list* result = malloc(sizeof(list));
    if ((*head)->next == NULL) {
           //копия последнего элемента
        result->name = strdup((*head)->name);
        result->type = (*head)->type;
        result->zn = (*head)->zn;
        result->next = NULL;

        free((*head)->name);
        free(*head);
        *head = NULL;
    }
    else{
        list* current = *head;
        while (current->next->next != NULL)  //current - предпоследний элемент
            current = current->next;

        result->name = strdup(current->next->name);
        result->type = current->next->type;
        result->zn = current->next->zn;
        result->next = NULL;

        free(current->next->name);
        free(current->next);
        current->next = NULL; 
    }

    return result;
}

//ищет элемент в списке с заданным именем и возвращает его
list* find_in_list(list** head, const char* nameToFind) { 

    if (*head == NULL || nameToFind == NULL)
        return NULL;

    list* current = *head;

    while (current != NULL) {
        if (strncmp(current->name, nameToFind, N) == 0)
            return current;                            // Возвращаем указатель на элемент, если имя совпадает
        
        current = current->next;                       // Переходим к следующему элементу
    }
    return NULL;                               // Возвращаем NULL, если элемент с заданным именем не найден
}

// Структура для элементов стека для операндов
typedef struct {
    char data[N];
    char type;
    int top;
} Stack;

// инициализация стека
void initStack(Stack *stack) {
    stack->top = -1;
}

//добавление последнего элемента
void push(Stack* stack, const char c) {
    stack->data[++(stack->top)] = c;
}

//взятие верхнего элемента
char pop(Stack *stack) {
    return stack->data[stack->top--]; 
}

//просмотр верхнего элемента
char peek(const Stack* stack) {
    return stack->data[stack->top];
}

//проверка на пустоту
int not_is_empty(const Stack* stack) {
    return stack->top != -1;
}

//функция, определяющая приоритет операций
int priority(char c){                    
    if(c == '(') return 0;       
    if(c == '=') return 1;
    if(c == '+' || c == '-') return 2;
    if(c == '*' || c == '/' || c == '%') return 3;
    if(c == '~') return 4;
    return -1;
}

//число из строки
char *numfromstr(const char infix[], int* begin){

    char *tmp = (char*)calloc(1, N);
    int i = 0;

    for(; *begin < (int)strlen(infix); ++(*begin)){
        char c = infix[*begin];
        if(isdigit(c) || c == '.')
            tmp[i++] = c;
        else{
            --(*begin);
            break;
        }
    }
    tmp[i] = '\0';
    return tmp;
}

//имя переменной из строки
char *namefromstr(const char infix[], int* begin){

    char *tmp = (char*)calloc(1, N);
    int i = 0;

    for(; *begin < (int)strlen(infix); ++(*begin)){
        char c = infix[*begin];
        if(isalnum(c) || c == '_')
            tmp[i++] = c;
        else{
            --(*begin);
            break;
        }
    }
    tmp[i] = '\0';
    return tmp;
}

//перевод в польскую запись
char *infixTOpostfix(char infix[]){
    char *postfix = (char*)calloc(1, N);
    char *operations = "+-/%%*~(=";
    Stack local;
    initStack(&local);

    int k = 0;

    for(int i = 0; i < (int)strlen(infix); ++i){

        char c = infix[i];
     
        if(isdigit(c) || c == '.'){
            char* strnum = numfromstr(infix, &i);
            
            for(int j = 0; j < (int)strlen(strnum); ++j)
                postfix[k++] = strnum[j];

            free(strnum);
            postfix[k++] = ' ';  
        }
        else if(isalnum(c) || c == '_'){
            char* strname = namefromstr(infix, &i);

            for(int j = 0; j < (int)strlen(strname); ++j)
                postfix[k++] = strname[j];
    
            free(strname);
            postfix[k++] = ' '; 

        }
        else if(c == '(') 
            push(&local, c);

        else if(c == ')'){
            while(not_is_empty(&local) && peek(&local) != '('){
                postfix[k++] = pop(&local);
                postfix[k++] = ' ';
            } 
            pop(&local);
        }

        else if(strchr(operations, c)){
            char op = c;
            if(op == '-' && (i == 0 || (i > 1 && strchr(operations, infix[i - 1])))) //проверка на унарный минус
                op = '~';  
            
            while(not_is_empty(&local) && op != '=' && (priority(op) <= priority(peek(&local))) ){ //пока приориетт операции из стека выше кладем их в постфикс
                postfix[k++] = pop(&local);
                postfix[k++] = ' ';
            }

            push(&local, op);
        }

    }
    
    while(not_is_empty(&local)){ //заносим все оставшиеся операторы из стека
            postfix[k++] = pop(&local);
            postfix[k++] = ' ';               //после последнего элемента тоже пробел
    }      

    postfix[k] = '\0';
    return postfix;        
}

//подсчет выражения 
list* local = NULL;

//добавление переменной в список для подсчета
void add_var(const char* token, list** var, list** local){
    list * tmp = find_in_list(var, token);
    
    if(*local == NULL){  
        if(*var != NULL){
            if(varinlist(*var, token))
                *local = create(tmp->zn, token, tmp->type); 
            else{                                                                                  
                *local = create(0, token, ' ');
                add_elem(0, token, ' ', var);
            }      
        }
        else{
            *local = create(0, token, ' ');
            *var = create(0, token, ' ');    
        }                                            
    }
    else{
        if(*var != NULL){
            if(varinlist(*var, token))             
                add_elem(tmp->zn, token, tmp->type, local);
            else{                                                                          
                add_elem(0, token, ' ', local);
                add_elem(0, token, ' ', var);
            }      
        }
        else{
            add_elem(0, token, ' ', local);
            *var = create(0, token, ' '); 
        }                                                                   
    } 
}

//обработка операции =
void equation(list** local, list** var){
    char* s = (char*)calloc(1, 1);

    list* a = peek_list(*local);
    int t = (a->type == 'i');       //новая переменная без типа
    free(a->name);
    free(a);

    list* result = pop_list(local);
    
    list* tmp = peek_list(*local);
   
    if(tmp->type == ' '){                              //задаем тип новой переменной в двух списках
        if(t){
            tmp->type = 'i';
            find_in_list(var, tmp->name)->type = 'i';
        }     
        else{
            tmp->type = 'd'; 
            find_in_list(var, tmp->name)->type = 'd';
        }       
    }
    
    int flag = (tmp->type == 'i');

    list* tmp1 = pop_list(local);

    if(varinlist(*var, tmp->name)){                                        //заносим результат в список var, если переменная не новая
        if (find_in_list(var, tmp->name)->type == 'd') 
            find_in_list(var, tmp1->name)->zn = result->zn;
        else
            find_in_list(var, tmp1->name)->zn = (int)result->zn;
    }
    else{      
        list* tmp2 = pop_list(local);                          
                                    
        if(flag) 
            add_elem((int)result->zn, tmp2->name, 'i', var);   
        else 
            add_elem(result->zn, tmp2->name, 'd', var);

        delete_list(tmp2);
    }
    
    if(flag)                                                               //заносм результат в локальный список
        add_elem((int)result->zn, s, 'i', local);    
    else
        add_elem(result->zn, s, 'd', local);  

    free(tmp->name);
    free(tmp);
    free(tmp1->name);
    free(tmp1);
    free(result->name);
    free(result);
    
    free(s);    
}

list* calculate(char* expression, list** var) {            //учесть крайний случай
    
    char* s = (char*)calloc(1, 1);
    char* token = strtok(expression, " ");
    
    while (token != NULL){ 
        
        if (isalnum(token[0]) || token[0] == '.' || token[0] == '_'){    //добавление чисел и переменных в стек(список) для подсчета
            
            if(strchr(token, '.')){                                 //если число и double
                double tmp = atof(token);
                if(local == NULL) local = create(tmp, s, 'd');
                else add_elem(tmp, s, 'd', &local);
            }
            else if(isalpha(token[0]) || token[0] == '_'){                           //если имя переменной
                add_var(token, var, &local);
            }
            else{                                                         //если число и int
                int tmp = atoi(token);
                if(local == NULL) local = create(tmp * 1.0, s, 'i');
                else add_elem(tmp * 1.0, s, 'i', &local);
            }            
        } 
        else{                                                                //если операция                                  
            if (token[0] == '~'){     
                list* a = pop_list(&local);
                if (a != NULL) {
                    add_elem(-a->zn, s, a->type, &local);
                    free(a->name);
                    free(a);
                }
            }           
            else if(token[0] == '='){                                         //операция =   
                equation(&local, var);                  
            } 
            else{
                double result;
                int flag = 0;
                list* a = peek_list(local); 
                if(a->type == 'd'){
                    
                    list* operand2 = pop_list(&local);
                    list* operand1 = pop_list(&local);
                   
                    switch (token[0]) {
                        case '+':
                            result = operand1->zn + operand2->zn;
                            break;
                        case '-':
                            result = operand1->zn - operand2->zn;
                            break;
                        case '*':
                            result = operand1->zn * operand2->zn;
                            break;
                        case '/':
                            result = operand1->zn / operand2->zn;    
                            break;
                    }    
                    free(operand1->name);
                    free(operand1);
                    free(operand2->name);
                    free(operand2);
                }
                else if(a->type == 'i'){   
                    list* operand2 = pop_list(&local);

                    list* b = peek_list(local);
                    if(b->type == 'i')
                        flag = 1;
                    free(b->name);
                    free(b);

                    list* operand1 = pop_list(&local);

                    switch (token[0]) {
                        case '+':
                            result = operand1->zn + operand2->zn;
                            break;
                        case '-':
                            result = operand1->zn - operand2->zn;
                            break;
                        case '*':
                            result = operand1->zn * operand2->zn;
                            break;
                        case '/':
                            if(flag)
                                result = trunc((operand1->zn / operand2->zn));
                            else
                                result = operand1->zn / operand2->zn;    
                            break;
                        case '%':
                            result = operand1->zn - trunc((operand1->zn / operand2->zn)) * operand2->zn;
                            break;
                    }
                    
                    free(operand1->name);
                    free(operand1);
                    free(operand2->name);
                    free(operand2);
                }  

                free(a->name);
                free(a);

                if(flag)                                          //добавить результат в локальный список
                    add_elem((int)result, s, 'i', &local);
                else 
                    add_elem(result, s, 'd', &local); 
            }
        } 
        token = strtok(NULL, " "); // продолжает разбивать строку по пробелам       
    }  
    
    //free(token);
    free(s);
    return peek_list(local);
}

//удаляет определенный символ из строки
void delsym (char s[], const int c) { 
  int i, j;
  for (i = j = 0; i < (int)strlen(s); ++i){
    if (s[i] != c)
      s[j++] = s[i];
  }
  s[j] = '\0';
}

int main()
{     
    list *var = NULL, *result = NULL;
    char infix[N],  *postfix;     
    
    printf(">");                          
    fgets(infix, sizeof(infix), stdin); 

    while(strncmp(infix, "exit\n", 5) != 0) {

        if(strncmp(infix, "del ", 4) == 0){                  //del
            
            infix[strlen(infix) - 1] = '\0';
            del(infix+4, &var);
            out_list_lexicographically(var);

            printf("%c", '>');                        
            fgets(infix, sizeof(infix), stdin);
            continue;
        }
 
        delsym(infix, ' ');
        postfix = infixTOpostfix(infix);           //infix->postfix
             
        result = calculate(postfix, &var); 

        if(result != NULL){
            if(result->type == 'i')
                printf("Result: %.0f\n", result->zn);
            else 
                printf("Result: %f\n", result->zn);    

            if(result->name != NULL)
                free(result->name);
            
            free(result);
        }

        out_list_lexicographically(var);

        printf(">");                        
        fgets(infix, sizeof(infix), stdin);

        free(postfix);
        
    }

    delete_list(local);
    delete_list(var);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define lenght 20

typedef struct FDresult{
    int ps_write, ps_read,sp_write, sp_read;  //ps: parent_to_son
}FDresult;

typedef struct arr_FDresult{
    int n;
    FDresult* parent, ** sons;
}arr_FDresult;

//по возрастанию
int increase(const void * a, const void * b){
    return (*(int*)a - *(int*)b);
}

void write_PID(pid_t pid){
    char child_pid_str[lenght];               
    int len = snprintf(child_pid_str, sizeof(child_pid_str), "%d ", pid);
    write(1, child_pid_str, len);
}

void write_out() {
    char buffer[50];
    int length = sprintf(buffer, "Process %d finished\n", getpid());
    write(1, buffer, length);
}

void Numbers(arr_FDresult* FD){
    char c;
    int countNum, arr_num_count;

    if(FD->parent)                               //не корень, ждет 
        read(FD->parent->ps_read, &c, 1);

    setbuf(stdin, NULL);
    scanf("%d", &countNum); 

    int* Num = malloc(countNum * sizeof(int)); //массив чисел
    for(int i = 0; i < countNum; ++i){          //заполняем массив
        setbuf(stdin, NULL);
        scanf("%d", Num + i);
    }
    qsort(Num, countNum, sizeof(int), increase);

    for(int i = 0; i < FD->n; ++i){
        write(FD->sons[i]->ps_write, "c", 1);
        
        read(FD->sons[i]->sp_read, &arr_num_count, sizeof(int)); //количество чисел 
        int* arr_num = malloc(arr_num_count* sizeof(int));            //считали числа
        read(FD->sons[i]->sp_read, arr_num, arr_num_count * sizeof(int));

        if(arr_num_count > countNum)                                        //расширение
            Num = realloc(Num, arr_num_count * sizeof(int));
    
        for(int j = 0; j < arr_num_count; ++j){
            if(j >= countNum)
                Num[j] = arr_num[j];
            else
                Num[j] += arr_num[j];
        }

        countNum = countNum < arr_num_count ? arr_num_count : countNum; //max
        free(arr_num);
    }

    for(int i = 0; i < FD->n; ++i)
        wait(NULL);

    char Nums[20]; 
    int len;
    if(!FD->parent){                                            //если нет отца...
        for(int i = 0; i < countNum; ++i){
            len = snprintf(Nums, sizeof(Nums), "%d ", Num[i]);
            write(1, Nums, len);
        }
        write(1, "\n", 1);
    }
    else{
        write(FD->parent->sp_write, &countNum, sizeof(int));
        write(FD->parent->sp_write, Num, countNum * sizeof(int));
    }
    free(Num);
}


void* create_son(FDresult* FD){
    char c;
    int childCount;                //кол-во детей
   
    setbuf(stdin, NULL);
    scanf("%d", &childCount);
    
    write_PID(getpid());

    int fd[childCount][2];                  //сын - отец
    int fd1[childCount][2];                 //наоборот

    FDresult** sons = calloc(childCount, sizeof(FDresult*));

    arr_FDresult* arr_fd = calloc(1, sizeof(arr_FDresult));
    arr_fd->n = childCount;
    arr_fd->parent = FD;
    arr_fd->sons = sons;

    if(!childCount)
       free(sons);

    for (int j = 0; j < childCount; j++){
        int childIndex;
        setbuf(stdin, NULL);
        scanf("%d", &childIndex);//ввод впустую..

        pipe(fd[j]);
        pipe(fd1[j]);

        FDresult* son = calloc(1, sizeof(FDresult));
        son->ps_read = fd1[j][0];          
        son->ps_write = fd1[j][1];
        son->sp_read = fd[j][0];
        son->sp_write = fd[j][1];
        sons[j] = son;

        pid_t pid = fork();
        
        if (pid < 0){
            perror("fork");
            exit(1);         
        } 
        else if(pid == 0){ 
            write_PID(getpid());

            write(fd[j][1], "c", 1);                 //родитель дождался сыновьи процессы и выводит \n

            FDresult* fd_parent = calloc(1, sizeof(FDresult)); //вернем из функции дескрипторы
            fd_parent->sp_write = fd[j][1];
            fd_parent->ps_write = fd1[j][1];
            fd_parent->sp_read = fd[j][0];
            fd_parent->ps_read = fd1[j][0]; 

            read(fd1[j][0], &c, 1);//ждать сообщение от родителя~!!!!!!!!!!!!!!!!!!!!!!!!!
            for(int i = 0; i < arr_fd->n; ++i)
            free(arr_fd->sons[i]);
        
            if(FD)
                free(arr_fd->parent);
            if(childCount)    
                free(arr_fd->sons);
            free(arr_fd);

            create_son(fd_parent);
        } 
    }
    
    for(int i = 0; i < childCount; ++i){          //родитель ждет пока создадутся все сыновья
        char c = 1;
        read(fd[i][0], &c, 1);
    }

    write(1, "\n", 1);
    
    for(int i = 0; i < childCount; ++i){             //отпарвить сообщение процессу и ждать ответ
        char c = 1;
        write(fd1[i][1], "c", 1);
        read(fd[i][0], &c, 1);
    }

    if(FD)                                 
        write(FD->sp_write, "c", 1);

    Numbers(arr_fd);
    
    if (childCount > 0)
        wait(NULL);

    write_out(); 

    for(int i = 0; i < arr_fd->n; ++i)
            free(arr_fd->sons[i]);
        
    if(FD)
        free(arr_fd->parent);
    if(childCount)    
        free(arr_fd->sons);
    free(arr_fd);

    for(int i = 0; i < childCount; ++i){
        
        close(fd[i][0]);
        close(fd[i][1]);
        close(fd1[i][0]);
        close(fd1[i][1]);
    }

    exit(0);
}


int main() {
    int N;                   //кол-во процессов
    scanf("%d", &N);

    create_son(NULL);

    return 0;
}
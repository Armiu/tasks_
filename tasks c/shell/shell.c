#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/file.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

//обработка зомби процессов
void handle_sigchld(int sig) {
    while (waitpid((pid_t)(-1), 0, WNOHANG) > 0) {}  // чтобы родительский не блокировался
}

//подсчет количества токенов
int count_token(char *str, char* symbol) {
    int count = 0;
    while(*str) {
        if(*str == *symbol) {
            count++;
        }
        str++;
    }
    return count + 1; // Добавляем один элемент для последней подстроки
}

//разделение строки на массив строк по разделителю symbol
char** parse_by_symbol(char *str, char *symbol, int *count) {
    int i = 0, elements_count = count_token(str, symbol);
    char *tmp_str = str, *start = str;

    char** Arr_str = malloc(elements_count * sizeof(char*));

    tmp_str = strtok(start, symbol);
    while(tmp_str) {
        if(tmp_str[strlen(tmp_str) - 1] == ' ' || tmp_str[strlen(tmp_str) - 1] == '\n') {
            tmp_str[strlen(tmp_str) - 1] = '\0';
        }
        if(tmp_str[0] == ' ') {
            tmp_str = &tmp_str[1];
        }

        Arr_str[i++] = tmp_str;
        tmp_str = strtok(NULL, symbol);
    }

    *count = i;
    return Arr_str;
}

//выполнение команды
void running_command(char *parsed_bruh) {   
    int count_args = 0;
    char **parsed_bruh_args = NULL, **argv = NULL;
    int fd, argv_size;
     
    parsed_bruh_args = parse_by_symbol(parsed_bruh, " ", &count_args); //массив токенов
    argv_size = count_args;

    for(int j = 0; j < count_args; ++j) {
        switch(parsed_bruh_args[j][0]) {
            case '<':
            case '>':
                argv_size -= 2;
                
                if(parsed_bruh_args[j][0] == '<') {
                    fd = open(parsed_bruh_args[j + 1], O_RDONLY);  //в parsed_bruh_args[j + 1] - имя файла
                    dup2(fd, 0); 
                } 
                else {
                    if(parsed_bruh_args[j][1] == '>'){                                // если >>, то добавляем в конец файла
                        fd = open(parsed_bruh_args[j + 1], O_WRONLY | O_CREAT | O_APPEND, 0666); //в parsed_bruh_args[j + 1] - имя файла, APPEND - добавляем в конец файла
                    }
                    else {
                        fd = open(parsed_bruh_args[j + 1], O_WRONLY | O_CREAT | O_TRUNC, 0666); //в parsed_bruh_args[j + 1] - имя файла, TRUNC - обрезаем до нулевого размера
                    }
                    dup2(fd, 1);        
                }

                close(fd);
                break;
            case '&':
                argv_size -= 1;  
                break;
        }
    }
    
    argv = malloc((argv_size + 1) * sizeof(char*));  // NULL в конце
    for(int i = 0; i < argv_size; ++i) {
        argv[i] = parsed_bruh_args[i];
    }    
    argv[argv_size] = NULL;

    execvp(argv[0], argv);
 
}

//закрытие дескрипторов
void close_fd_arr(int count_bruh, int fd[count_bruh - 1][2]) {
	for(int j = 0; j < count_bruh - 1; ++j) {
		close(fd[j][0]);
		close(fd[j][1]);
	}
}

void _free(char** parsed_bruh, char* str){
    free(parsed_bruh);
    free(str);
    exit(0);
}

//конвейер
void conv(char *str) {
    int count_bruh = 0;
    int background_mode = 0; 
    char **parsed_bruh = parse_by_symbol(str, "|", &count_bruh);    

    if(str[strlen(str) - 1] == '&'){                     //если последний элемент &
        background_mode = 1;  
        str[strlen(str) - 1] = '\0';
    }

    if(count_bruh > 0) {

        pid_t process; 
                                    //если одна команда или больше
        int arr_fd[count_bruh - 1][2];                    //массив дескрипторов для пайпа

        if(background_mode) {  
            pid_t ch;
            if((ch = fork())) {
                free(parsed_bruh);
                return;
            } 
            else {
                int fd = open("/dev/null", O_WRONLY);
                dup2(fd, 0);
                dup2(fd, 1);
                dup2(fd, 2);
                close(fd);
                setpgid(0, 0);

                if(fork()) {
                    free(parsed_bruh);
                    free(str);
                    exit(0);
                }
            }
            
        }

        for(int i = 0; i < count_bruh - 1; ++i) {
            pipe(arr_fd[i]);
        }     

        for(int i = 0; i < count_bruh; ++i) {
        
            if((process = fork()) == 0) {
                if(i != 0) {
                    dup2(arr_fd[i - 1][0], 0); // перенаправляем ввод из пайпа
                }
                if(i != count_bruh - 1) {
                    dup2(arr_fd[i][1], 1); // перенаправляем вывод в пайп
                }

                close_fd_arr(count_bruh, arr_fd); // dup2 создаёт новые дескрипторы, поэтому закрываем старые
                
                running_command(parsed_bruh[i]);
                _free(parsed_bruh, str);
            }
        }

        close_fd_arr(count_bruh, arr_fd);
        waitpid(process, NULL, 0);   //ждем завершения процесса
    
        free(parsed_bruh);
    }
}

int main()
{   
    struct sigaction sa;
    sa.sa_handler = handle_sigchld;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;
    sigaction(SIGCHLD, &sa, NULL);

    pid_t pid = getpid();

    char *str = NULL;
    write(1, "> ", 2); 
    size_t length = 0;
    getline(&str, &length, stdin); 
    
    while(strncmp(str, "exit\n", 5)) {
        conv(str);
        if(getpid() != pid) {
            free(str);
            exit(0);
        }
        write(1, "> ", 2); 
        getline(&str, &length, stdin); 
    }

    free(str);
    return 0;
}

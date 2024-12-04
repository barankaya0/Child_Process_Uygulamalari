#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;

    
    pid = fork();

    if (pid < 0) {
       
        perror("Fork başarısız!");
        exit(1);
    } else if (pid == 0) {
        
        printf("Child process baslatiliyor...\n");

        FILE *file = fopen("metin.txt", "r");
        if (file == NULL) {
            perror("Dosya acilamadi!");
            abort(); 
        }

        
        printf("Dosya basariyla açıldı.\n");
        fclose(file);
        exit(0);
    } else {
        
        printf("Parent process, child process'in tamamlanmasini bekliyor...\n");

        wait(&status);

        if (WIFEXITED(status)) {
            
            printf("Child process normal bir sekilde cikti, cikis kodu: %d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            
            printf("Child process bir sinyal ile sonlandı, sinyal: %d\n", WTERMSIG(status));
        } else {
            printf("Child process beklenmedik bir sekilde sonlandi.\n");
        }
    }

    return 0;
}

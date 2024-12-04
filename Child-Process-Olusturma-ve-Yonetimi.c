#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid; 
    int status; 

    
    pid = fork();

    if (pid < 0) {
        
        perror("Fork basarisiz!");
        exit(1);
    } else if (pid == 0) {
        
        printf("Child process başlatılıyor.\n");
        
        
        execlp("cat", "cat", "metin.txt", (char *)NULL);

        
        perror("execlp basarisiz!");
        exit(1);
    } else {
        
        printf("Parent process, child process'in tamamlanmasını bekliyor...\n");

        
        wait(&status);

        if (WIFEXITED(status)) {
            printf("\nChild process tamamlandı, cikis durumu: %d\n", WEXITSTATUS(status));
        } else {
            printf("Child process beklenmedik bir sekilde sonlandı.\n");
        }
    }

    return 0;
}

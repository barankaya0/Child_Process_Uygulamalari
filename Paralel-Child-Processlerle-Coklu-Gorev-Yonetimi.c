#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

void create_file(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Dosya olusturulamadi");
        exit(1);
    }
    printf("Dosya olusturuldu: %s\n", filename);
    fclose(file);
}

void write_to_file(const char *filename, const char *data) {
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        perror("Dosyaya yazilamadi");
        exit(1);
    }
    fprintf(file, "%s", data);
    printf("Dosyaya veri eklendi: %s\n", data);
    fclose(file);
}

void read_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Dosya okunamadi");
        exit(1);
    }
    printf("Dosyanın icerigi:\n");
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }
    printf("\n");
    fclose(file);
}

int main() {
    const char *filename = "metin.txt";
    pid_t pid1, pid2, pid3;

    pid1 = fork();
    if (pid1 == 0) {
        create_file(filename);
        exit(0);
    } else if (pid1 < 0) {
        perror("Child process olusturulamadi");
        exit(1);
    }

    pid2 = fork();
    if (pid2 == 0) {
        write_to_file(filename, "Merhaba!\nOdev yapiyorum.\n");
        exit(0);
    } else if (pid2 < 0) {
        perror("Child process olusturulamadi");
        exit(1);
    }

    pid3 = fork();
    if (pid3 == 0) {
        sleep(1);
        read_file(filename);
        exit(0);
    } else if (pid3 < 0) {
        perror("Child process olusturulamadi");
        exit(1);
    }

    
    for (int i = 0; i < 3; i++) {
        wait(NULL);
    }

    printf("Tum child process'ler tamamlandi.\n");
    return 0;
}

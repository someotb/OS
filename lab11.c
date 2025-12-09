/*
Написать программу на языке Си,
выполняющую следующие действия:
1) создание программного канала и порождение дочернего процесса;
2) основной процесс считывает содержимое файла, созданного в лабораторной работе №1, и передаёт его в канал;
3) дочерний процесс получает информацию через канал и при получении информации дочерний процесс производит
   работу согласно заданию по варианту из таблицы 11.3 выводит эту информацию в файл с новым именем
   передача завершается при поступлении в канал символа с кодом 26.
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int fd[2];
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(1);
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid > 0) {
        close(fd[0]);

        int in = open("lab1.c", O_RDONLY);
        if (in < 0) {
            perror("open input");
            exit(1);
        }

        char buf;
        while (read(in, &buf, 1) == 1) {
            write(fd[1], &buf, 1);
            if ((unsigned char)buf == 26) break;
        }

        close(in);
        close(fd[1]);
    } else {
        close(fd[1]); // закрываем запись, дочерний процесс только читает

        int out = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (out < 0) {
            perror("open output");
            exit(1);
        }

        char buf;
        char word[100];
        int i = 0;
        int max_a = 0;
        char max_word[100];

        while (read(fd[0], &buf, 1) == 1) {
            if ((unsigned char)buf == 26) break;

            if (buf == ' ' || buf == '\n') {
                if (i > 0) {
                    word[i] = '\0';
                    int cnt = 0;
                    for (int j = 0; j < i; j++)
                        if (word[j] == 'a') cnt++;

                    if (cnt > max_a) {
                        max_a = cnt;
                        strcpy(max_word, word);
                    }
                    i = 0; // начинаем новое слово
                }
            } else {
                if (i < 99) word[i++] = buf;
            }
        }

        // на случай если текст не закончился пробелом
        if (i > 0) {
            word[i] = '\0';
            int cnt = 0;
            for (int j = 0; j < i; j++)
                if (word[j] == 'a') cnt++;
            if (cnt > max_a) {
                max_a = cnt;
                strcpy(max_word, word);
            }
        }

    // выводим результат
    dprintf(out, "Слово: %s\nКоличество 'a': %d\n", max_word, max_a);

    close(out);
    close(fd[0]);
    }
    return 0;
}

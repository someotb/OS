#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "common.h"

int main() {
    char filename[MAX_FILENAME];
    printf("Введите имя файла: ");
    scanf("%s", filename);

    char buffer[MAX_BUFFER];
    snprintf(buffer, MAX_BUFFER, "FILENAME~%s", filename);

    int fd = open(FIFO_NAME, O_WRONLY);
    if (fd < 0) {
        perror("open fifo for write");
        exit(1);
    }

    write(fd, buffer, strlen(buffer));
    close(fd);

    // ждём ответ сервера
    fd = open(FIFO_NAME, O_RDONLY);
    if (fd < 0) {
        perror("open fifo for read");
        exit(1);
    }

    char out_name[MAX_FILENAME];
    int n = read(fd, out_name, MAX_FILENAME - 1);
    close(fd);

    if (n <= 0) {
        printf("Нет ответа от сервера\n");
        exit(1);
    }

    out_name[n] = '\0';

    // читаем результат и выводим на экран
    int in = open(out_name, O_RDONLY);
    if (in < 0) {
        perror("open result file");
        exit(1);
    }

    char c;
    while (read(in, &c, 1) == 1) {
        putchar(c);
    }

    close(in);
    return 0;
}

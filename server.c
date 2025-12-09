#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include "common.h"

int main() {
    // создаём FIFO, если его ещё нет
    mkfifo(FIFO_NAME, 0666);

    char buffer[MAX_BUFFER];

    while (1) {
        int fd = open(FIFO_NAME, O_RDONLY); // ждём клиента
        if (fd < 0) {
            perror("open fifo");
            exit(1);
        }

        // читаем строку от клиента
        int n = read(fd, buffer, MAX_BUFFER - 1);
        close(fd);
        if (n <= 0) continue;

        buffer[n] = '\0';

        // ищем строку формата "FILENAME~имя_файла"
        char *prefix = "FILENAME~";
        char *fname = strstr(buffer, prefix);
        if (!fname) continue;

        fname += strlen(prefix);

        // открываем файл, указанный клиентом
        int in = open(fname, O_RDONLY);
        if (in < 0) {
            perror("open input file");
            continue;
        }

        char content[MAX_BUFFER];
        int i = 0;
        char c;
        while (read(in, &c, 1) == 1 && i < MAX_BUFFER - 1) {
            content[i++] = c;
        }
        content[i] = '\0';
        close(in);

        // найдём слово с максимальным числом 'a'
        char word[100], max_word[100];
        int max_a = 0;
        int j = 0;
        max_word[0] = '\0';

        for (int k = 0; k <= i; k++) {
            if (content[k] == ' ' || content[k] == '\n' || content[k] == '\0') {
                if (j > 0) {
                    word[j] = '\0';
                    int count = 0;
                    for (int l = 0; l < j; l++)
                        if (word[l] == 'a') count++;
                    if (count > max_a) {
                        max_a = count;
                        strcpy(max_word, word);
                    }
                    j = 0;
                }
            } else {
                if (j < 99) word[j++] = content[k];
            }
        }

        // создаём новый файл с результатом
        char out_name[MAX_FILENAME];
        snprintf(out_name, MAX_FILENAME, "result_%s.txt", fname);

        int out = open(out_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (out < 0) {
            perror("open output file");
            continue;
        }

        dprintf(out, "Слово с макс. 'a': %s\nКоличество 'a': %d\n", max_word, max_a);
        close(out);

        // отправляем имя нового файла клиенту
        fd = open(FIFO_NAME, O_WRONLY);
        write(fd, out_name, strlen(out_name));
        close(fd);
    }

    return 0;
}

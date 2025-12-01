#define _GNU_SOURCE
#include "program.h"
#include <getopt.h>

// Функция, вызываемая при завершении программы
void print_author_info(void) {
    uid_t uid = getuid();
    struct passwd *pw = getpwuid(uid);
    const char *username = pw ? pw->pw_name : "unknown";
    fprintf(stderr, "\nАвтор: Любимов Кирилл Алексеевич, UID: %d (%s)\n", (int)uid, username);
}

// Способ 1: вывод первых 10 переменных окружения через environ
void print_env_method1(void) {
    for (int i = 0; i < 10 && environ[i] != NULL; ++i) {
        printf("%s\n", environ[i]);
    }
}

// Способ 2: вывод первых 10 переменных через getenv и список известных имён
void print_env_method2(void) {
    const char *common_vars[] = {
        "USER", "HOME", "SHELL", "PATH", "LANG", "PWD", "LOGNAME",
        "TERM", "DISPLAY", "EDITOR", "MAIL", "HOSTNAME", NULL
    };

    int count = 0;
    for (int i = 0; common_vars[i] != NULL && count < 10; ++i) {
        char *val = getenv(common_vars[i]);
        if (val != NULL) {
            printf("%s=%s\n", common_vars[i], val);
            ++count;
        }
    }
}

// Вывод содержимого файла с обработкой ошибок
int print_file(const char *filename) {
    if (!filename) {
        fprintf(stderr, "Ошибка: имя файла не задано.\n");
        return -1;
    }

    FILE *fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "Ошибка открытия файла '%s': %s\n", filename, strerror(errno));
        return -1;
    }

    char buf[4096];
    size_t n;
    while ((n = fread(buf, 1, sizeof(buf), fp)) > 0) {
        if (fwrite(buf, 1, n, stdout) != n) {
            fprintf(stderr, "Ошибка записи при выводе файла '%s': %s\n", filename, strerror(errno));
            fclose(fp);
            return -1;
        }
    }

    if (ferror(fp)) {
        fprintf(stderr, "Ошибка чтения файла '%s': %s\n", filename, strerror(errno));
        fclose(fp);
        return -1;
    }

    if (fclose(fp) != 0) {
        fprintf(stderr, "Ошибка закрытия файла '%s': %s\n", filename, strerror(errno));
        return -1;
    }

    return 0;
}

// Вывод справки по использованию
void print_usage(const char *progname) {
    fprintf(stderr, "Использование: %s [-1 | -2] [-f файл]\n", progname);
}

// Основная функция
int main(int argc, char *argv[]) {
    // Регистрируем функцию завершения
    atexit(print_author_info);

    int method1 = 0, method2 = 0;
    const char *filename = NULL;

    int opt;
    while ((opt = getopt(argc, argv, "12f:")) != -1) {
        switch (opt) {
            case '1':
                method1 = 1;
                break;
            case '2':
                method2 = 1;
                break;
            case 'f':
                filename = optarg;
                break;
            case '?':
                // getopt уже вывел сообщение об ошибке
                print_usage(argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    // Проверка: должен быть указан хотя бы один режим или файл
    if (!method1 && !method2 && filename == NULL) {
        fprintf(stderr, "Ошибка: необходимо указать -1, -2 или -f.\n");
        print_usage(argv[0]);
        exit(EXIT_FAILURE);
    }

    // Нельзя использовать оба способа одновременно
    if (method1 && method2) {
        fprintf(stderr, "Ошибка: нельзя указывать одновременно -1 и -2.\n");
        print_usage(argv[0]);
        exit(EXIT_FAILURE);
    }

    // Выполнение запрошенных действий
    if (method1) {
        print_env_method1();
    }
    if (method2) {
        print_env_method2();
    }
    if (filename) {
        if (print_file(filename) != 0) {
            exit(EXIT_FAILURE);
        }
    }

    return EXIT_SUCCESS;
}
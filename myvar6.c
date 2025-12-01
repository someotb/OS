#include <stdio.h>
#include <string.h>

#define MAX_LEN_REQUEST 50

int main() {
    char request[MAX_LEN_REQUEST];
    FILE *fp = fopen("Spravka.dat", "r");
    if (fp == NULL){
        printf("Не удалось открыть файл!\n");
        return 1;
    }
    
    printf("Введите пункт назначения: ");
    fgets(request, sizeof(request), stdin);
    request[strcspn(request, "\n")] = 0;  // убираем '\n'

    char data[100];
    char *token;
    char *flight_number;
    char *plain_type;
    int found = 0;

    while (fgets(data, sizeof(data), fp) != NULL) {
        data[strcspn(data, "\n")] = 0;   // убираем '\n' из строки файла
        token = strtok(data, ";");       // название пункта
        flight_number = strtok(NULL, ";"); // номер рейса
        plain_type = strtok(NULL, ";"); // Типо самолета

        if (strcmp(token, request) == 0) {
            printf("Рейс найден:\n");
            printf("Пункт назначения: %s\n", request);
            printf("Модель самолета:%s\n", plain_type);
            printf("Номер рейса:%s\n", flight_number);
            found = 1;
        }
    }

    if (!found) {
        printf("Рейс не найден!\n");
    }

    fclose(fp);
    return 0;
}

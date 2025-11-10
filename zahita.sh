if [ $# -eq 2 ]; then
        if [ -d $1 ]; then
                dir=$1
                echo -e "Кол-во файлов принадлежащие текущему пользователю: $(find "$dir" -user $(whoami)  2>/dev/null | wc -l)\n" #через find ищем в нашей директории файлы принадлежащие тек. пользователю и выводим кол-во через wc
                echo -e "Кол-во подкаталогов:  $(find "$dir" -type d | wc -l)\n" #через find ищем в нашей директории -d и выводим кол-во через wc
                echo -e "Кол-во обычных файлов:  $(find "$dir" -type f | wc -l)\n" #через find ищем в нашей директории -f и выводим кол-во через wc
        else
                echo -e "Ошибка "$dir" - не каталог\n"
        fi

        file_name=$2
        if [ -e "$1/$file_name" ]; then
                echo -e "Файл "$file_name" существует\n"
                touch file_1.txt
                sed -n '4,5p' "$file_name" > file_1.txt
                echo -e "Вывод файла "$file_name": "
                cat file_1.txt
        fi
else
        echo -e "Необходимо вводить 2 аргумента!\n"
fi
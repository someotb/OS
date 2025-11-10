while getopts ":fm:" opt; do
    case $opt in
        f)
            echo "Введите команду: "
            read cmd
            echo "Выполняю команду: $cmd"
            eval "$cmd"
            ;;
        m)
            filename="$NAME"
            if [ -f "$filename" ]; then
                echo "Содержимое файла '$filename': "
                cat "$filename"
            else
                echo "Файл '$filename' - не существует"
            fi
            ;;
        \?)
            echo "Недопустимая опция: -$NAME"
            echo "Использование: $0 [-f] [-m filename]"
            exit 1
            ;;
        :)
            echo "Опция -m требует аргумент."
            exit 1
            ;;
    esac
done

if [ "$#" -gt 0 ]; then
    while getopts ":fm:" opt; do
        case $opt in
            f)
                echo "Введите команду: "
                read cmd
                echo "Выполняю команду: $cmd"
                eval "$cmd"
                ;;
            m)
                filename="$OPTARG"
                if [ -f "$filename" ]; then
                    echo "Содержимое файла '$filename': "
                    cat "$filename"
                else
                    echo "Файл '$filename' - не существует"
                fi
                ;;
            \?)
                echo "Недопустимая опция: -$OPTARG"
                echo "Использование: $0 [-f] [-m filename]"
                exit 1
                ;;
            :)
                echo "Опция -m требует аргумент."
                exit 1
                ;;
        esac
    done
else
    echo "Использование: $0 [-f] [-m filename]"   
fi
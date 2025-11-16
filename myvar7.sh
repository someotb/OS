if [[ -z "$1" || ! -d "$1" ]]; then
    echo "Ошибка: укажите существующий каталог"
    echo "Использование: $0 <каталог>"
    exit 1
fi

DIR="$1"
TMPFILE="/tmp/dirlist_$$.txt"  # $$ — PID текущего процесса

ls "$DIR" > "$TMPFILE"

{
    while IFS= read -r line; do  # IFS= предотвращает обрезание пробелов в начале/конце строки. -r — отключает интерпретацию \ как escape-символ.
        echo "$line"
        sleep 1
    done < "$TMPFILE"
} | dialog --progressbox "Оглавление каталога: $DIR" 20 50

rm -f "$TMPFILE"
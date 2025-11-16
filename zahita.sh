noopts=1

while getopts ":ec::d:" opt; do
    noopts=0
    case $opt in
        e)
            echo "exp(0) = 1"
            ;;
        c)
            num=${OPTARG:-1}
            echo "Создаю $num файлов"
            for i in $(seq $num); do
                f="file_$i"
                touch "$f"
                chmod a-w "$f"
            done
            ;;
        d)
            echo "Удаляю пустые файлы в $OPTARG"
            find "$OPTARG" -type f -empty -print -delete
            ;;
        \?)
            echo "Неизвестная опция"
            ;;
    esac
done

if (( noopts )); then
    echo "Опций нет, получаю имя узла:"
    hostname
fi

#!/bin/bash

set -m

# Долгоиграющий процесс
sleep 10 &
PID=$!
echo "Долгоиграющий процесс запущен. PID=$PID"

while true; do
    clear
    echo "Меню управления процессом PID=$PID:"
    echo "1) Остановить процесс"
    echo "2) Продолжить выполнение на заднем плане (bg)"
    echo "3) Перевести на передний план (fg)"
    echo "4) Завершить процесс"
    echo "5) Завершить принудительно"
    echo "0) Выйти из меню"
    echo
    read -p "Выберите опцию: " choice

    case $choice in
        1)
            if kill -0 $PID 2>/dev/null; then
                kill -STOP $PID
                echo "Процесс $PID приостановлен"
            else
                echo "Процесс $PID уже завершён"
                break
            fi
            read -p "Нажмите Enter, чтобы продолжить..."
            ;;
        2)
            if kill -0 $PID 2>/dev/null; then
                kill -CONT $PID
                echo "Процесс $PID продолжен"
            else
                echo "Процесс $PID уже завершён"
                break
            fi
            read -p "Нажмите Enter, чтобы продолжить..."
            ;;
        3)
            if kill -0 $PID 2>/dev/null; then
                echo "Перевод процесса на передний план. Скрипт приостановится до завершения процесса или перевода его обратно в фон."
                fg %1
                echo "Процесс завершился"
                break
            else
                echo "Процесс $PID уже завершён"
            fi
            read -p "Нажмите Enter, чтобы продолжить..."
            ;;
        4)
            if kill -0 $PID 2>/dev/null; then
                kill $PID
                echo "Процесс $PID завершён"
            else
                echo "Процесс $PID уже завершён"
            fi
            break
            ;;
        5)
            if kill -0 $PID 2>/dev/null; then
                kill -9 $PID
                echo "Процесс $PID завершён принудительно"
            else
                echo "Процесс $PID уже завершён"
            fi
            break
            ;;
        0)
            echo "Выход"
            break
            ;;
        *)
            echo "Неверный выбор"
            read -p "Нажмите Enter, чтобы продолжить..."
            ;;
    esac
done

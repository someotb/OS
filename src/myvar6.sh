#!/bin/bash

# Долгоиграющий процесс — поиск "namespace" в .h файлах
sleep 1000 &
PID=$!
echo "Долгоиграющий процесс запущен. PID=$PID"

while true; do
    clear
    echo "Меню управления процессом PID=$PID:"
    echo "1) Остановить процесс"
    echo "2) Продолжить выполнение"
    echo "3) Завершить процесс"
    echo "4) Завершить принудительно"
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
            fi
            read -p "Нажмите Enter, чтобы продолжить..."
            ;;
        2)
            if kill -0 $PID 2>/dev/null; then
                kill -CONT $PID
                echo "Процесс $PID продолжен"
            else
                echo "Процесс $PID уже завершён"
            fi
            read -p "Нажмите Enter, чтобы продолжить..."
            ;;
        3)
            if kill -0 $PID 2>/dev/null; then
                kill $PID
                echo "Процесс $PID завершён"
            else
                echo "Процесс $PID уже завершён"
            fi
            read -p "Нажмите Enter, чтобы продолжить..."
            ;;
        4)
            if kill -0 $PID 2>/dev/null; then
                kill -9 $PID
                echo "Процесс $PID завершён принудительно"
            else
                echo "Процесс $PID уже завершён"
            fi
            read -p "Нажмите Enter, чтобы продолжить..."
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

user_id=$UID

if [ -z "$user_id" ]; then
	printf "Вы ввели непрвильно!"
fi

printf "Введите число на которое будет разделен ваш UID: "
read delitel
printf "Результат деления $(($user_id/$delitel))\n"
res=$(($user_id/$delitel)) 

mkdir $HOME/"$res"
printf "Создана папка $res по пути  $HOME\n"
printf "Команда ls в $HOME:\n"
ls $HOME

cp $0 $HOME/"$res"
printf "Проверим папку $res\n"
ls $HOME/"$res"

printf "Запретим запись в файл\n"
chmod a-w $HOME/"$res"/var5.sh
ls -l $HOME/"$res"

printf "Вы хотите удалить следы скрипта? Если да, то напишите что-то, иначе оставьте поле пустым: "
read chose
if [ -z chose ]; then
	exit
else
	rm -rf $HOME/"$res"
fi

printf "Проверим удалился ли каталог\n"
ls $HOME

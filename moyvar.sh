path="";

if [ $# -eq 1 ]; then
        path=$1
else
        path="/usr/bin"
fi

echo "$path"

for i in "$path"/*;
do
        if [ -x "$i" ]; then
                whatis "$i"
                echo "***************"
        else
                file "$i"
                echo "---------------------"
        fi
done
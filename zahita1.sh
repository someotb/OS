filename="encrypted.txt"
echo "Create an encrypted file in $PWD"
umask 077
> "$filename"

if [ "$#" -gt 0 ]; then
    for file in "$@"; do
    encrypted=$(cat "$file" | tr 'a-zA-Z' 'f-za-eF-ZA-E' | tr -d '\n')
    echo "$encrypted" >> "$filename"
done
else
    if [ -t 0 ]; then
        echo "Enter a text to encrypt (Ctrl+D to end input): " 
    fi
    cat | tr 'a-zA-Z' 'f-za-eF-ZA-E' > $filename
fi
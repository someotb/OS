filename="decrypted.txt"
echo "Create an decrypted file in $PWD"
umask 077
> "$filename"

if [ "$#" -gt 0 ]; then
    for file in "$@"; do
    tr 'f-za-eF-ZA-E' 'a-zA-Z' < "$file" >> "$filename"
done
else
    if [ -t 0 ]; then
        echo "Enter a text to decrypt (Ctrl+D to end input): " 
    fi
    cat | tr 'f-za-eF-ZA-E' 'a-zA-Z' > $filename
fi
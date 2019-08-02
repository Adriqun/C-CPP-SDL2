gcc -Wall -g -O0 -fPIC -c sh.c
gcc -g -shared sh.o -o libsh.so -Wl,--version-script,script
readelf -S libsh.so
echo ""
echo ""
readelf -V libsh.so
echo ""
echo ""
readelf --symbols libsh.so | grep function

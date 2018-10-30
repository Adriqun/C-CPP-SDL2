program mat;

uses matrix;

var s : Square;
var n : integer;
var d : double;

begin
    n := 5; // It would be matrix 5x5
    setSeed();
    create(s, n);
    load(s, 'file.txt');
    print(s);
    d := getDet(s);
    write('Det=', d:2:2);
end.


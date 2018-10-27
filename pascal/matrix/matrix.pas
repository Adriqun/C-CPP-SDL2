program matrix;

uses sysutils;

var tab : array of array of integer;
var i, j, result : integer;
var ffile : text;

begin
  SetLength(tab, 3, 3);

  // Read input.
  for i := low(tab) to high(tab) do
    for j := low(tab[i]) to high(tab[i]) do
      read(tab[i,j]);

  // Calculate.
  result := tab[0,0]*tab[1,1]*tab[2,2];
  result := result + tab[0,1]*tab[1,2]*tab[2,0];
  result := result + tab[0,2]*tab[1,0]*tab[2,1];

  result := result + (tab[2,0]*tab[1,1]*tab[0,2])*-1;
  result := result + (tab[2,1]*tab[1,2]*tab[0,0])*-1;
  result := result + (tab[2,2]*tab[1,0]*tab[0,1])*-1;

  // Write output.
  assign(ffile, 'result.txt');
  rewrite(ffile);

  for i := low(tab) to high(tab) do
  begin
    for j := low(tab[i]) to high(tab[i]) do
      write(ffile, tab[i,j], ' ');
    writeln(ffile);
  end;
  writeln(ffile, 'det=', result);
  close(ffile);
end.

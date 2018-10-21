program main;

uses sysutils;

var tab2D : array[0..15,0..15] of integer;
var i, j, k : integer;

var str : string;
var s : integer;

begin
  for i := low(tab2D) to high(tab2D) do
  begin
      for j := low(tab2D[i]) to high(tab2D[i]) do
      begin
           //tab2D[i,j] := (i*10)+(j+1); // in sort
           tab2D[i,j] := (i+1)*(j+1);

           str := IntToStr(tab2D[i,j]);
           s := 3 - Length(str);

           write(str);
           for k := 0 to s do
               write(' ');
      end;
      writeln();
  end;
end.


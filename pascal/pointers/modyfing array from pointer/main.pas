program main;

const max = 5;
var i, j : integer;
var tab : array [0..max] of integer;
var tab2 : array [0..max] of integer;
var ptr : ^integer;

begin
  for i := 0 to max-1 do
      tab[i] := i + 1;

  //ptr := @tab[0]; // or @tab
  //writeln(ptr^);
  for i := 0 to max-1 do
  begin
    //ptr := ptr + 1;
    ptr := @tab[i];
    writeln(ptr^);
  end;


  ptr := @tab2;
  for i := 0 to max-1 do
  begin
    (ptr+i)^ := i + 1;
     writeln(tab2[i]);
  end;
end.


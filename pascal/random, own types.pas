program type_p;

uses sysutils;

const min = 0; max = 10;
type Tab = array[min..max] of integer;
str = string[20];
var warunek : boolean;

var t : Tab;
var i, j : integer;

begin
  randomize();

  for i := min to max do
  begin
  //  t[i] := random(100);
  end;

  warunek := true;
  while warunek do
  begin
    warunek := false;
    for i := min to max do
        for j := min to i-1 do
        begin
          if t[i] = t[j] then
          begin
             warunek := true;
             t[j] := random(11);
          end;
        end;
  end;

  for i := min to max do
    writeln(t[i]);
end.


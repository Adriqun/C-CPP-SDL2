program main;

const max = 10;
var i : integer;
var ptr : ^integer;
var arrow : ^integer;

begin
  // allocate array of size max
  GetMem(ptr, sizeof(integer)*max);

  for i := 0 to max-2 do
      ptr[i] := i + 1;
  ptr[max-1] := 0;

  arrow := ptr;
  while not(arrow^ = 0) do
  begin
    writeln(arrow^);
    arrow := arrow + 1;
  end;

  // deallocate array
  FreeMem(ptr, sizeof(integer)*max);
end.


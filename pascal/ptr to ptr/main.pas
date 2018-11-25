program main;

type intPtr = ^integer;
var i, j : integer;
var p1 : intPtr;    // 1D
var p2 : ^integer;  // 1D
var pp : ^intPtr;   // 2D

begin
  i := 11;
  p1 := @i;
  p2 := p1;
  pp := @p2;

  writeln(integer(@i));
  writeln(pp^^);

end.


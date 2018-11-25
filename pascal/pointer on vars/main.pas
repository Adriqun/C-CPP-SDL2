program main;
uses sysutils;

var i, j : integer;
var p : ^integer; // pointer

begin
  i := 10;
  j := 7;
  writeln('Address: ', Integer(@i));
  writeln('Address: ', Integer(@j));

  p := @i;
  p^ := 5;
  writeln(i);
end.


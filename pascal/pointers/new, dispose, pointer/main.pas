program main;

var i, j : integer;
var p : ^integer;

begin
     // allocate
     new(p);

     // ascribe
     p^ := 10;

     // address of pointer
     writeln('Address of ptr: ', integer(@p));

     // value of pointer
     writeln('Value of ptr: ', p^);

     // free
     dispose(p);
     p := NIL;
end.


program main;

uses sysutils;

var tab : array of integer;
var size : integer;
var i : integer;
var j : integer;
var current : integer;

var myfile : TEXT;
var str : string;

begin
  size := 10;
  SetLength(tab, size);

  assign(myfile, 'file.txt');
  reset(myfile);
  //while not eof(myfile) do
  //begin
  //  readln(myfile, str);
  //  writeln(str);
  //end;

  // Read n values from file
  for i := low(tab) to high(tab) do
  begin
      readln(myfile, str);
      tab[i] := StrToInt(str);
  end;

  // Close and open again
  close(myfile);
  assign(myfile, 'file.txt');
  rewrite(myfile);

  // Sort
  for i := low(tab) to high(tab) do
  begin
      for j := low(tab) to high(tab) do
      begin
          if tab[i] < tab[j] then
          begin
             current := tab[i];
             tab[i] := tab[j];
             tab[j] := current;
          end;
      end;
  end;

  for i := low(tab) to high(tab) do
      writeln(myfile, tab[i]);

  // Close
  close(myfile);

end.


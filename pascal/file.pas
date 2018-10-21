program plik;
uses sysutils;

var myfile : TEXT;
var str : string;

begin
  assign(myfile, 'file.txt');// stworz

  //rewrite(myfile);           // otwiera plik w trybie zapisu
  //append(myfile);
  //writeln(myfile, '303');

  reset(myfile); // otwiera plik w trybie do odczytu
  while not eof(myfile) do
        begin
           readln(myfile, str);
           writeln(str);
        end;
  close(myfile);
end.


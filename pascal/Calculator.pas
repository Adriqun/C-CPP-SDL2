program Calculator;

uses sysutils;

var size : integer;   // Number of parameters.
var nr : integer;     // Current number of parameter.
var i : integer;
var result : double;
var language : string;// Language PL/ENG

type optionsArray = array of string;
var options : optionsArray;

begin
  nr := 1; // start reading parameters starting from 1.
  language := 'PL';
  size := ParamCount;

    // There has to be at least 3 parameters... (+1 with path)
    if size < 3 then
       begin
       writeln('Error: Number of parameters should be at least 3!');
       exit;
       end;

//------ Setting Language
    SetLength(options, 4);
    options[0] := 'd'; // dodawanie
    options[1] := 'o'; // odejmowanie
    options[2] := 'm'; // mnozenie
    options[3] := 'dz';// dzielenie

    if ParamStr(nr) = 'ENG' then
        begin
            options[0] := 'a'; // adding
            options[1] := 's'; // substracting
            options[2] := 'm'; // multiplying
            options[3] := 'd'; // dividing
            language := 'ENG';
            nr := 2;
            writeln('English language selected.');
        end
     else if ParamStr(nr) = 'PL' then
        begin
        nr := 2;
        writeln('Wybrano jezyk polski.');
        end;
//------

     // Check if next parameter is an option then calculate.
     result := StrToInt(ParamStr(nr + 1));
     if ParamStr(nr) = options[0] then
        begin
        for i := nr+2 to size do
              result := result + StrToInt(ParamStr(i));
        end
     else if ParamStr(nr) = options[1] then
        begin
        for i := nr+2 to size do
              result := result - StrToInt(ParamStr(i));
        end
     else if ParamStr(nr) = options[2] then
        begin
        for i := nr+2 to size do
              result := result * StrToInt(ParamStr(i));
        end
     else if ParamStr(nr) = options[3] then
        begin
        for i := nr+2 to size do
              result := result / StrToInt(ParamStr(i));
        end
     else
        begin
        if language = 'ENG' then
        begin
           writeln('Error: Option is not recognized!');
        end
        else if language = 'PL' then
        begin
           writeln('Blad: Opcja nie zostala poprawnie rozpoznana!');
        end;
        exit;
        end;

     if language = 'ENG' then
     begin
        writeln('Result = ', result:2:2);
     end
     else
        writeln('Wynik = ', result:2:2);
end.


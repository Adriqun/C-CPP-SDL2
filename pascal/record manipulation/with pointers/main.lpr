program main;

uses auto;

var autoTab : TAutoArray;
var tabSize : integer = 10;
begin
      fill();
      if readFromFile(autoTab, 'carshowroom.dat', tabSize) then
      begin
         replace(autoTab[0], autoTab[1]);
         writeln('AutoArray sorted:');
         bubblesort(autoTab, tabSize);
         printAutoArray(autoTab, tabSize);
      end;
      destroyAutoArray(autoTab, tabSize);
end.


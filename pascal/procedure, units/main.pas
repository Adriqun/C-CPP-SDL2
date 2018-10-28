program myunit;

uses hellofile;

//var name : string;
var mytab : ttab;

begin
  randomize();
  //name := 'John';
  //hello(name);
  fill(mytab);
  bubblesort(mytab, false);
  //mytab := generate();
  print(mytab);
end.


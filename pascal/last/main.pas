program exString;
uses sysutils;
var
   str1, str2, str3 : ansistring;
   str4: string;
   len: integer;

begin
   str1 := 'Hello ';
   str2 := 'There!';
   //appendstr( str1, string(str2[0]) );
   writeln( 'appendstr( str1, str2) ' , str1 );

   str1 :=Concat(str1, *str2[0]);
   writeln( 'appendstr( str1, str2) ' , str1 );
end.

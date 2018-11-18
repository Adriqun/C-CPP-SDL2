program main;

uses auto;

var autoTab : TAutoArray;

begin
	//Set Arrays.
	fill();
        // 1
	//getAutoArray(autoTab, 10);
	//printAutoArray(autoTab);
        //saveToFile(autoTab);

        // 2
        if readFromFile(autoTab, 'carshowroom.dat', 10) then
        begin
           //printAutoArray(autoTab);
           //replace(autoTab[0], autoTab[1]);
           //writeln('Auto[0] after changes:');
           //printAuto(autoTab[0]);
           writeln('AutoArray sorted:');
           sort(autoTab);
           printAutoArray(autoTab);
        end;

end.


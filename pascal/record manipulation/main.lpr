program main;

uses auto;

var autoTab : TAutoArray;

begin
	//Set Arrays.
	fill();

	//getAutoArray(autoTab, 10);
	//printAutoArray(autoTab);

        saveToFile(autoTab);
        if readFromFile(autoTab, 'dupa.dat') then
           printAutoArray(autoTab)
end.


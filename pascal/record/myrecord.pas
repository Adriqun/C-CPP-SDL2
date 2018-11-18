program myrecord;

uses sysutils;

Type TAuto = record
	color : string;
	brand : string;
	capacity : real;
	end;

var passat : TAuto;


begin
	passat.color := 'black';
	passat.brand := 'VW';
	passat.capacity := 1.6;

	with passat do
	begin
		writeln('Color: ', color);
		writeln('Brand: ', brand);
		writeln('Capacity: ', capacity:3:3);
	end;
end.


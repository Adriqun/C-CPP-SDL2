unit auto;

interface
	uses
	  Classes, SysUtils;

        const MAX = 20;

	Type TAuto = record
		color : string[MAX];
		brand : string[MAX];
		capacity : real;
		end;

	Type TAutoArray = array of TAuto;

	var colors : array of string;
	var brands : array of string;
	var capacities : array of real;

	procedure fill();
	function getAuto(const color, brand : string; const capacity : real) : TAuto;
	//function doAuto() : TAuto;
	procedure printAuto(const auto : TAuto);
	procedure getAutoArray(var auto : TAutoArray; num : integer);
	procedure printAutoArray(const auto : TAutoArray);
    procedure saveToFile(const auto : TAutoArray);
	function exists(filename : string) : boolean;
	function readFromFile(const auto : TAutoArray; filename : string) : boolean;

implementation
	procedure fill();
		begin
			SetLength(colors, 5);
			SetLength(brands, 5);
			SetLength(capacities, 5);
			colors[0] := 'Black';
			colors[1] := 'Green';
			colors[2] := 'White';
			colors[3] := 'Blue';
			colors[4] := 'Red';
			brands[0] := 'Mercedes';
			brands[1] := 'VG';
			brands[2] := 'Fiat';
			brands[3] := 'Opel';
			brands[4] := 'Ford';
			capacities[0] := 2.0;
			capacities[1] := 1.6;
			capacities[2] := 2.2;
			capacities[3] := 3.0;
			capacities[4] := 1.9;
		end;
		
	function getAuto(const color, brand : string; const capacity : real) : TAuto;
		var newAuto : TAuto;
		begin
			newAuto.color := color;
			newAuto.brand := brand;
			newAuto.capacity := capacity;
			getAuto := newAuto;
		end;

	//function doAuto() : TAuto;
		//var newAuto : TAuto;
		//begin
			//readln(newAuto.color);
			//readln(newAuto.brand);
			//readln(newAuto.capacity);
                        //doAuto := newAuto;
		//end;

	procedure printAuto(const auto : TAuto);
		begin
			writeln('Color: ', auto.color);
			writeln('Brand: ', auto.brand);
			writeln('Capacity: ', auto.capacity:3:3);
		end;

	procedure getAutoArray(var auto : TAutoArray; num : integer);
		var i, s : integer;
		begin
			s := Length(colors)-1;
			SetLength(auto, num);
			for i := 0 to num-1 do
				auto[i] := getAuto(colors[random(s)], brands[random(s)], capacities[random(s)]);
		end;

	procedure printAutoArray(const auto : TAutoArray);
		var i : integer;
		begin
			for i := 0 to Length(auto)-1 do
			begin
				writeln(i, '.');
				printAuto(auto[i]);
                                writeln();
			end;
		end;

	procedure saveToFile(const auto : TAutoArray);
		var i : integer; ffile : File of TAuto;
		begin
			assign(ffile, 'car showroom.dat');
			rewrite(ffile);
			for i := low(auto) to high(auto) do
				write(ffile, auto[i]);
			close(ffile);
		end;

	function exists(filename : string) : boolean;
		var ffile : file of TAuto;
		begin
			{$I-}
				assign(ffile, filename);
				reset(ffile);
				close(ffile);
			{$I+}
			exists := (IOResult=0);
		end;

	function readFromFile(const auto : TAutoArray; filename : string) : boolean;
		var ffile : file of TAuto;
		var i : integer;
		begin
			if exists(filename) then
			begin
				assign(ffile, filename);
				reset(ffile);
				for i := low(auto) to high(auto) do
					read(ffile, auto[i]);
				close(ffile);
			end
			else
			begin
			readFromFile := false;
			end;
		end;
end.

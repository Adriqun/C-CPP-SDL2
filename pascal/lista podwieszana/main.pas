program main;
uses sysutils;

const MAX = 20;
const MAXC = 10;
type PBrand = ^TBrand;
     PModel = ^TModel;
TModel = record
	model : string[MAX];
	color : string[MAX];
	year : integer;
	next : PModel;
	end;

TBrand = record
	brand : string[MAX];
	next : PBrand;
	prev : PBrand;
	models : PModel;
	end;


var colors : array [0..MAXC] of string;
var years : array [0..MAXC] of integer;

procedure fill();
	begin
		Randomize();
		colors[0] := 'Yellow';
		colors[1] := 'Black';
		colors[2] := 'Blue';
		colors[3] := 'Brown';
		colors[4] := 'Red';
		colors[5] := 'Purple';
		colors[6] := 'Violet';
		colors[7] := 'Green';
		colors[8] := 'Gray';
		colors[9] := 'Orange';

		years[0] := 1998;
		years[1] := 1999;
		years[2] := 2000;
		years[3] := 2001;
		years[4] := 2002;
		years[5] := 2003;
		years[6] := 2004;
		years[7] := 1990;
		years[8] := 1991;
		years[9] := 1992;
	end;


function get() : PModel; // get new model
	var model : PModel;
	begin
		new(model);
		model^.model := IntToStr(random(MAXC));
		model^.color := colors[random(MAXC)];
		model^.year := years[random(MAXC)];
		model^.next := NIL;
		get := model;
	end;

function find(var list : PBrand; brand : string) : PBrand;
	var buffer : PBrand;
	begin
		buffer := list;
		while (buffer <> NIL) do
		begin
			if(buffer^.brand = brand) then
			begin
				find := buffer;
				exit;
			end;
			buffer := buffer^.next;
		end;
		buffer := NIL;
	end;

procedure add(var list : PBrand; brand : string); // adds to correct brand, if brand is found.
	var buffer : PBrand;
	var tmp : PModel;
	begin
		buffer := find(list, brand);
		if buffer <> NIL then
		begin
			if buffer^.models = NIL then
			begin
				buffer^.models := get();
			end
			else
			begin
				tmp := buffer^.models;
				while (tmp^.next <> NIL) do
					tmp := tmp^.next; // go at the end of the list
				tmp^.next := get();
			end;
		end;
	end;

procedure push(var list : PBrand; str : string);
	var tmp, buffer, stp : PBrand;
	begin
		new(tmp);
		tmp^.brand := str;
		tmp^.next := NIL;
		tmp^.prev := NIL;
		tmp^.models := NIL;

		if list = NIL then
		begin
			list := tmp;
		end
		else
		begin
			// [] <-> [] <-> []
			buffer := list;
			while(buffer^.next <> NIL) do
			begin
				if (buffer^.next^.brand[1] > str[1]) then // a > b
					break;
				buffer := buffer^.next;
			end;

			if buffer^.next = NIL then // we are at the end of the list
			begin
				tmp^.prev := buffer; // set previous
				buffer^.next := tmp; // add new one
			end
			else
			begin // we want to place new one between buffer and stp
				stp := buffer^.next;
				stp^.prev := tmp;	// prev is now new one
				buffer^.next := tmp;// next is now new one
				tmp^.next := stp;
				tmp^.prev := buffer;
			end;
		end;
	end;

function compare(var a, b : TModel) : boolean;
	begin
		compare := true;
		if not(a.model = b.model) then
			compare := false;
		if not(a.color = b.color) then
			compare := false;
		if not(a.year = b.year) then
			compare := false;
	end;

procedure delete(var node : PModel; var model : TModel); // removes model from brand
	var buffer, spt : PModel;
	begin
		if node <> NIL then
		begin
			if compare(node^, model) then // first one to delete
			begin
				buffer := node^.next;
				dispose(node);
				node := buffer;
			end
			else
			begin
				buffer := node;
				while(buffer^.next <> NIL) do
				begin
					if compare(buffer^.next^, model) then
						break;
					buffer := buffer^.next;
				end;

				if buffer^.next <> NIL then // found
				begin
					spt := buffer^.next;
					buffer^.next := buffer^.next^.next;
					dispose(spt);
					spt := NIL;
				end
			end;
		end;
	end;

procedure remove(var node : PBrand; brand : string; var model : TModel); // removes model from brand or brand
	var buffer, n, p : PBrand;
	var tmp : PModel;
	begin
		buffer := find(node, brand);
		if buffer <> NIL then
		begin
			if buffer^.models = NIL then // remove brand
			begin
				p := buffer^.prev;
				n := buffer^.next;

				if p <> NIL then
					p^.next := n;

				if n <> NIL then
					n^.prev := p;

				dispose(buffer);
				buffer := NIL;
			end
			else // brand contains models
			begin
				delete(buffer^.models, model);
			end;
		end;
	end;


procedure printb(var node : PBrand); // print brand
	begin
		if (node <> NIL) then
			writeln('Brand: ', node^.brand);
	end;

procedure prints(var node : PBrand); // print model of brand
	var buffer : PModel;
	begin
		buffer := node^.models;
		if buffer = NIL then
		begin
			writeln('	Empty');
			writeln();
		end
		else
		begin
			while buffer <> NIL do
			begin
				writeln('	Model: ', buffer^.model);
				writeln('	Color: ', buffer^.color);
				writeln('	Year: ', buffer^.year);
				writeln();
				buffer := buffer^.next;
			end;
		end;
	end;

procedure print(var node : PBrand); // print model of brand
	var buffer : PBrand;
	begin
		buffer := node;
		while buffer <> NIL do
		begin
			printb(buffer);
			prints(buffer);
			buffer := buffer^.next;
		end;
	end;	

var head : PBrand = NIL;
var i : integer = 0;
var mm : TModel;

begin
	fill();
	push(head, 'Polonez');
	push(head, 'Pontiac');
	//push(head, 'Porshe');
	push(head, 'Peuegot');
	push(head, 'Saab');
	push(head, 'Seat');
	push(head, 'Skoda');
	push(head, 'Tata');
	//push(head, 'Tesla');
	//push(head, 'Toyota');

	add(head, 'Mercedes'); // model is not found
	add(head, 'Polonez');
	add(head, 'Polonez');
	add(head, 'Polonez');
	add(head, 'Peuegot');
	add(head, 'Skoda');
	add(head, 'Tata');

	print(head);
        writeln();

        readln(mm.model);
        readln(mm.color);
        readln(mm.year);
        remove(head, 'Polonez', mm);
        print(head);
end.


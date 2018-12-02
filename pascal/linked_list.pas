program main;

const MAX = 20;
type TCar = record
	brand : string[MAX];
	color : string[MAX];
	year : integer;
end;


// every next element is at the beggining
// [] -> [] -> [] -> list
PPart = ^Part;
Part = record
	data : TCar;
	prev : PPart;
end;

procedure getNewCar(var car : TCar);
	begin
		readln(car.brand);
		readln(car.color);
		readln(car.year);
	end;

procedure push(var list : PPart);
	var newOne : PPart;
	begin
		new(newOne);
		getNewCar(newOne^.data);
		newOne^.prev := list;
		list := newOne;
	end;

procedure pop(var list : PPart);
	var buffer : PPart;
	begin
		if list = NIL then
                   exit;

		buffer := list;			// the element we want to delete
		list := list^.prev;		// the first one is now second one
		dispose(buffer);		// delete element
                buffer := NIL;	// NIL
	end;

procedure print(const list : PPart);
	var buffer : PPart;
	begin
		buffer := list;
		while buffer <> NIL do
		begin
			writeln('Brand: ', buffer^.data.brand);
			writeln('Color: ', buffer^.data.color);
			writeln('Year: ', buffer^.data.year);
			buffer := buffer^.prev;
		end;
	end;

// Main.
var head : PPart = NIL;
begin
	push(head);
	push(head);
	print(head);
        writeln('---------------');
	pop(head);
	print(head);
        writeln('---------------');
end.


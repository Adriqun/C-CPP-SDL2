program main;

const MAX = 20;
type TCar = record
	brand : string[MAX];
	color : string[MAX];
	year : integer;
end;


// every next element is at the end
// list -> [] -> [] -> []
PPart = ^Part;
Part = record
	data : TCar;
	next : PPart;
	prev : PPart;
end;

procedure getNewCar(var car : TCar);
	begin
		readln(car.brand);
		readln(car.color);
		readln(car.year);
	end;

procedure push_back(var head, tail : PPart);
	var newOne, buffer : PPart;
	begin
		new(newOne);
		getNewCar(newOne^.data);
		newOne^.next := NIL;
		newOne^.prev := NIL;
		
		if (head = NIL) and (tail = NIL) then
		begin
			head := newOne;
		end
		else
		begin
			buffer := head;
			while buffer^.next <> NIL do
				buffer := buffer^.next;

			buffer^.next := newOne;
			newOne^.prev := buffer;
			tail := newOne;
		end;
	end;

procedure pop(var head, tail : PPart);
	var buffer : PPart;
	begin

		if (head <> NIL) and (head^.next = NIL) then
		begin
			dispose(head);
			head := NIL;
			tail := NIL;
			exit;
		end;

		buffer := head;	// point to first element
		while buffer^.next <> NIL do
		begin
			if buffer^.next^.next = NIL then	// delete the last one
			begin
				buffer^.next^.prev := NIL;
				dispose(buffer^.next);
				buffer^.next := NIL;
				tail := buffer;
				break;
			end;
			buffer := buffer^.next; // point to next one
		end;
	end;

procedure printHead(const list : PPart);
	begin
		if(list <> NIL)then
		begin
			writeln('Brand: ', list^.data.brand);
			writeln('Color: ', list^.data.color);
			writeln('Year: ', list^.data.year);
			printHead(list^.next);
		end;
	end;

procedure printTail(const list : PPart);
	begin
		if(list <> NIL)then
		begin
			writeln('Brand: ', list^.data.brand);
			writeln('Color: ', list^.data.color);
			writeln('Year: ', list^.data.year);
			printTail(list^.prev);
		end;
	end;

// Main.
var head : PPart = NIL;
var tail : PPart = NIL;
begin
	push_back(head, tail);
	push_back(head, tail);
	push_back(head, tail);
	
	writeln('From the head:');
	printHead(head);
	writeln('---------------');
	writeln('From the tail:');
	printTail(tail);
	writeln('---------------');
	
	pop(head, tail);
	writeln('After pop() - From the head:');
	printHead(head);
	writeln('---------------');
	writeln('After pop() - From the tail:');
	printTail(tail);
	writeln('---------------');
end.



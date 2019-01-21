program major;

uses sysutils;

type PNode = ^TNode;
TNode = record
	data : integer;
	next : PNode;
	prev : PNode;
end;

procedure add(var head : PNode; data : integer);
	var current, buffer : PNode;
	begin
		if head = nil then
		begin
			new(head);
			head^.data := data;
			head^.next := head;
			head^.prev := head;
			exit;
		end;

		if head = head^.next then
		begin
			new(current);
			current^.data := data;
			head^.prev := current;
			head^.next := current;
			current^.prev := head;
			current^.next := head;
			exit;
		end;

		buffer := head; // zapisujemy glowe
		current := head^.next; // zaczynamy odrazu od nastepnego

		// idziemy dalej jesli nastepny od current to nie glowa
		while current^.next <> buffer do
			current := current^.next;

		// dodajemy
		new(buffer);
		buffer^.data := data;
		current^.next := buffer;
		buffer^.prev := current;
		buffer^.next := head;
		head^.prev := buffer;
	end;

procedure printNext(var head : PNode);
	var buffer, current : PNode;
	begin
		buffer := head;
		current := head;
		if head <> nil then
		begin
			repeat
				writeln('Data Next: ', current^.data);
				current := current^.next;
			until current = buffer;
		end;
	end;

procedure printPrev(var head : PNode);
	var buffer, current : PNode;
	begin
		buffer := head;
		current := head;
		if head <> nil then
		begin
			repeat
				writeln('Data Prev: ', current^.data);
				current := current^.prev;
			until current = buffer;
		end;
	end;

var head : PNode;
begin

	add(head, 15);
	add(head, 10);
	add(head, 1);
	add(head, 99);
	add(head, 36);
	add(head, 76);
	printNext(head);
	writeln();
	printPrev(head);
end.


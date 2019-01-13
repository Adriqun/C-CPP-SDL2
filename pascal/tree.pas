program main;

type PElem = ^TElem;
TElem = record
	n : integer;
	left : PElem;
	right : PElem;
end;

procedure add(var p : PElem; n : integer);
begin
	if p = NIL then
	begin
		new(p);
		p^.n := n;
		p^.left := NIL;
		p^.right := NIL;
	end
	else
	begin
		if p^.n > n then
		begin
			add(p^.left, n);
		end
		else
		begin
			add(p^.right, n);
		end;
	end;
end;

procedure printInOrder(var head : PElem);
begin
	if head = NIL then
		exit;
	printInOrder(head^.left);
	writeln('Nr: ', head^.n);
	printInOrder(head^.right);
end;

procedure printPreOrder(var head : PElem);
begin
	if head = NIL then
		exit;
	writeln('Nr: ', head^.n);
	printPreOrder(head^.left);
	printPreOrder(head^.right);
end;

procedure printPostOrder(var head : PElem);
begin
	if head = NIL then
		exit;
	printPostOrder(head^.left);
	printPostOrder(head^.right);
	writeln('Nr: ', head^.n);
end;

function find(var head : PElem; seek : integer) : PElem;
begin
	find := head;
	if (head = NIL) or (head^.n = seek) then
	begin
		exit;
	end
	else
	begin
		if head^.n > seek then
		begin
			find(head^.left, seek);
		end
		else
		begin
			find(head^.right, seek);
		end;
	end;
end;

procedure removetree(var head : PElem);
begin
	if head <> NIL then
	begin
		removetree(head^.left);
		removetree(head^.right);
		dispose(head);
	end;
end;



var head : PElem = NIL;
var temp : PElem = NIL;
begin
     add(head, 5);
     add(head, 15);
     add(head, 28);
     add(head, 17);
     add(head, 1);
     add(head, 4);
     add(head, 13);
     printPostOrder(head);
     temp := find(head, 15);
     writeln('Found: ', temp^.n);
end.


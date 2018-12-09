program main;

type TAuto = record
	marka : string[20];
	kolor : string[20];
	rok : integer;
end;

PElem = ^Elem;
Elem = record
	data : TAuto;
	poprzedni : PElem;
end;

procedure noweAuto(var auto : TAuto);
begin
	readln(auto.marka);
	readln(auto.kolor);
	readln(auto.rok);
end;

procedure dodaj(var lista : PElem);
var nowyEl : PElem;
begin
	new(nowyEl);
	noweAuto(nowyEl^.data);
	nowyEl^.poprzedni := lista;
	lista := nowyEl;
end;

procedure pop(var lista : PElem);
var tymczas : PElem;
begin
	if lista = NIL then
               exit;

	tymczas := lista;
	lista := lista^.poprzedni;
	dispose(tymczas);
            tymczas := NIL;
end;

procedure wypisz(const lista : PElem);
var tymczas : PElem;
begin
	tymczas := lista;
	while tymczas <> NIL do
	begin
		writeln('marka: ', tymczas^.data.marka);
		writeln('kolor: ', tymczas^.data.kolor);
		writeln('rok: ', tymczas^.data.rok);
		tymczas := tymczas^.poprzedni;
	end;
end;

// Main.
var glowa : PElem = NIL;
begin
dodaj(glowa);
dodaj(glowa);
wypisz(glowa);
writeln('---------------');
pop(glowa);
wypisz(glowa);
writeln('---------------');
end.


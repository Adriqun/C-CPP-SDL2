program main;

const MAX = 30;

type pReb = ^TRebeliant;
	TRebeliant = record
	id : Byte;
	imie : string[MAX];
	nazwisko : string[MAX];
	nast : pReb; // nastepny
	end;

type pBaza = ^TBaza;
	TBaza = record
	id : Byte;
	planeta : string[MAX];
	rozmiar : integer;
	zaloga : pReb;
	nast : pBaza; // nastepny
	pop : pBaza; // poprzedni
	end;

function znajdzBaze(szukaneID : integer; baza : pBaza) : pBaza;
	var temp : pBaza;
	begin
		if baza = NIL then
		begin
			znajdzBaze := NIL;
			exit;
		end;

		if ((baza = baza^.nast) and (baza^.id = szukaneID)) then
		begin
			znajdzBaze := baza;
			exit;
		end;

		temp := baza^.nast;
		while not(temp = baza) do
		begin
			if temp^.id = szukaneID then
			begin
				znajdzBaze := temp;
				exit;
			end;

			temp := temp^.nast;
		end;

		znajdzBaze := NIL;
	end;

procedure dodajBaze(noweID : integer; nowyRozmiar : integer; planeta : string; var baza : pBaza);
	var temp, buf : pBaza;
	begin
		if baza = NIL then // pierwsza baza
		begin
			new(baza);
			baza^.id := noweID;
			baza^.planeta := planeta;
			baza^.rozmiar := nowyRozmiar;
			baza^.zaloga := NIL;
			baza^.nast := baza;
			baza^.pop := baza;
			exit;
		end;

		// jest jedna baza i wskazuje na siebie
		temp := baza^.nast;
		if baza = temp then
		begin
			new(temp);
			temp^.id := noweID;
			temp^.planeta := planeta;
			temp^.rozmiar := nowyRozmiar;
			temp^.zaloga := NIL;
			temp^.nast := baza;
			temp^.pop := baza;
			baza^.nast := temp;
			baza^.pop := temp;
			exit;
		end;

		// jakas baza juz istnieje
		// idziemy na "koniec" naszej listy baz
		temp := baza;
		while not(temp^.nast = baza) do // jesli nastepny to poczatek to konczymy
		begin;
			buf := temp; // poprzednik
			temp := temp^.nast;
		end;

		// jestesmy na "koncu" listy baz
		new(temp^.nast);
		temp^.nast^.id := noweID;
		temp^.nast^.planeta := planeta;
		temp^.nast^.rozmiar := nowyRozmiar;
		temp^.nast^.zaloga := NIL;
		temp^.nast^.nast := baza; // nastepny to glowa
		temp^.nast^.pop := buf; // poprzedni to poprzednik
		buf^.nast := temp;		// nastepny od poprzedniego to nasz nowo dodany
		baza^.pop := temp^.nast; // poprzedni od glowy to nasz nowo dodany
	end;

function liczebnosc(baza : pBaza) : integer;
	var temp : pReb;
	var licznik : integer;
	begin
		if baza = NIL then
		begin
			liczebnosc := -1;
			exit;
		end;

		licznik := 1;
		temp := baza^.zaloga;
		while temp <> NIL do
		begin
			licznik := licznik + 1;
			temp := temp^.nast;
		end;

		liczebnosc := licznik;
	end;

function zakwateruj(id : integer; imie : string; nazwisko : string; baza : pBaza) : boolean;
	var reb : pReb;
	var licznik : integer;
	begin
		zakwateruj := true;
		if id = -1 then // czy id jest ustawione?
			zakwateruj := false;

		if imie = '' then // czy imie jest ustawione?
			zakwateruj := false;

		if nazwisko = '' then // czy nazwisko jest ustawione?
			zakwateruj := false;

		if baza = NIL then // czy baza jest NIL?
			zakwateruj := false;

		if not(zakwateruj) then
			exit;

		// dane sa sprecyzowane
		reb := baza^.zaloga;
		licznik := 1;

		if reb = NIL then
		begin
			new(reb);
			reb^.id := id;
			reb^.imie := imie;
			reb^.nazwisko := nazwisko;
			reb^.nast := NIL;
                        baza^.zaloga := reb;
			zakwateruj := true; // poprawnie dodany pierwszy czlonek zalogi
		end
		else
		begin
			// idziemy na koniec listy
			while not(reb^.nast = NIL) do
			begin
				licznik := licznik + 1;
				reb := reb^.nast;
			end;

			if licznik > baza^.rozmiar then // nie ma wolnego miejsca w zalodze
			begin
				zakwateruj := false;
				exit;
			end;

			new(reb^.nast);
			reb^.nast^.id := id;
			reb^.nast^.imie := imie;
			reb^.nast^.nazwisko := nazwisko;
			reb^.nast^.nast := NIL;
			zakwateruj := true; // poprawnie dodany kolejny czlonek zalogi
		end;
	end;

procedure wypisz(baza : pBaza);
	var buf : pReb;
	begin
		writeln('-------------------------------------');
		writeln('ID Bazy: ', baza^.id);
		writeln('Liczebnosc: ', liczebnosc(baza), ' Rozmiar Bazy: ', baza^.rozmiar);
		writeln('Nazwa Bazy: ', baza^.planeta);

		buf := baza^.zaloga; // wypisz zaloge
		while not(buf = NIL) do
		begin
			writeln('----');
			writeln('ID Czlonka: ', buf^.id);
			writeln('Imie Czlonka: ', buf^.imie);
			writeln('Nazwisko Czlonka: ', buf^.nazwisko);
			writeln('----');
			buf := buf^.nast;
		end;

		writeln('-------------------------------------');
		writeln();
	end;

procedure raport(baza : pBaza);
	var temp : pBaza;
	begin
		if baza = NIL then
			exit;

		temp := baza;
		repeat
		begin
			wypisz(temp);
			temp := temp^.nast;
		end;
		until temp = baza
	end;

var bazy : pBaza = NIL;

begin
	dodajBaze(1, 10, 'Ziemia', bazy);
	zakwateruj(1, 'Kamil', 'Gawlik', bazy);
	zakwateruj(2, 'Joanna', 'Zielonka', bazy);
	zakwateruj(3, 'Zenek', 'Nosak', bazy);
	dodajBaze(3, 4, 'Mars', bazy);
	zakwateruj(4, 'Janek', 'Kowalski', bazy^.nast);
	zakwateruj(5, 'Barbara', 'Nowak', bazy^.nast);
	dodajBaze(5, 200, 'Jowisz', bazy);
	zakwateruj(6, 'Mariusz', 'Pieprz', bazy^.nast^.nast);
	zakwateruj(7, 'Zdzislaw', 'Szafka', bazy^.nast^.nast);
	zakwateruj(8, 'Ania', 'Solina', bazy^.nast^.nast);
	zakwateruj(9, 'Maria', 'Bazujaca', bazy^.nast^.nast);
	raport(bazy);
end.


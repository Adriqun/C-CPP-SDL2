program main;
uses Crt;

const treeWidth = 45;
const woodWidth = 9;
const w = treeWidth + 2;
const h = 23;

var christmasstr : string = '@0oO8';
var leafstr : string = 'H!;:\"[]$%^&(){}~J,-=';

var i, j, k, s, l : integer;
var tree : array of array of char;
var snballs : array of array of char;
var chballs : array of array of char;
var snballsbuf : array of char;

function isTree(const sign : char) : boolean;
var i : integer;
begin
	for i := 0 to high(leafstr) do
		if sign = leafstr[i] then
		begin
			isTree := true;
			exit;
		end;

	if (sign = '/') or (sign = '\') then
	begin
		isTree := true;
		exit;
	end;

	isTree := false;
end;

function isWood(const sign : char) : boolean;
var i : integer;
begin
	if sign = '#' then
	begin
		isWood := true;
		exit;
	end;

	isWood := false;
end;

procedure setTree();
begin
	TextColor(2);
end;

procedure setWood();
begin
	TextColor(6);
end;

procedure setSnowBall();
begin
	TextColor(random(2) + 7);
end;

procedure setChristmasBall();
begin
	TextColor(random(5) + 9);
end;


// main
begin
	// set seed
	randomize();

	// set size
	SetLength(tree, w);
	SetLength(snballs, w);
	SetLength(chballs, w);
        SetLength(snballsbuf, w);
	for i := 0 to w-1 do
	begin
		SetLength(tree[i], h);
		SetLength(snballs[i], h);
		SetLength(chballs[i], h);
		for j := 0 to h-1 do
		begin
			tree[i, j] := ' ';
			chballs[i, j] := ' ';
			if random(10) = 0 then
			begin
				snballs[i, j] := '*';
			end
			else
			begin
				snballs[i, j] := ' ';
			end;
		end;
	end;

	// prepare tree
	s := h - 1;
	l := 2;
	for j := 0 to (h - 3) do
	begin
		for i := s to (s + l - 1) do
			tree[i, j] := leafstr[random(length(leafstr))];
		s := s - 1;
		l := l + 2;
	end;


	// right border of a tree
	for j := 0 to (h - 1) do
		for i := (w - 1) downto 0 do
			if not(tree[i, j] = ' ') then
			begin
				tree[i, j] := '\';
				break;
			end;

	// left border of a tree
	for j := 0 to h - 1 do
		for i := 0 to (w - 1) do
			if not(tree[i, j] = ' ') then
			begin
				tree[i, j] := '/';
				break;
			end;

	// prepare christmas balls
	for j := 0 to (h - 1) do
		for i := (w - 1) downto 0 do
			if not(tree[i, j] = ' ') and not(tree[i, j] = '/') and not(tree[i, j] = '\') then
			begin
                                if random(10) < 2 then
				   chballs[i, j] := christmasstr[random(length(christmasstr))];
			end;

	// prepare wood
	k := round((treeWidth / 2) - (woodWidth / 2));
	l := round((treeWidth / 2) + (woodWidth / 2));
	for j := h - 2 to h - 1 do
		for i := k to l do
			tree[i, j] := '#';

	while true do
	begin
		// clear console
		ClrScr;

		for i := 0 to (h - 1) do
		begin
			for j := 0 to (w - 1) do
			begin
				if not(snballs[j, i] = ' ') then
				begin
					setSnowBall();
					write(snballs[j, i]);
					continue;
				end
				else if not(chballs[j, i] = ' ') then
				begin
					setChristmasBall();
					write(chballs[j, i]);
					continue;
				end;

				if isTree(tree[j, i]) then
				begin
					setTree();
				end
				else if isWood(tree[j, i]) then
				begin
					setWood();
				end;

				write(tree[j, i]);
			end;
			writeln();
		end;

		// move snow balls
		for i := 0 to (w - 1) do
			snballsbuf[i] := snballs[i, (h - 1)];
		for i := (h - 1) downto 1 do
			for j := 0 to (w - 1) do
				snballs[j, i] := snballs[j, (i - 1)];
		for i := 0 to (w - 1) do
			snballs[i, 0] := snballsbuf[i];

		// sleep for 0.8s
		Delay(800);
	end;
end.

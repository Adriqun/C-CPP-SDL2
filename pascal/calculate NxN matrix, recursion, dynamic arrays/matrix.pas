// Author: Adrian Michalek
// Functionality: Square Matrix Manipulation.
// Goal: Calculate Determinant Of Any Square Matrix.
// Release: 30 October 2018
// Github: https://github.com/devmichalek

unit matrix;

interface
    type Square = array of array of double; // matrix n*n

    // Call only once, set seed for random numbers.
    procedure setSeed();

    // Creates square matrix with n*n size.
    procedure create(var square : Square; n : integer);

    // Fill matrix with random numbers, read from user or load from file.
    procedure fill(var square : Square);
    procedure _read(var square : Square);
    procedure load(var square : Square; path : string);

    // Print matrix to console or save to file.
    procedure print(const square : Square);
    procedure save(const square : Square; path : string);

    // Get determinant for 2/3/n square matrix.
    function getDet2D(var s : Square) : double;
    function getDet3D(var s : Square) : double;
    function getDetND(var s : Square) : double; // Recursive.
    function getDet(var s : Square) : double; // Global.


implementation
    procedure setSeed();
    begin
        randomize();
    end;
// ------------------------------------------------------------
    procedure create(var square : Square; n : integer);
    var i : integer;
    begin
        SetLength(square, n);
        for i := 0 to Length(square)-1 do
            SetLength(square[i], n);
    end;
// ------------------------------------------------------------
    procedure fill(var square : Square);
    var i, j : integer;
    begin
        for i := 0 to Length(square)-1 do
            for j := 0 to Length(square[i])-1 do
                square[i, j] := random(10); // Change scope here.
    end;
// ------------------------------------------------------------
    procedure _read(var square : Square);
    var i, j : integer;
    begin
        for i := 0 to Length(square)-1 do
            for j := 0 to Length(square[i])-1 do
                read(square[i, j]);
    end;
// ------------------------------------------------------------
    procedure load(var square : Square; path : string);
    var i, j : integer; f : text;
    begin
        assign(f, path);
        reset(f);
        for i := 0 to Length(square)-1 do
            for j := 0 to Length(square[i])-1 do
                read(f, square[i, j]);
        close(f);
    end;
// ------------------------------------------------------------
    procedure print(const square : Square);
    var i, j : integer;
    begin
        for i := 0 to Length(square)-1 do
        begin
            for j := 0 to Length(square[i])-1 do
                write(square[i, j]:2:1, '  ');
            writeln();
        end;
    end;
// ------------------------------------------------------------
    procedure save(const square : Square; path : string);
    var i, j : integer; f : text;
    begin
        assign(f, path);
        rewrite(f);
        for i := 0 to Length(square)-1 do
        begin
            for j := 0 to Length(square[i])-1 do
                write(f, square[i, j]:2:1, '  ');
            writeln(f);
        end;
        close(f);
    end;
// ------------------------------------------------------------
    function getDet2D(var s : Square) : double;
    begin
        getDet2D := s[0][0]*s[1][1] - s[1][0]*s[0][1];
    end;

// ------------------------------------------------------------
    function getDet3D(var s : Square) : double;
    var a, b, c, d, e, f : double;
    begin
        a := s[0][0]*s[1][1]*s[2][2];
	b := s[0][1]*s[1][2]*s[2][0];
	c := s[0][2]*s[1][0]*s[2][1];

	d := s[2][0]*s[1][1]*s[0][2];
	e := s[0][0]*s[1][2]*s[2][1];
	f := s[1][0]*s[0][1]*s[2][2];
	getDet3D := (a + b + c) - (d + e + f);
    end;
// ------------------------------------------------------------
    function getDetND(var s : Square) : double;
    var res : double;
    var i, j, k, h : integer;
    var buffer : Square;
    begin
        res := 0;

        if Length(s) = 3 then
            exit(getDet3D(s));

        // Allocate
        create(buffer, Length(s)-1);

        // Calculate
        for i := 0 to Length(s)-1 do
        begin
            h := 0; // y pos
            for j := 0 to Length(s)-1 do
            begin
                if not(i=j) then
                begin
                    for k := 1 to Length(s)-1 do
                        buffer[k-1][h] := s[k][j];
                    h := h+1;
                end;
            end;

            if i mod 2 = 0 then
            begin
                res := res + s[0][i]*getDetND(buffer);
            end
            else
                res := res - s[0][i]*getDetND(buffer);
        end;
        exit(res);
    end;

// ------------------------------------------------------------
    function getDet(var s : Square) : double;
    begin
        if Length(s) = 1 then
        begin
            exit(s[0][0]);
        end
        else if Length(s) = 2 then
        begin
            exit(getDet2D(s));
        end
        else if Length(s) = 3 then
        begin
            exit(getDet3D(s));
        end
        else
        begin
            exit(getDetND(s));
        end;
    end;
// ------------------------------------------------------------
end.


unit hellofile;

// {$mode objfpc}{$H+} ANSI stirng or sth

// headers of function
interface
    //procedure hello(name : string);
    function max(const a, b : integer) : integer;

    //procedure fill(var tab : ttab); // by reference
    //procedure fill(tab : ttab);     // deep copy

    type ttab = array[0..9] of integer;
    procedure fill(var tab : ttab);
    procedure print(const tab : ttab);
    function generate() : ttab;

    // dir -> true -> ascending order
    // dir -> false -> descending order
    procedure bubblesort(var tab : ttab; dir : boolean);

implementation
    //procedure hello(name : string);
    //begin
      //writeln('Hello ', name);
    //end;

    function max(const a, b : integer) : integer;
    begin
        if a > b then
        begin
            max := a;
        end
        else
            max := b;
        exit; // c++ return;
    end;

    procedure fill(var tab : ttab);
    var i : integer;
    begin
       for i := low(tab) to high(tab) do
           tab[i] := random(90) + 10; // 10 - 99
    end;

    procedure print(const tab : ttab);
    var i : integer;
    begin
       for i := low(tab) to high(tab) do
           write(tab[i], ' ');
    end;

    function generate() : ttab;
    var tab : ttab; i : integer;
    begin
        for i := low(tab) to high(tab) do
            tab[i] := random(10) + 1;
        generate := tab;
    end;

    procedure bubblesort(var tab : ttab; dir : boolean);
    var buffer, i, j : integer;
    begin
        for i := low(tab) to high(tab) do
            for j := low(tab) to high(tab) do
                if not(i = j) then
                begin
                    if (dir and (tab[i] < tab[j])) then
                    begin
                        buffer := tab[i];
                        tab[i] := tab[j];
                        tab[j] := buffer;
                    end
                    else if not(dir) and (tab[i] > tab[j]) then
                    begin
                        buffer := tab[i];
                        tab[i] := tab[j];
                        tab[j] := buffer;
                    end;
                end;
    end;
end.


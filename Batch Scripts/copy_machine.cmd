@echo off
rem Kopiuje zadane pliki do zadanego folderu


rem Zmienne do ustawienia
set src_dir=release\bin\
set des_dir=instalka\bin\Linux\
set files[0]=vsimsa
set files[1]=libscripter.so

set "x=0"
:simple
if defined files[%x%] (

	rem Testowanie, warto sprawdzic!
	@echo on
    call echo From:  %%src_dir%%%%files[%x%]%%
    call echo To:  %%des_dir%%%%files[%x%]%%
    @echo off

    rem Kopiowanie, wylaczyc komentarz po sprawdzeniu, Q znaczy quietly Y znaczy yes
    call xcopy %%src_dir%%%%files[%x%]%% %%des_dir%%%%files[%x%]%% /Y

    set /a "x+=1"
    goto :simple
)


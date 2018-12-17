#set ArrayName(Index) value

set languages(0) {Tcl}
set languages(1) {PHP}
set languages(2) {Java}
set languages(3) {C#}
set languages(3) {Perl}
set length [array size languages]

for {set i 0} {$i < $length} {incr i} {
	puts "Language\[$i\] = $languages($i)"
}
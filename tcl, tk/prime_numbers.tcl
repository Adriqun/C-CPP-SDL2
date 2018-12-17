set k 0
for {set i 2} {$i < 100} {incr i} {
	for {set j 2} {$j < $i} {incr j} {
		if {[expr $i%$j] == 0} {
			set k 1
			break;
		}
	}

	if {!$k} {
		puts "Prime number: $i";
	}
	set k 0
}
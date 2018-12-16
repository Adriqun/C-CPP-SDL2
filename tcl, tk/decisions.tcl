set a 1

#if statement
if {$a < 5} {
	puts "yes"
} elseif {$a < 6} {
	puts "no"
} else {
	puts "no"
}

#switch statement
set b "1"
switch $b {
	"0" {
		puts "It is zero"
	}

	"1" {
		puts "It is one"
	}
}

set c ABC
switch $c {
	CBA {
		puts "It is CBA"
	}

	ABC {
		puts "It is ABC"
	}

	default {
		puts "It is none of those"
	}
}

set d 10;
set e [expr $d == 1 ? 20 : 30]
puts "Value of e is $e\n"
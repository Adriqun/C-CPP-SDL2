set a 10
while {$a < 20} {
	puts "  Value of a: $a"
	incr a
}

for {set b 5} {$b > -1} {incr b -1} {
	puts "\tValue of b: $b"
}
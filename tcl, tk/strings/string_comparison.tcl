set str1 "Hello"
set str2 "World"
set str3 "World"

puts "Result of str1 and str2 = [string compare $str1 $str2]"

if {[string compare $str2 $str3] == 0} {
	puts "String \'str1\' and \'str2\' are the same."
}

#-1 means the first string comes before second and 1 means the opposite
#Other options below:
#if {$name=="foo"} {...}                  ;# (1)
#if {$name eq "foo"} {...}                ;# (2)
#if {[string compare $name foo]==0} {...} ;# (3)
#if {[string equal $name foo]} {...}      ;# (4)
#if {[string match foo $name]} {...}      ;# (5)
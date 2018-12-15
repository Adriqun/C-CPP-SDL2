#arithmetic on the variable
set var1 18
puts stdout [expr $var1 + 6 + 9]

#dynamic object nature
#string representations

#multiple strings
set var2 "hello world"
puts $var2
set var3 {hello world}
puts $var3

#list
set var4 {red green blue}
puts [lindex $var4 2]
set var4 "red green blue"
puts [lindex $var4 1]

#associative array have an index (key)
set var5(english) 10
set var5(math) 15
puts $var5(english)
puts $var5(math)

#handles
set fileout [open "temp.txt" w]
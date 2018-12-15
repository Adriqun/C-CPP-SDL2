#variables with space in name! :o
set {Variable A} 15
puts stderr ${Variable A}

#dynamic typing
set strVar "-10"
set result [expr $strVar + 25]
puts $result

#to get the precision (in standard there is 12)
set nextVar "10"
puts [expr $nextVar / 9.0]

set tcl_precision 5
set var "13"
puts [expr $var / 1.15]

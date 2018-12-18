proc factorial {number} {
   if {$number <= 1} {
      return 1
   } 
   return [expr $number * [factorial [expr $number - 1]]]

}
puts [factorial 3]
puts [factorial 5]
set v1 [factorial 999]
set v2 [factorial 998]
puts [expr $v1 + $v2]
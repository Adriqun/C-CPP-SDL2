#!/usr/bin/perl

@coins = ("Quarter", "Dime", "Zloty");
print "1. \@coins = @coins\n";

# add one element at the end
push(@coins, "Penny");
print "2. \@coins = @coins\n";

# add one element at the beggining
unshift(@coins, "Dollar");
print "3. \@coins = @coins\n";

# remove last element
pop(@coins);
print "4. \@coins = @coins\n";

# remove element from the beggining
shift(@coins);
print "5. \@coins = @coins\n";
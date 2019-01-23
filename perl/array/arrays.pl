#!/usr/bin/perl

#sequential number arrays
# .. is range operator
@a = (1..10);
@b = (11..20);
@c = (a..z);

print "@a\n";
print "@b\n";
print "@c\n";
print "Size of array \@a is ", scalar @a,"\n";

@array = (1, 2, 3);
$array[40] = 0;
print "Size of array \@array is ", scalar @array, "\n";
print "Max index is $#array\n";

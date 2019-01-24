#!/usr/bin/perl

# Slices.
%data = (-OneWord => 10, -SecondOneWord => 100, -ThirdOneWord => 1000);
@array = @data{-OneWord, -SecondOneWord};
print "Array: @array\n";

# Keys and values.
@names = keys(%data);
print "Names: @names\n";

@values = values(%data);
print "Values: @values\n";


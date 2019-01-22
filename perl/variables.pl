#!/usr/bin/perl

# There are 3 types: scalars, arrays, hashes.
# Each of them is created inside its own namespace.


# scalars: number, string, reference.
# $
$b = false;
$age = 25;
$name = "John";
$salary = 1440.50;
print "Age: $age\n";
print "Name: $name\n";
print "Salary: $salary\n";

# array: of numbers, of string etc.
# @
@ages = (25, 30, 35);
@names = ("John", "Paul", "Joseph");
print "\$ages[0] = $ages[0]\n";
print "\$ages[1] = $ages[1]\n";
print "\$ages[2] = $ages[2]\n";
print "\$names[0] = $names[0]\n";
print "\$names[1] = $names[1]\n";
print "\$names[2] = $names[2]\n";

# hash: stores sets of key/value pair.
# %
%data = ('John', 45, 'Lisa', 30);
print "\$data{'John'} = $data{'John'}\n";
print "\$data{'Lisa'} = $data{'Lisa'}\n";

# variables are treated differently
@copy = @names;
$size = @names;
print "Given names are @copy\n";
print "Size is $size";


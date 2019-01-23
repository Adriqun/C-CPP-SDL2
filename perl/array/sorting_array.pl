#!/usr/bin/perl

# sort [ subroutine ] list

@foods = qw(pizza steak chicken burgers);
print "Before: @foods\n";

@foods = sort(@foods);
print "After: @foods\n";
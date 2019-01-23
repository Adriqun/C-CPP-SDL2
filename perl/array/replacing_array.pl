#!/usr/bin/perl

# splice @array, offset [ , length [ , list ] ]

@nums = (1..20);
print "Before - @nums\n";

splice(@nums, 4, 5, 101..106);
print "After - @nums\n";
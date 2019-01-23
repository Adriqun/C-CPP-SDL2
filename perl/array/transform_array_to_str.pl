#!/usr/bin/perl

$var_string = "Rain-Drops-On-Roses-And-Whiskers-On-Kittens";
$var_names = "Larry,David,Roger,Ken,Michael,Tom";

@string = split('-', $var_string);
@names  = split(',', $var_names);

$strings1 = join( '-', @string );
$strings2 = join( ',', @names );

print "$strings1\n";
print "$strings2\n";
#!/usr/bin/perl

# split [ pattern [ , expr [ , limit ] ] ]

$str1 = "Rain-Drops-On-Roses-And-Whiskers-On-Kittens";
$str2 = "Larry,David,Roger,Ken,Michael,Tom";

@strings1 = split('-', $str1);
@strings2 = split(',', $str2);

print "\$strings1[3] = $strings1[3]\n";
print "\$strings2[4] = $strings2[4]\n";
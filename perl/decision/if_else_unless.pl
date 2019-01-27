#!/usr/bin/perl

$a = 0;

if(!$a) {
	print("if(!\$a) \$a=$a\n");
} else {
	print("if(\$a) \$a=$a\n");
}

# unless = not if
unless($a) {
	print("unless(\$a) \$a=$a\n");
} else {
	print("unless(!\$a) \$a=$a\n");
}


# ?: operator like in c++
$a > 0 ? print("\$a is bigger than 0\n") : print("\$a is not bigger than 0\n");
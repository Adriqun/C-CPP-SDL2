#!/usr/bin/perl

#Perl consists of 5 different loops.

$reset = 0;
$var = $reset;
$limit = 10;

# 1. While
while ($var < $limit) {
	print "While \$var=$var\n";
	++$var;
}
$var = $reset;

# 2. Do while
do {
	print "Do While \$var=$var\n";
	++$var;
} while ($var < $limit);

# 3. Until
until ($var <= $reset) {
	print "Until \$var=$var\n";
	--$var;
}

# 4. For
for ($i = 0; $i < $limit; ++$i) {
	print "For \$i=$i\n";
}

@list = (0, 5, 10, 15, 20, 25, 30);
foreach $it (@list) {
	print "List \$it=$it\n";
}
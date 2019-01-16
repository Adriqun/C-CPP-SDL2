#!/usr/bin/perl

# single line comment
=begin
this is
multi
line
=cut

print("Hello World\n");
print('Hello World\n'); print("\n");
print "Hello
	   World\n";



$a = 10;
$var = <<"EOF";
This is the syntax for here document and it will continue
until it encounters a EOF in the first line.
This is case of double quote so variable value will be 
interpolated. For example value of a = $a
EOF
print "$var\n";

$var = <<'EOF';
This is case of single quote so variable value will be 
interpolated. For example value of a = $a
EOF
print "$var\n";
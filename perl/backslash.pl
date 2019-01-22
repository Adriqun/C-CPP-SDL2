#!/usr/bin/perl

# interpolation
$str = "Welcome\nto the jungle";
print("$str\n");

# non-interpolation
$str = 'Welcome\nto the jungle';
print("$str\n");

# w will be uppercase, \u
$str = "\uwelcome to the jungle";
print("$str\n");

# uppercase \U
$str = "\UWelcome to the jungle";
print("$str\n");

# uppercase \U till the \E
$str = "Welcome \Uto the jun\Egle";
print("$str\n");

# backsalash non alpha-numeric including spaces.
$str = "\QWelcome to the jungle";
print("$str\n");

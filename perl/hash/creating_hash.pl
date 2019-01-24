#!/usr/bin/perl

%data = ('Adrian', 10, 'Michalek', 3, 'Cropp', 9);

print("\%data{'Adrian'} = $data{'Adrian'}\n");
print("\%data{'Michalek'} = $data{'Michalek'}\n");
print("\%data{'Cropp'} = $data{'Cropp'}\n");

$data{'John'} = 2;
$data{'Lisa'} = 1;
#$[ = 1;
print("\$data{'John'} = $data{'John'}\n");

# Another way of setting hash data.
%data = (-OneWord => 10, -Only => 9);
$val = %data{-OneWord};
print("\$val = $val");
#!/usr/bin/perl

# check if key/values exists by simple:
%data = ("John Paul", 10, "Lisa" => 1, 'Thing' => 2);

if(exists($data{'Lisa'})) {
	print("Key 'Lisa' exists.\n")
} else {
	print("Warning, key 'Lisa' does not exist.\n");
}

# getting size of hash table
@keys = keys(%data);
$size = @keys;
print("Size by keys: $size\n");
@values = values(%data);
$size = @values;
print("Size by values: $size\n");

# adding by scalar
$data{'Lu'} = 35;
# now size is 4 not 3
$size = values(%data);
print("Size after adding: $size\n");

delete $data{'Lu'};
# now size is 3 not 4
$size = values(%data);
print("Size after removing: $size\n");
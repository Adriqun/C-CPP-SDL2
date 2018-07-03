#!/usr/bin/python

fo = open( "file.txt", "r" )
print "Name of the file: ", fo.name
print "Closed: ", fo.closed
print "Opening mode: ", fo.mode
print "Softspace flag: ", fo.softspace

for line in fo:
	print line[ 0 : len( line)-1 ]

fo.close()

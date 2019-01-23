#!/usr/bin/perl

# qw -> quote words
# @dats = ("Mon", "Tue" ... "Sun");
@days = qw(Mon Tue Wed Thu Fri Sat Sun);
@weekdays = @days[3, 4, 5];
@daysweek = @days[3..5];
print "@weekdays\n";
print "@daysweek\n";

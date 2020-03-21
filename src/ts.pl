open(FILE, ">t.txt") or die "Cannoe open file";
use Time::HiRes qw(time);
printf FILE ("%.2f", time);
close(FILE);
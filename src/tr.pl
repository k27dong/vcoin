open(FILE, "<t.txt") or die "Cannot open file";
my $row = <FILE>;
use Time::HiRes qw(time);
my $tnow = time;
printf("%.2f s\n", $tnow - $row);
close(FILE);
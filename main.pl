use strict;
use lib ".";
use Efeu;

my $input = \*STDIN;
my $maschine = Efeu::init();

while(Efeu::process_word($maschine, read_word($input))) { };

sub read_word {
	my $handle = shift;
	my $word = "";
	my $started = undef;
	while(1) {
		my $char;
		read($handle, $char, 1);
		last unless $char; # stop loop if eof
		unless ($started) {
			next if ord($char) < 33 or ord($char) > 126; # skip if is whitespace
			$started = 1;
		} else {
			last if ord($char) < 33 or ord($char) > 126; # stop loop if whitespace is found (end of word)
		}
		$word .= $char;
	}
	return $word;
}
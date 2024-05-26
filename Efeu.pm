package Efeu;
use strict;
use Class::Struct;

struct Maschine => {
	data_stack => '@',
	words => '%',
	compile_mode => '$',
	last_definiton => '$',
	word => '$',
	last_word => '$',
	ip => '$'
};

struct Word => {
	immediate => '$',
	instructions => '@'
};

sub init {
	my $maschine = Maschine->new();
	$maschine->data_stack(());
	$maschine->words({});
	$maschine->compile_mode(undef);
	$maschine->last_definiton(undef);
	$maschine->word(undef);
	$maschine->last_word(undef);
	$maschine->ip(0);
	return $maschine;
}

sub process_word {
	my $maschine = shift;
	my $word = shift;

	return undef unless $word;

	$maschine->last_word($maschine->word);
	$maschine->word($word);

	return process_word_compile($maschine, $word) if $maschine->compile_mode;
	return process_word_execute($maschine, $word) unless $maschine->compile_mode;
}

sub process_word_compile {
	my $maschine = shift;
	my $word = shift;

	if ($maschine->last_word eq "def") {
		$maschine->last_definiton($word);
		my $definiton = Word->new();
		$definiton->immediate(undef);
		$definiton->instructions(());
		$maschine->words->{$word} = $definiton;
		return 1;
	}

	if ($word eq "immediate") {
		die "no definition to mark as immediate" unless $maschine->last_definiton;
		$maschine->words->{$maschine->last_definiton}->immediate(1);
		return 1;
	}

	if ($word eq "end") {
		$maschine->compile_mode(undef);
		return 1;
	}

	# if word is defined and it is immediate, execute it
	if ($maschine->words->{$word} and $maschine->words->{$word}->immediate) { 
		return process_word_execute($maschine, $word);
	}

	# otherwise, just compile it
	push @{$maschine->words->{$maschine->last_definiton}->instructions}, $word; 
}

sub process_word_execute {
	my $maschine = shift;
	my $word = shift;

	if ($word eq "def") {
		$maschine->compile_mode(1);
		$maschine->last_definiton(undef);
		return 1;
	}

	if ($maschine->last_word eq "branch") {
		return 1;
	}

	if ($maschine->last_word eq "0branch") {
		# my $value = pop @{$maschine->data_stack};
		return 1;
	}

	if ($word eq "+") {
		my $a = pop @{$maschine->data_stack};
		my $b = pop @{$maschine->data_stack};
		push @{$maschine->data_stack}, $a+$b;
		return 1;
	}

	if ($word eq ".") {
		pop @{$maschine->data_stack};
		return 1;
	}

	if ($word eq "branch") {
		return 1;
	}

	if ($word eq "0branch") {
		return 1;
	}

	if ($word eq "emit") {
		my $value = pop @{$maschine->data_stack};
		print "$value\n";
		return 1;
	}

	if ($word eq "quit") {
		return 0;
	}

	# defined word
	if (defined $maschine->words->{$word}) {
		foreach (@{$maschine->words->{$word}->instructions}) {
			process_word_execute($maschine, $_);
		}
		return 1;
	}

	# integer
	if ($word =~ m/^\d+$/) {
		push @{$maschine->data_stack}, $word+0;
		return 1;
	}

	die "could not execute word '$word'";
}

1;
#!/usr/bin/php
<?PHP
	while (42)
	{
		echo "Enter a number: ";
		if (feof(STDIN)) {
			echo PHP_EOL;
			break ;
		}
		$line = fgets(STDIN);
		if (ctype_digit(trim($line))) {
			if ($line % 2 == 0)
				echo "The number " . trim($line) . " is even\n";
			else
				echo "The number " . trim($line) . " is odd\n";
		}
		else
			echo "'" . preg_replace("(\n+)", "", $line) ."' is not a number\n";
	}
?>

#!/usr/bin/php
<?PHP
	$argv[1] = trim($argv[1]);
	$argv[2] = trim($argv[2]);
	$argv[3] = trim($argv[3]);
	if ($argc > 1 && $argc < 5) {
		if (is_numeric($argv[1]) && is_numeric($argv[3])) {
			switch ($argv[2]) {
				case '+':
					echo $argv[1] + $argv[3] . PHP_EOL;
					break ;
				case '-':
					echo $argv[1] - $argv[3] . PHP_EOL;
					break ;
				case '*':
					echo $argv[1] * $argv[3] . PHP_EOL;
					break ;
				case '/':
					if ($argv[3] == 0) {
						echo 'Incorrect Parameters' . PHP_EOL;
						break ;
					}
					echo $argv[1] / $argv[3] . PHP_EOL;
					break ;
				case '%':
					if ($argv[3] == 0) {
						echo 'Incorrect Parameters' . PHP_EOL;
						break ;
					}
					echo $argv[1] % $argv[3] . PHP_EOL;
					break ;
			}
		}
		else {
			echo 'Incorrect Parameters' . PHP_EOL;
		}
	}
	else {
		echo 'Incorrect Parameters' . PHP_EOL;
	}
?>

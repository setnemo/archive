#!/usr/bin/php
<?PHP
	$line = preg_replace("( +)", " ", trim($argv[1]));
	if ($line)
		echo "$line", PHP_EOL;
?>

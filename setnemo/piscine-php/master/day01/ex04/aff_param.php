#!/usr/bin/php
<?PHP
	if ($argc == 1)
		return ;
	foreach ($argv as $key => $value) {
		if ($key != 0)
			echo "$value", PHP_EOL;
	}
?>

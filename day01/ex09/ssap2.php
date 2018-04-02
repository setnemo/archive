#!/usr/bin/php
<?PHP
	function ft_split($input) {
		$line = trim($input);
		$line = preg_replace("( +)", " ", $line);
		$arr = array();
		if ($line)
			$arr =  explode(' ', $line);
		sort($arr);
		return ($arr);
	}
	$arr = array();
	for ($i = 1; $i < $argc; $i++) {
		$split = ft_split($argv[$i]);
		foreach ($split as $elem) {
			array_push($arr, $elem);
		}
	}
	foreach ($array as $line) {
		if (ctype_alpha($line))
			$alpha[] = $line;
		else if (is_numeric($line))
			$digits[] = $line;
		else
			$ascii[] = $line;
	}
	if (!(empty($alpha))) {
		sort($alpha, SORT_FLAG_CASE | SORT_STRING);
		foreach ($alpha as $line)
			echo $line . PHP_EOL;
	}
	if (!(empty($digits))) {
		sort($digits, SORT_STRING);
		foreach ($digits as $line)
			echo $line . PHP_EOL;
	}
	if (!(empty($ascii))) {
		sort($ascii, SORT_STRING);
		foreach ($ascii as $line)
			echo $line . PHP_EOL;
	}
?>

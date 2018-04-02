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
	sort($arr, SORT_STRING);
	foreach ($arr as $line) {
		echo "$line" . PHP_EOL;
	}
?>

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
	$rostring = ft_split($argv[1]);
	if ($argc == 1 || !($rostring))
		return ;
	for ($i = 1; $i < count($rostring); $i++)
		echo "$rostring[$i] ";
	if ($argc > 1)
		echo "$rostring[0]", PHP_EOL;
?>

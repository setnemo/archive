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
	function pri1($a , $b)
	{
		$f1 = 0;
		$f2 = 0;
		if ( $a >= 97 && $a <= 122) {
			$f1 = 1;
			$a = $a - 32;
		}
		if($b >= 97 && $b <= 122) {
			$f2 = 1;
			$b = $b - 32;
		}
		if($a == $b)
		{
			if($f1 == 1 && $f2 != 1) {
				return (1);
			}
			if($f1 == 1 && $f2 == 1) {
				return(0);
			}
			if($f1 != 1 && $f2 == 1) {
				return(-1);
			}
			if($f1 != 1 && $f2 != 1){
				return(0);
			}
		}
		return ($a < $b) ? -1 : 1;
	}

	function pri($it)
	{
		$ti = ord($it);
		if(($ti >= 65 && $ti <= 90) || ($ti >= 97 && $ti <= 122)) {
			return (1);
		}
		else if($ti >= 48 && $ti <= 57) {
			return(2);
		}
		else {
			return(3);
		}
	}

	function cmp($a, $b)
	{
		$c = pri($a);
		$d = pri($b);
		if($c == $d)
		{
			if (ord($a) ==  ord($b)) {
				return 0;
			}
			if($c == 1) {
				return(pri1(ord($a), ord($b)));
			}
			return (ord($a) < ord($b)) ? -1 : 1;
		}
		return ($c < $d) ? -1 : 1;
	}

	if ($argc > 1)
	{
		$array = array();
		foreach ($argv as $elem)
		{
			$split = array_filter(explode(" ", $elem), 'strlen');
			$array = array_merge($array, $split);
		}
		$array = array_filter($array, 'strlen');
		array_shift($array);
		usort($array, "cmp");
		if (!(empty($array))) {
			foreach ($array as $line)
				echo $line . PHP_EOL;
		}
	}
?>

#!/usr/bin/php
<?PHP
	if ($argc == 2) {
		$str = trim($argv[1]);
		$arr = str_split($str);
		$arr1 = array();
		$arr2 = array();
		$arr3 = array();
		$i = 0;
		$skip = 0;
		$br = 0;
		foreach ($arr as $item) {
			if ($i != 0 && ($item == '-' || $item == '+'  || $item == '*'  || $item == '/'  || $item == '%' )) {
				if ($skip) {
					$skip == 2;
				}
				else {
					$skip = 1;
				}
			}
			if ($skip == 1) {
				$arr2[0] = $item;
				$i = 0;
				$skip = 2;
				$br++;
				if ($br > 1) {
					echo 'Syntax Error' . PHP_EOL;
					return (-42);
				}

			}
			else if ($skip == 0) {
				$arr1[$i] = $item;
				$i++;
			}
			else {
				$arr3[$i] = $item;
				$i++;
			}
		}
		$minus = 0;
		$plus = 0;
		$valid3 = 0;
		foreach ($arr1 as $item) {
		 	$arrstr1 .= $item;
		 	if (ord($item) == 45) {
		 		$minus++;
		 	}
		 	if (ord($item) == 43) {
		 		$plus++;
		 	}
		 	if (is_numeric($item)) {
		 		$valid3++;
		 	}
		}
		if ($minus > 1 || $plus > 1) {
			return (-42);
		}
		$minus = 0;
		$plus = 0;
		$valid3 = 0;
		foreach ($arr2 as $item) {
		 	$arrstr2 .= $item;
		 	if (ord($item) == 45) {
		 		$minus++;
		 	}
		 	if (ord($item) == 43) {
		 		$plus++;
		 	}
		 	if (is_numeric($item)) {
		 		$valid3++;
		 	}
		}
		if ($minus > 1 || $plus > 1 || $minus == 1 && $plus == 1) {
			echo 'Syntax Error' . PHP_EOL;
			return (-42);
		}
		$minus = 0;
		$plus = 0;
		$valid3 = 0;
		foreach ($arr3 as $item) {
		 	$arrstr3 .= $item;
		 	if (ord($item) == 45) {
		 		$minus++;
		 	}
		 	if (ord($item) == 43) {
		 		$plus++;
		 	}
		 	if (is_numeric($item)) {
		 		$valid3++;
		 	}
		}
		if ($minus > 1 || $plus > 1) {
			echo 'Syntax Error' . PHP_EOL;
			return (-42);
		}
		if (!$arrstr3)
			$arrstr3 = '0';
		$arrstr1 = trim($arrstr1);
		$arrstr3 = trim($arrstr3);
		if (!is_numeric($arrstr1) || !is_numeric($arrstr3) || $arrstr3 == 0 || strstr($arrstr1, " ")) {
			echo "Syntax Error" . PHP_EOL;
		}
		else {
			switch ($arrstr2) {
				case '+':
					echo $arrstr1 + $arrstr3 . PHP_EOL;
					break ;
				case '-':
					echo $arrstr1 - $arrstr3 . PHP_EOL;
					break ;
				case '*':
					echo $arrstr1 * $arrstr3 . PHP_EOL;
					break ;
				case '/':
					if ($arrstr3 == 0) {
						echo 'Incorrect Parameters' . PHP_EOL;
						break ;
					}
					echo $arrstr1 / $arrstr3 . PHP_EOL;
					break ;
				case '%':
					if ($arrstr3 == 0) {
						echo 'Incorrect Parameters' . PHP_EOL;
						break ;
					}
					echo $arrstr1 % $arrstr3 . PHP_EOL;
					break ;
			}
		}
		}
		else {
			echo 'Incorrect Parameters' . PHP_EOL;
		}
?>

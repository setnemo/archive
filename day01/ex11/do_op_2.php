#!/usr/bin/php
<?PHP
	if ($argc == 2) {
		$str = str_replace(" ", "", $argv[1]);
		$arr = str_split($str);
		$arr1 = array();
		$arr2 = array();
		$arr3 = array();
		$i = 0;
		$skip = 0;
		foreach ($arr as $item) {
			if ($i != 0 && ($item == '-' || $item == '+'  || $item == '*'  || $item == '/'  || $item == '%' )) {
				$skip = 1;
			}
			if ($skip == 1) {
				$arr2[0] = $item;
				$i = 0;
				$skip = 2;
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
		foreach ($arr1 as $item) {
		 	$arrstr1 .= $item;
		}
		$arrstr2 = $arr2[0];
		foreach ($arr3 as $item) {
		 	$arrstr3 .= $item;
		}
		if (!$arrstr3)
			$arrstr3 = '0';
		if (!is_numeric($arrstr1) || !is_numeric($arrstr3)){
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

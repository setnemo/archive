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
		for ($i=0; $arr1[$i]; $i++) { 
			$arrstr1 .= $arr1[$i];
		}
		$arrstr2 = $arr2[0];
		for ($i=0; $arr3[$i]; $i++) { 
			$arrstr3 .= $arr3[$i];
		}
		}
		else {
			echo 'Incorrect Parameters' . PHP_EOL;
		}
?>

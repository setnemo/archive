#!/usr/bin/php
<?php
	function get_http_response_code($theURL) {
		$headers = get_headers($theURL);
		return substr($headers[0], 9, 3);
	}
	if ($argv[1]) {

		$html = file_get_contents($argv[1]);
		$name = substr(strstr($argv[1], "//"), 2);
		preg_match_all('/<img[^>]+>/i',$html, $result); 
		$i = 0;
		$img = array();
		foreach ($result[0] as $line)
		{
			$img[$i] = trim(preg_replace("( +)", " ", preg_replace("(\n+)", " ", $line)));
			preg_match_all('/src=("[^"]*")/i',$line, $img[$line]);
			$i++;
		}
		if(!is_dir($name)) {
			mkdir($name, 0777, true);
		}
		foreach ($img as $key ) {
			if (strlen($key[1][0]) > 1 && !strstr($key[1][0], "//")) {
				$key[1][0] = preg_replace("(\")", "", $key[1][0]);
				$tempname = strrchr($key[1][0], "/");
				$tempname = mb_substr($tempname, 1);
				if ($key[1][0][0] != '/'){
					$key[1][0] = $argv[1] . "/" . $key[1][0];
				}
				else {
					$key[1][0] = $argv[1] . $key[1][0];
				}
				if (get_http_response_code($key[1][0]) == 200) {
					$tempimg = file_get_contents($key[1][0]);
				}
				if (strlen($tempname) > 0) {
					file_put_contents($name . "/" .$tempname, $tempimg);
				}
			}
		}
	}
?>
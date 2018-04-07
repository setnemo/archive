#!/usr/bin/php
<?php
	$fd = fopen("/var/run/utmpx", 'r');
	date_default_timezone_set("Europe/Kiev");
	while ($str = fread($fd, 628)) {
		$elem = unpack("a256user/a4id/a32line/ipid/itype/Itime", $str);
		if ($elem[type] == 7) {
			echo "$elem[user] $elem[line]  ". date('M  j H:i', $elem[time])."\n";
		}
	}
?>

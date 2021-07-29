#!/usr/bin/php
<?PHP
if ($argv[2])
{
	$str = $argv;
	foreach ($str as $value)
	{
		if ($value == $str[0] || $value == $str[1])
			continue ;
		$elem = explode(":", $value);
		if (count($elem) > 2)
			$key[$elem[0]] = substr($value, strlen($elem[0]) + 1);
		else
			$key[$elem[0]] = $elem[1];
	}
	if ($key[$argv[1]])
		echo $key[$argv[1]]."\n";
}
?>

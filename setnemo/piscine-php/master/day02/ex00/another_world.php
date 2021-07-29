#!/usr/bin/php
<?PHP
if ($argv[1])
{
	echo trim(preg_replace("( +)", " ", preg_replace("(\t+)", " ", $argv[1]))) . PHP_EOL;
}
?>

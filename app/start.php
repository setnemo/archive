<?php

require_once('RatpClient.php'); 

if (isset($_POST['first']) && isset($_POST['last']))
{
	$c = new RatpClient();
	$r1 = $c->getMetro($_POST['first']);
	echo "<pre>";
	print_r($r1);
	echo "</pre>";

	$r2 = $c->getMetro($_POST['last']);
	echo "<pre>";
	print_r($r2);
	echo "</pre>";
	
}

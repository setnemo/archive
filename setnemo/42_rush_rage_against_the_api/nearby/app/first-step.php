<?php

require_once('RatpClient.php'); 


$c = new RatpClient();
$r = $c->getPlace('gare');
echo "<pre>";
print_r($r);
echo "</pre>";


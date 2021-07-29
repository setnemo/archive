<?php

require_once('RatpClient.php'); 


$c = new RatpClient();
$r = $c->getMetro('gare');
// echo "<pre>";
// print_r($r);
// echo "</pre>";

$r = $c->getTest('stop_area:OIF:SA:8768600');
echo "<pre>";
print_r($r);
echo "</pre>";


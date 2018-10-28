<?php

require_once('RatpClient.php'); 


$c = new RatpClient();
$r = $c->getMetro('gare');
// echo "<pre>";
// print_r($r);
// echo "</pre>";

$r = $c->getTest('networks/network%3AOIF%3A439/routes?depth=3&');
$routes = $c->getRoutes($r['routes']);
echo "<pre>";
print_r($routes);
echo "</pre>";

// https://api.navitia.io/v1/coverage/sandbox/networks/network%3ARAT%3A1/routes?depth=3&
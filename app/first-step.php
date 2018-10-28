<?php

require_once('RatpClient.php'); 


$c = new RatpClient();
$r = $c->getMetro('gare');
// echo "<pre>";
// print_r($r);
// echo "</pre>";

$r = $c->getTest('networks/network%3AOIF%3A439/routes?depth=3&');
$routes = $c->getRoutes($r['routes']);
// $matrix = $c->getMatrix($routes);


// $journey = $c->getJourney($routes, 'stop_point:OIF:SP:59213', 'stop_point:OIF:SP:59322');
$journey = $c->getJourney($routes, 'Nation (Paris)', 'Opéra (Paris)');
echo "<pre>";
print_r($journey);
echo "</pre>";
// https://api.navitia.io/v1/coverage/sandbox/networks/network%3ARAT%3A1/routes?depth=3&
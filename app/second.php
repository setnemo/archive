<?php

require_once('RatpClient.php'); 
require_once('JorneyFinder.php');

$c = new RatpClient();
$r = $c->getMetro('gare');
$routes = $c->getRoutes();
// $matrix = $c->getMatrix($routes);

$jf = new JourneyFinder();


// echo "<pre>";
// print_r($journey);
// echo "</pre>";
// https://api.navitia.io/v1/coverage/sandbox/networks/network%3ARAT%3A1/routes?depth=3&


if (isset($_POST['first']) && isset($_POST['last']) && strlen($_POST['first']) > 0 && strlen($_POST['last']) > 0 )
{
$journey = $jf->getJourney($routes, $_POST['first'], $_POST['last']);
	?>


	<div ><hr><?php
	if (count($$journey) == 0 ) { exit ;}
	foreach ($journey as $key) { ?>
        <?php echo $key['label']; ?><br>

<?php }
	?>

	</div>


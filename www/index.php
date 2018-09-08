<?php

ini_set('display_errors', 1);
error_reporting(E_ALL);

define('ROOT', dirname(__FILE__));
require_once(ROOT.'/components/Router.php');
require_once(ROOT.'/components/Db.php');
$router = new Router();
$router->run();

// $teststring = "20-08-2018";
// $pattern = '/([0-9]{2})-([0-9]{2})-([0-9]{4})/';
// $replacement = 'Year $3, Month $2, Day $1<br>';
// echo preg_replace($pattern, $replacement, $teststring);
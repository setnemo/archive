<?php
	session_start();

	include 'auth.php';

	if (auth($_GET['login'], hash("whirlpool", $_GET['passwd']))) {
		$_SESSION['authorized_user'] = $_GET['login'];
		echo "OK" . PHP_EOL;
	}
	else {
		$_SESSION['authorized_user'] = "";
		echo "ERROR" . PHP_EOL;
	}

?>

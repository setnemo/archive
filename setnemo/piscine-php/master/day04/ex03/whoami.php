<?php
session_start();

	if ($_SESSION['authorized_user'])
		echo $_SESSION['authorized_user'] . PHP_EOL;
	else
		echo "ERROR" . PHP_EOL;
?>

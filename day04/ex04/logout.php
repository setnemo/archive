<?php
	session_start();
	$_SESSION['authorized_user'] = NULL;
	header("Location: index.html",TRUE,301);
?>

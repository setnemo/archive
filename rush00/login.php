<?php
	session_start();

	function auth($login, $passwd) {
		$arr = unserialize(file_get_contents("../private/passwd"));
		foreach ($arr as $key => $inarr) {
			if ($inarr['login'] === $login && $inarr['passwd'] === $passwd) {
				return (true);
			}
		}
		return (false);
	}
	if (auth($_POST['login'], hash("whirlpool", $_POST['passwd']))) {
		$_SESSION['authorized_user'] = $_POST['login'];
		header("Location: index.php?signin=success",TRUE,301);
	}
	else {
		$_SESSION['authorized_user'] = "";
		header("Location: index.php?signin=error",TRUE,301);
	}

?>

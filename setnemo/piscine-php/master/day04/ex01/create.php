<?php
	function exiterror() {
		echo "ERROR" . PHP_EOL;
		exit ;
	}
	if ($_POST['submit'] === "OK") {
		if ($_POST['login']) {
			if (!$_POST['passwd']) {
				exiterror();
			}
			if (!(file_exists("../private")))
				mkdir("../private", 0777, true);
			$login = $_POST['login'];
			$passwd = hash("whirlpool", $_POST['passwd']);
			$arr = unserialize(file_get_contents("../private/passwd"));
			foreach ($arr as $inarr) {
				if ($inarr['login'] === $login) {
					exiterror();
				}
			}
			$new_arr = array('login' => $login, 'passwd' => $passwd);
			$arr[] = $new_arr;
			file_put_contents('../private/passwd', serialize($arr));
			echo "OK" . PHP_EOL;
		}
		else {
			exiterror();
		}
	}
	else {
		exiterror();
	}
?>

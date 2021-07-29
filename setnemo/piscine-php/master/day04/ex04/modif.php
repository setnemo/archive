<?php
	function exiterror() {
		echo "ERROR" . PHP_EOL;
		header("Location: index.html",TRUE,301);
		exit ;
	}
	if ($_POST['submit'] === "OK" && $_POST['login'] && $_POST['oldpw'] && $_POST['newpw'])
	{
		if (!(file_exists("../private")))
			mkdir("../private", 0777, true);
		$login = $_POST['login'];
		$oldpw = hash("whirlpool", $_POST['oldpw']);
		$newpw = hash("whirlpool", $_POST['newpw']);
		$arr = unserialize(file_get_contents("../private/passwd"));
		foreach ($arr as $key => $inarr) {
			if ($inarr['login'] === $login && $inarr['passwd'] === $oldpw)
			{
				$arr[$key]['passwd'] = $newpw;
				file_put_contents('../private/passwd', serialize($arr));
				echo "OK" . PHP_EOL;
				header("Location: index.html",TRUE,301);
				exit ;
			}
			else
				exiterror();
		}
	}
	else
		exiterror();
?>

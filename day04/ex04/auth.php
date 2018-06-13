<?php
	function auth($login, $passwd) {
		$arr = unserialize(file_get_contents("../private/passwd"));
		foreach ($arr as $key => $inarr) {
			if ($inarr['login'] === $login && $inarr['passwd'] === $passwd) {
				return (true);
			}
		}
		return (false);
	}
?>

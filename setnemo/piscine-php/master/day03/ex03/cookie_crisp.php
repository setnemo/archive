<?PHP
	if ($_GET['action'] == "set")
	{
		if ($_GET['name'] && $_GET['value'])
			setcookie($_GET['name'], $_GET['value']);
		else if ($_GET['name'])
			setcookie($_GET['name'], "");
	}
	if ($_GET['action'] == "get")
		echo $_COOKIE[$_GET['name']];
	if ($_GET['action'] == "del")
	{
		if ($_GET['value'])
			setcookie($_GET['name'], $_GET['value'], time() - 3600);
		else
			setcookie($_GET['name'], "", time() - 3600);
	}
?>
<?php
	if ($_SESSION['authorized_user'])
	{
		if (!file_exists('../private/user_basket')) {
			mkdir("../private/user_basket");
		}
		if (!file_exists('../private/user_basket/'.$_SESSION['authorized_user'].'_user_basket')) {
			file_put_contents('../private/user_basket/'.$_SESSION['authorized_user'].'_user_basket', null);
		}
		$basket = unserialize(file_get_contents('../private/user_basket/'.$_SESSION['authorized_user'].'_user_basket'));
		
		if (!file_exists('../private/user_order')) {
			mkdir("../private/user_order");
		}
		if (!file_exists('../private/user_order/'.$_SESSION['authorized_user'].'user_order')) {
			file_put_contents('../private/user_order/'.$_SESSION['authorized_user'].'user_order', null);
		}
		$tmp['authorized_user'] = $_SESSION['authorized_user'];
		$basket[] = $tmp;
		file_put_contents('../private/user_order/'.$_SESSION['authorized_user'].'user_order', $basket);
		header("Location: index.php",TRUE,301);
	}
	else {
		header("Location: index.php",TRUE,301);
	}
?>
<?php

function generateNewPassword($length = 10) {
	$characters = '0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ';
	$charactersLength = strlen($characters);
	$newPassword = '';
	for ($i = 0; $i < $length; $i++) {
	    $newPassword .= $characters[rand(0, $charactersLength - 1)];
	}
	return $newPassword;
}

return generateNewPassword();
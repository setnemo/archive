#!/usr/bin/php
<?php



class User {
	
	public $name;
	public $pwd;
	public $email;
	public $city;

	function __construct($name, $pwd, $email, $city) {
		$this->name = $name;
		$this->pwd = $pwd;
		$this->email = $email;
		$this->city = $city;
	}

	function getinfo() {
		return "{$this->name}" . "{$this->pwd}" . "{$this->email}" . "{$this->city}"
	}
}

	$admin = new User("Name", "pwd", "email", "city");

	var_dump($admin);

?>
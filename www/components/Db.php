<?php 

class Db {

  public static function getConnection() {
    $params = include(ROOT.'/config/db_settings.php');
    $conn = new PDO("mysql:host=".$params['servername'].";dbname=".$params['dbname'], $params['username'], $params['password']);
    return $conn;
  }
}

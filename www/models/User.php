<?php

class User {

  public static function getAuth($user, $pass) {
    
  $conn = Db::getConnection();
    
    $hashpass = hash('whirlpool', $pass);
    $result = $conn->query("
    SELECT
      status
    FROM
      users
    WHERE login=\"".$user."\" AND password=\"".$hashpass."\";
    ");
    return $result->fetch();
  }    
}
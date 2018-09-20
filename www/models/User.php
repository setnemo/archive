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

  public static function getLogout() {

    $_SESSION['auth'] = null;
    $_SESSION['login'] = null;
    header("Location: /");
    return true;
  }

  public static function getAccount() {

    //
    return true;
  }

  public static function getEdit() {

    //
    return true;
  }

  public static function getRecovery() {

    //
    return true;
  }

  public static function getRegister() {

    //
    return true;
  }
}
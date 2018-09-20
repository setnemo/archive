<?php

include_once ROOT.'/models/Email.php';

class User {

  public static function getAuth($user, $pass) {
    
    $conn = Db::getConnection();
    
    $hashpass = hash('whirlpool', $pass);
    $result = $conn->query("
    SELECT
      status
    FROM
      users
    WHERE login=\"".$user."\" AND password=\"".$hashpass."\" AND status = 1;
    ");
    $fetch = $result->fetch();
    if ($fetch['status'])
      return true;
    else
      return false;
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

  public static function getAdd() {

  $conn = Db::getConnection();
  $result = $conn->query("
    SELECT
      id
    FROM
      users
    WHERE
      login = \"".$_POST['login']."\" OR email = \"".$_POST['email']."\";
    ");
  $fetch = $result->fetch();
  if ($fetch)
  {
    return false;
  }
  else
  {
    $token = hash('whirlpool', $_POST['login'].$_POST['pass'].time());
    $insert = $conn->prepare("INSERT INTO users (login, email, password, firstname, lastname, token) VALUES (?, ?, ?, ?, ?, ?)");
    $insert->execute([$_POST['login'], $_POST['email'], hash('whirlpool', $_POST['pass']), $_POST['firstname'], $_POST['lastname'], $token]);
    $emailObj = new Email;
    $tokenUrl = $_SERVER['SERVER_NAME'].'/token/'.$token.'/'.$_POST['email'].'/';
    $confirm = Email::confirmEmail($_POST['email'], $_POST['login'], $tokenUrl);
  }
    return true;
  }
}

<?php

include_once ROOT.'/models/Email.php';

class User {

  public static function getAuth($user, $pass) {
    
    $conn = Db::getConnection();
    
    $hashpass = hash('whirlpool', $pass);
    $result = $conn->query("
    SELECT
      *
    FROM
      users
    WHERE login=\"".$user."\" AND password=\"".$hashpass."\" AND status = 1;
    ");
    $fetch = $result->fetch();
    if ($fetch['status']) {
      $_SESSION['user_id'] = $fetch['id'];
      return true;
    }
    else
      return false;
  }

  public static function getLogout() {

    $_SESSION['auth'] = null;
    $_SESSION['login'] = null;
    header("Location: " . $_SESSION['enter']);
    return true;
  }

  public static function getNewpassword() {

    $conn = Db::getConnection();
    
    $result = $conn->prepare("
    SELECT
      id
    FROM
      users
    WHERE login=? AND email=? AND firstname=? AND lastname=? AND status = 1;
    ");
    $result->execute([$_POST['login'], $_POST['email'], $_POST['firstname'], $_POST['lastname']]);
    $fetch = $result->fetch();
    if ($fetch)
    {
      $newpassword = include(ROOT.'/config/generator.php');
      $insert = $conn->prepare("UPDATE users SET password=? WHERE email=?;");
      $newhash = hash('whirlpool', $newpassword);
      $insert->execute([$newhash, $_POST['email']]);
      $insert->fetch();
      $emailObj = new Email;
      $confirm = Email::confirmPassword($_POST['email'], $newpassword);
      return true;
    }
    return false;
  }


  public static function getAdd() {

  if (isset($_SESSION['login']) && $_SESSION['login'] == '' || !isset($_SESSION['login']) ) { 

  $conn = Db::getConnection();
  $result = $conn->prepare("
    SELECT
      id
    FROM
      users
    WHERE
      login = ? OR email = ? ;
    ");
  $result->execute([$_POST['login'], $_POST['email']]);
  $fetch = $result->fetch();
  if ($fetch)
  {
    return false;
  }
  $token = hash('whirlpool', $_POST['login'].$_POST['pass'].time());
  $insert = $conn->prepare("INSERT INTO users (login, email, password, firstname, lastname, token) VALUES (?, ?, ?, ?, ?, ?)");
  $insert->execute([$_POST['login'], $_POST['email'], hash('whirlpool', $_POST['pass']), $_POST['firstname'], $_POST['lastname'], $token]);
  $emailObj = new Email;
  $tokenUrl = $_SERVER['SERVER_NAME'].'/token/'.$token.'/'.$_POST['email'].'/';
  $confirm = Email::confirmEmail($_POST['email'], $_POST['login'], $tokenUrl);
  return true;
  }
  return false;
  }

  public static function getEdit() {

    if (!isset($_SESSION['login'])) { return false;}

    $conn = Db::getConnection();

    $data = array();
    foreach ($_POST as $key => $value) {
      if ($value)
      {
        $data[$key] = $value;
      }
    }
    if (array_key_exists('password', $data))
    {
      $result = $conn->prepare("
      SELECT
        id
      FROM
        users
      WHERE login=? AND password=? ;
      ");
      $result->execute([$_SESSION['login'], hash('whirlpool', $_POST['password'])]);
      $fetch = $result->fetch();
      if ($fetch)
      {
        if (count($data) >= 1)
        {
          if (array_key_exists('passn1', $data) && array_key_exists('passn2', $data) && array_key_exists('passn1', $data) == array_key_exists('passn2', $data))
          {
            // change password
            $insert = $conn->prepare("UPDATE users SET password=? WHERE login=?;");
            $insert->execute([hash('whirlpool', $data['passn2']), $_SESSION['login']]);
            $insert->fetch();
          }
          if (array_key_exists('login', $data))
          {
            $result = $conn->prepare("
            SELECT
              id
            FROM
              users
            WHERE login=? ;
            ");
            $result->execute([$data['login']]);
            $fetch = $result->fetch();
            if ($fetch)
              return false;
            else 
            {
              $insert = $conn->prepare("UPDATE users SET login=? WHERE login=?;");
              $insert->execute([$data['login'], $_SESSION['login']]);
              $insert->fetch();
              $_SESSION['login'] = $data['login'];
            }
          }
          if (array_key_exists('email', $data))
          {
            $result = $conn->prepare("
            SELECT
              id
            FROM
              users
            WHERE email=? ;
            ");
            $result->execute([$data['email']]);
            $fetch = $result->fetch();
            if ($fetch)
              return false;
            else 
            {
              $insert = $conn->prepare("UPDATE users SET email=? WHERE login=?;");
              $insert->execute([$data['email'], $_SESSION['login']]);
              $insert->fetch();
            }
          }
          if (array_key_exists('firstname', $data))
          {
            $insert = $conn->prepare("UPDATE users SET firstname=? WHERE login=?;");
            $insert->execute([$data['firstname'], $_SESSION['login']]);
            $insert->fetch();
          }
          if (array_key_exists('lastname', $data))
          {
            $insert = $conn->prepare("UPDATE users SET lastname=? WHERE login=?;");
            $insert->execute([$data['lastname'], $_SESSION['login']]);
            $insert->fetch();
          }
          if (array_key_exists('action', $data))
          {
            $insert = $conn->prepare("UPDATE users SET action=? WHERE login=?;");
            $insert->execute(['1', $_SESSION['login']]);
            $insert->fetch();
          } else {
            $insert = $conn->prepare("UPDATE users SET action=? WHERE login=?;");
            $insert->execute(['0', $_SESSION['login']]);
            $insert->fetch();

          }

            return true;
        }
      }
    }
    return false;
  }

  public static function getAccountData($login) {

    if (!isset($_SESSION['login'])) { return false;}
    $conn = Db::getConnection();

    $result = $conn->prepare("
    SELECT
      *
    FROM
      users
    WHERE login=?;
    ");
    $result->execute([$login]);
    return $result->fetch();
  }

  public static function getAvatars() {

    $conn = Db::getConnection();
    $result = $conn->query("
      SELECT
        login, email
      FROM
        users;
      ");
    $fetch = $result->fetchAll(PDO::FETCH_ASSOC);
    $data = array();
    foreach ($fetch as $key) {
        $data[$key['login']] = md5( strtolower( trim( $key['email'] ) ) );
    }
    return $data ;
  }
  
  public static function getRecovery() {

    // silence is golden
    return true;
  }

  public static function getRegister() {

    // silence is golden
    return true;
  }

  public static function getAccount() {

    // silence is golden
    return true;
  }
  
}

<?php

include_once ROOT.'/models/Email.php';

class Token {

  public static function confirmToken($token, $email) {

  $conn = Db::getConnection();
  $result = $conn->prepare("
    SELECT
      id
    FROM
      users
    WHERE
      token = ? AND email = ? AND status = 0;
    ");
  $result->execute([$token, $email]);
  $result = $result->fetch();
  if ($result)
  {
    $insert = $conn->prepare("UPDATE users SET status=1 WHERE email=?;");
    $insert->execute([$email]);
    $insert->fetch();
    $emailObj = new Email;
    $confirm = Email::confirmAccount($email);
    return true;
  }
  else
  {
    return false;
  }
  return false;
  }

}
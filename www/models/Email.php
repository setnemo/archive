<?php

include_once ROOT.'/models/Email.php';

class Email {

  public static function confirmEmail($email, $login, $tokenUrl) {

    include_once ROOT.'/views/templates/email-confirm.php';

    $message = confirmation($login, $tokenUrl);
    $subject = "CAMAGRU: Confirm your email";
    // Always set content-type when sending HTML email
    $headers = "MIME-Version: 1.0" . "\r\n";
    $headers .= "Content-type:text/html;charset=UTF-8" . "\r\n";

    // More headers
    $headers .= 'From: <real@camagru.pp.ua>' . "\r\n";

    mail($email, $subject, $message, $headers, '-freal@camagru.pp.ua');
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
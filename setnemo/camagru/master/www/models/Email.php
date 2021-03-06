<?php

class Email {

  public static function confirmEmail($email, $login, $tokenUrl) {

    include_once ROOT.'/views/templates/email-confirm.php';

    $message = confirmation($login, $tokenUrl);
    $subject = "CAMAGRU: Confirm your email";
    // Always set content-type when sending HTML email
    $headers = "MIME-Version: 1.0" . "\r\n";
    $headers .= "Content-type:text/html;charset=UTF-8" . "\r\n";

    // More headers
    $headers .= 'From: <no-reply@camagru.pp.ua>' . "\r\n";

    mail($email, $subject, $message, $headers, '-fno-reply@camagru.pp.ua');
    return true;
  }

  public static function confirmAccount($email) {

    include_once ROOT.'/views/templates/email-success.php';

    $message = confirmation();
    $subject = "CAMAGRU: Account confirmed!";
    // Always set content-type when sending HTML email
    $headers = "MIME-Version: 1.0" . "\r\n";
    $headers .= "Content-type:text/html;charset=UTF-8" . "\r\n";

    // More headers
    $headers .= 'From: <no-reply@camagru.pp.ua>' . "\r\n";

    mail($email, $subject, $message, $headers, '-fno-reply@camagru.pp.ua');
    return true;
  }

  public static function confirmPassword($email, $newpassword) {

    include_once ROOT.'/views/templates/email-newpassword.php';

    $message = confirmation($newpassword);
    $subject = "CAMAGRU: Generate new password!";
    // Always set content-type when sending HTML email
    $headers = "MIME-Version: 1.0" . "\r\n";
    $headers .= "Content-type:text/html;charset=UTF-8" . "\r\n";

    // More headers
    $headers .= 'From: <no-reply@camagru.pp.ua>' . "\r\n";

    mail($email, $subject, $message, $headers, '-fno-reply@camagru.pp.ua');
    return true;
  }

  public static function commentNotification($fetch, $post) {

    include_once ROOT.'/views/templates/email-notification.php';

    $message = confirmation($fetch, $post);
    $subject = "CAMAGRU: New comment!";
    // Always set content-type when sending HTML email
    $headers = "MIME-Version: 1.0" . "\r\n";
    $headers .= "Content-type:text/html;charset=UTF-8" . "\r\n";

    // More headers
    $headers .= 'From: <no-reply@camagru.pp.ua>' . "\r\n";

    mail($fetch['email'], $subject, $message, $headers, '-fno-reply@camagru.pp.ua');
    return true;
  }

}
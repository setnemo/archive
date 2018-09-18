<?php

include_once ROOT.'/models/User.php';

class UserController {
  
  public function actionIndex() {
    // echo "UserController actionIndex<br>";
    $login = User::getAuth($_POST['login'], $_POST['pass']);
    // echo "<pre>";
    // echo "UserController actionLogin<br>";
    // print_r($login);
    // echo "</pre>";
    if ($login) {
      $_SESSION['auth'] = session_id();
      $_SESSION['login'] = $_POST['login'];
      header("Location: /");
    }
    return false ;
  }
  public function action404() {
    require_once(ROOT.'/views/login/index.php');
    return true;
  }
  public function actionExternal($user, $pass) {
    return true;
  }
}
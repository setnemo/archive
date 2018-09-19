<?php

include_once ROOT.'/models/User.php';

class UserController {
  
  public function actionIndex() {
    if (isset($_SESSION['auth']) && $_SESSION['auth'] == session_id())
    {
      header("Location: /account/");
      exit ;
    }
    if (!isset($_POST['login']) || !isset($_POST['pass']))
    {
      require_once(ROOT.'/views/login/index.php');
      return true;
    }
    $login = User::getAuth($_POST['login'], $_POST['pass']);
    if ($login)
    {
      $_SESSION['auth'] = session_id();
      $_SESSION['login'] = $_POST['login'];
      header("Location: /");
      exit ;
    }
    return false ;
  }
  public function action404() {
    require_once(ROOT.'/views/login/index.php');
    return true;
  }
  public function actionExternal($user, $pass) {
    if ($pass == 'logout')
    {
      $_SESSION['auth'] = null;
      $_SESSION['login'] = null;
      header("Location: /");
      exit ;
    }
    return true;
  }
}
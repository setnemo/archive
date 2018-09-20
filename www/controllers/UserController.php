<?php

include_once ROOT.'/models/User.php';

class UserController {
  
  public function actionIndex() {
    if (isset($_SESSION['auth']) && $_SESSION['auth'] == session_id())
    {
      header("Location: /");
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

  public function actionExternal($login, $params) {

    $valid = ['logout', 'recovery', 'edit', 'account', 'register'];

    if (in_array($params, $valid))
    {
      $methodName = 'get' . ucfirst($params);
    }
    else
    {
      header("HTTP/1.0 404 Not Found");
      return true;
    }
    if ($params == 'register' && isset($_SESSION['auth']) && $_SESSION['auth'] == session_id())
    {
      header("Location: /");
      exit ;
    }
    if (($params == 'account' || $params == 'edit')  && !isset($_SESSION['auth']))
    {
      header("Location: /");
      exit ;
    }
    User::$methodName();
    if ($params != 'logout')
    {
      require_once(ROOT.'/views/login/'.$params.'.php');
    }
    return true;
  }

  public function action404() {
      require_once(ROOT.'/views/login/index.php');
      return true;
  }
}
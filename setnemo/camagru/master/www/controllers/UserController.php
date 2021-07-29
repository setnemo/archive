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
      header("Location: " . $_SESSION['enter']);
      exit ;
    }else{
      require_once(ROOT.'/views/login/index.php');
      return true;
    }
    return false ;
  }

  public function actionExternal($login, $params) {

    $valid = ['logout', 'recovery', 'account', 'register', 'add', 'newpassword', 'edit'];

    if (in_array($params, $valid))
    {
      $methodName = 'get' . ucfirst($params);
    }
    else
    {
      header("Location: /");
      return true;
    }
    if ($params == 'register' && isset($_SESSION['auth']) && $_SESSION['auth'] == session_id())
    {
      header("Location: /");
      return true;
    }
    if (($params == 'account' || $params == 'edit')  && !isset($_SESSION['auth']))
    {
      header("Location: /");
      return true;
    }
    $status = User::$methodName();
    if ($params == 'account' && $_SESSION['login']) {
      $account_data = User::getAccountData($_SESSION['login']);
    }
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
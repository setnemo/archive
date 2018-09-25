<?php

include_once ROOT.'/models/Post.php';

class ActionController {
  
  public function actionIndex($user) {

    header("HTTP/1.0 404 Not Found");
    return true;
  }

  public function actionExternal($what, $action) {


    if ($what != 'infinity') {
      $methodName = 'get' . ucfirst($action). ucfirst($what);
      // echo $methodName;
      if (count($_POST) < 1 || !isset($_SESSION['login']) ) { header("HTTP/1.0 404 Not Found"); exit ;}
    }
    $postsList = array();
    if ($what == 'infinity') {
      $methodName = 'get' . ucfirst($what);
      $postsList = Post::$methodName($action, null, null);
      return true;
    } 
    // $postsList = Post::$methodName($_POST['post'], $_SESSION['user']);
    // session_start();
    $fix = '';
    if (isset($_POST['fix'])) { $fix = $_POST['fix']; }
    $postsList = Post::$methodName($_POST['post'], $_SESSION['login'], $fix);
    return true;
  }

  public function action404() {
    header("HTTP/1.0 404 Not Found");
    return true;
  }
}
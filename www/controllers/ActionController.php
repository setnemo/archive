<?php

include_once ROOT.'/models/Post.php';

class ActionController {
  
  public function actionIndex($user) {

    header("HTTP/1.0 404 Not Found");
    return true;
  }

  public function actionExternal($what, $action) {

    $methodName = 'get' . ucfirst($action). ucfirst($what);
    // echo $methodName;
    if (!isset($_POST['post']) || !isset($_SESSION['login']) ) { header("HTTP/1.0 404 Not Found"); exit ;}
    $postsList = array();
    // $postsList = Post::$methodName($_POST['post'], $_SESSION['user']);
    // session_start();
    $postsList = Post::$methodName($_POST['post'], $_SESSION['login']);
    return true;
  }

  public function action404() {
    header("HTTP/1.0 404 Not Found");
    return true;
  }
}
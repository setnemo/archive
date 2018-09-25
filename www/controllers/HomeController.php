<?php

include_once ROOT.'/models/Post.php';
include_once ROOT.'/models/User.php';

class HomeController {
  
  public function actionIndex() {
    $postsList = array();
    if (isset($_SESSION['login'])) {
      $login = $_SESSION['login'];
    } else {
      $login = 0;
    }
    $postsList = Post::getPostList($login, null);
    $avatar = User::getAvatars();
    require_once(ROOT.'/views/posts/index.php');
    return true;
  }
  
  public function actionExternal($home, $attr) {

    if (!in_array($attr, ['liking', 'commenting'])) { header("HTTP/1.0 404 Not Found"); return false ;}

    $postsList = array();
    if (isset($_SESSION['login'])) {
      $login = $_SESSION['login'];
    } else {
      $login = 0;
    }
    $postsList = Post::getPostList($login, $attr);
    $avatar = User::getAvatars();
    require_once(ROOT.'/views/posts/index.php');
    return true;
  }  

  public function action404() {
    header("HTTP/1.0 404 Not Found");
    return true;
  }
}
  
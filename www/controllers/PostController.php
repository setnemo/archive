<?php

include_once ROOT.'/models/Post.php';
include_once ROOT.'/models/User.php';
class PostController {
  
  public function actionIndex($user) {
    $postsList = array();
    $postsList = Post::getPostItemByUser($_SESSION['login'], $user);
    $avatar = User::getAvatars();
    if ($postsList) {
      require_once(ROOT.'/views/posts/index.php');
//     echo "<pre>";
//     print_r($postsList);
//     echo "</pre>";
    }
    else { 
      header("HTTP/1.0 404 Not Found");
    }
    return true;
  }

  public function actionExternal($user, $id) {
    $postsList = array();
    $postsList = Post::getPostItemById($_SESSION['login'], $user, $id);
    $avatar = User::getAvatars();
    if ($postsList) {
      require_once(ROOT.'/views/posts/index.php');
//     echo "<pre>";
//     print_r($postsList);
//     echo "</pre>";
    }
    else { header("HTTP/1.0 404 Not Found"); }
    return true;
  }

  public function action404() {
    header("HTTP/1.0 404 Not Found");
    return true;
  }
}
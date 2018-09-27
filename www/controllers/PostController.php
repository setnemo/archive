<?php

include_once ROOT.'/models/Post.php';
include_once ROOT.'/models/User.php';

class PostController {
  
  public function actionIndex($user) {
    $postsList = array();
    if (isset($_SESSION['login'])) {
      $login = $_SESSION['login'];
    } else {
      $login = null;
    }
    $postsList = Post::getPostItemByUser($login, $user);
    $avatar = User::getAvatars();
    if ($postsList) {
      $pagemode = $user;
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
    if (isset($_SESSION['login'])) {
      $login = $_SESSION['login'];
    } else {
      $login = null;
    }
    if ($user == 'create')
    {
      if ($id == 'add')
      {
        require_once(ROOT.'/views/posts/add.php');
      }
      if ($id == 'send')
      {
        Post::getNewpost();
      }
      if ($id == 'live')
      {
        require_once(ROOT.'/views/posts/add-live.php');
      }
      if ($id == 'live-add')
      {
        Post::getNewpostLive();
      }
      return true;
    }
    // echo "<pre>";
    // print_r([$user, $id]);
    // echo "</pre>";
    $postsList = Post::getPostItemById($login, $user, $id);
    $avatar = User::getAvatars();
    if ($postsList) {
      $pagemode = $user;
      $comments = Post::getComments($id);
      require_once(ROOT.'/views/posts/single.php');
    }
    else { header("HTTP/1.0 404 Not Found"); }
    return true;
  }

  public function action404() {
    header("HTTP/1.0 404 Not Found");
    return true;
  }
}
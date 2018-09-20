<?php

include_once ROOT.'/models/Post.php';

class HomeController {
  
  public function actionIndex() {
    $postsList = array();
    $postsList = Post::getPostList(1); // 1 = full, 0 = without likes
    require_once(ROOT.'/views/posts/index.php');
//     echo "<pre>";
//     print_r($postsList);
//     echo "</pre>";
    return true;
  }

  public function action404() {
    header("HTTP/1.0 404 Not Found");
    return true;
  }
}
  
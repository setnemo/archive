<?php

class Post {

  public static function getPostItemByUser($user) {
    
  $conn = Db::getConnection();
    
    $postList = array();
    $result = $conn->query("
    SELECT
      posts.id, 
      posts.path,
      posts.likes,
      posts.caption,
      posts.created_at,
      posts.user,
      users.login
    FROM
      posts
    INNER JOIN users ON posts.user = users.id
    WHERE users.login=\"".$user."\"
    ORDER BY posts.id DESC;
    ");
    $it = 0;
    while ($row = $result->fetch()) {
      $postList[$it]['id'] = $row['id'];
      $postList[$it]['path'] = $row['path'];
      $postList[$it]['likes'] = $row['likes'];
      $postList[$it]['caption'] = $row['caption'];
      $postList[$it]['created_at'] = $row['created_at'];
      $postList[$it]['login'] = $row['login'];
      $it++;
    }
    return $postList;
  }    
  public static function getPostItemById($user, $id) {
    
    $id = intval($id);
    $postList = array();
    
    if ($id) {
  $conn = Db::getConnection();
    
    $result = $conn->query("
    SELECT
      posts.id, 
      posts.path,
      posts.likes,
      posts.caption,
      posts.created_at,
      posts.user,
      users.login
    FROM
      posts
    INNER JOIN users ON posts.user = users.id
    WHERE users.login=\"".$user."\" and posts.id=\"".$id."\"
    ORDER BY posts.id DESC;
    ");
    $it = 0;
    while ($row = $result->fetch()) {
      $postList[$it]['id'] = $row['id'];
      $postList[$it]['path'] = $row['path'];
      $postList[$it]['likes'] = $row['likes'];
      $postList[$it]['caption'] = $row['caption'];
      $postList[$it]['created_at'] = $row['created_at'];
      $postList[$it]['login'] = $row['login'];
      $it++;
    }
    }
    return $postList;
  }
  
  public static function getPostList($flag) {
  $conn = Db::getConnection();
    
    $postList = array();
    if ($flag) {
    $sq = "
    SELECT
      posts.id, 
      posts.path,
      posts.likes,
      posts.caption,
      posts.created_at,
      posts.user,
      users.login
    FROM
      posts
    INNER JOIN users ON posts.user = users.id
    ORDER BY posts.id DESC;
    ";
    }
    else {
    $sq = "
    SELECT
      posts.id, 
      posts.path,
      posts.caption,
      posts.user,
      users.login
    FROM
      posts
    INNER JOIN users ON posts.user = users.id
    ORDER BY posts.id DESC;
    ";
    }
    $result = $conn->query($sq);
    $it = 0;
    while ($row = $result->fetch()) {
      $postList[$it]['id'] = $row['id'];
      $postList[$it]['path'] = $row['path'];
      $postList[$it]['likes'] = $row['likes'];
      $postList[$it]['caption'] = $row['caption'];
      $postList[$it]['created_at'] = $row['created_at'];
      $postList[$it]['login'] = $row['login'];
      $it++;
    }
    return $postList;
  }
}
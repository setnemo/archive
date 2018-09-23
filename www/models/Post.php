<?php

class Post {

  public static function getPostItemByUser($flag, $user) {
    
  $conn = Db::getConnection();
    
    $postList = array();
    $result = $conn->query("
    SELECT
      posts.id, 
      posts.path,
      posts.likes,
      posts.comment,
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
      $postList[$it]['caption'] = $row['caption'];
      $postList[$it]['login'] = $row['login'];
      if ($flag) 
      {
        $postList[$it]['created_at'] = $row['created_at'];
        $postList[$it]['likes'] = $row['likes'];
        $postList[$it]['comment'] = $row['comment'];
      }
      $it++;
    }
    return $postList;
  }   
   
  public static function getPostItemById($flag, $user, $id) {
    
    $id = intval($id);
    $postList = array();
    
    if ($id) {
  $conn = Db::getConnection();
    
    $result = $conn->query("
    SELECT
      posts.id, 
      posts.path,
      posts.likes,
      posts.comment,
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
      $postList[$it]['caption'] = $row['caption'];
      $postList[$it]['login'] = $row['login'];
      if ($flag) 
      {
        $postList[$it]['created_at'] = $row['created_at'];
        $postList[$it]['likes'] = $row['likes'];
        $postList[$it]['comment'] = $row['comment'];
      }
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
      posts.comment,
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
      $postList[$it]['caption'] = $row['caption'];
      $postList[$it]['login'] = $row['login'];
      if ($flag) 
      {
        $postList[$it]['created_at'] = $row['created_at'];
        $postList[$it]['likes'] = $row['likes'];
        $postList[$it]['comment'] = $row['comment'];
      }
      $it++;
    }
    return $postList;
  }

  public static function getAddLike($post, $user) {

    $conn = Db::getConnection();
    $result = $conn->prepare("
      SELECT
        id
      FROM
        likes
      WHERE user = ?;
      ");
    $result->execute([$user]);
    $fetch = $result->fetch();

    if ($fetch)
    {
      $insert = $conn->prepare("UPDATE posts SET likes = likes - 1 WHERE id=?;");
      $insert->execute([$post]);
      $insert = $conn->prepare("DELETE FROM likes WHERE user=? AND post=?;");
      $insert->execute([$user, $post]);
    }
    else 
    {
      $insert = $conn->prepare("UPDATE posts SET likes = likes + 1 WHERE id=?;");
      $insert->execute([$post]);
      $sql = "INSERT INTO likes (user, post) VALUES (?, ?) ;";
      $conn->prepare($sql)->execute([$user, $post]);
    }
    $sql = "
      SELECT
        likes
      FROM
        posts
      WHERE id = ?;
      ";
      $result = $conn->prepare($sql);
      $result->execute([$post]);
      $fetch = $result->fetchAll(PDO::FETCH_ASSOC);
      echo $fetch[0]['likes'];
  }
}
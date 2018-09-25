<?php

include_once ROOT.'/models/Email.php';
include_once ROOT.'/models/User.php';

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
    ORDER BY posts.id DESC LIMIT 0, 8;
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
    if (count($postList))
      return $postList;
    else
      $postList = array('');
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
    ORDER BY posts.id DESC ;
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
    
  public static function getPostList($flag, $sort) {
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
    ";
    }
    else {
    $sq = "
    SELECT
      posts.id, 
      posts.path,
      posts.likes,
      posts.comment,
      posts.caption,
      posts.user,
      users.login
    FROM
      posts
    INNER JOIN users ON posts.user = users.id
    ";
    }
    if ($sort) {
      if ($sort == 'liking') {
        $sq .= 'ORDER BY posts.likes DESC, posts.comment DESC LIMIT 0, 8;';
      } else {
        $sq .= 'ORDER BY posts.comment DESC, posts.likes DESC LIMIT 0, 8;';
      }
    } else {
      $sq .= 'ORDER BY posts.id DESC LIMIT 0, 8;';
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

  public static function getAddLike($post, $user, $fix) {
    if (!isset($_SESSION['login'])) { return false; }
    $conn = Db::getConnection();
    $result = $conn->prepare("
      SELECT
        id
      FROM
        likes
      WHERE user = ? AND post = ?;
      ");
    $result->execute([$user, $post]);
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
      return ;
  }

  public static function getAddComment($comment, $user, $post) {
    if (!isset($_SESSION['login'])) { return false; }
    $conn = Db::getConnection();
    $sql = "INSERT INTO `comments` (`id`, `user`, `post`, `body`, `created_at`) VALUES (NULL, ?, ?, ?, CURRENT_TIMESTAMP);";
    $result = $conn->prepare($sql);
    $result->execute([$user, $post, $comment]); 
    $result = $conn->prepare("SELECT * FROM comments WHERE user = ? ORDER BY created_at DESC LIMIT 0,1;");
    $result->execute([$user]);
    $fetch1 = $result->fetch(PDO::FETCH_ASSOC);
    $result = $conn->prepare("SELECT * FROM users WHERE login = ? ;");
    $result->execute([$user]);
    $fetch2 = $result->fetch(PDO::FETCH_ASSOC);
    $insert = $conn->prepare("UPDATE posts SET comment = comment + 1 WHERE id=?;");
    $insert->execute([$post]);
    // need login post created! and email template
    $result = $conn->prepare("SELECT * FROM posts WHERE id = ?;");
    $result->execute([$post]);
    $fetch = $result->fetch(PDO::FETCH_ASSOC);
    $result = $conn->prepare("SELECT * FROM users WHERE id = ?;");
    $result->execute([$fetch['user']]);
    $fetch = $result->fetch(PDO::FETCH_ASSOC);
    // echo "<pre>";
    // print_r($fetch);
    // echo "</pre>";
    if ($fetch['action'] == "1") {
      $emailObj = new Email;
      $letter = Email::commentNotification($fetch, $post);
    }
    $printdata = array();
    $printdata['avatar'] = hash('md5', $fetch2['email']);
    $printdata['text'] = $fetch1['body'];
    $printdata['login'] = $user;
    $printdata['date'] = $fetch1['created_at'];
    require_once(ROOT.'/views/posts/comment.php');
    return ;
  }


  public static function getComments($id) {
  $conn = Db::getConnection();
    $sql = "
    SELECT
      *
    FROM
      comments
    WHERE post = ?
    ORDER BY created_at DESC;
    ";
    $result = $conn->prepare($sql);
    $result->execute([$id]);
    $fetch = $result->fetchAll(PDO::FETCH_ASSOC);
    return $fetch;
  }

  public static function getInfinity($iter, $what, $sort) {
  $conn = Db::getConnection();
  $it2 = $iter + 7;
  $iter--;
    $sql =  "SELECT
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
    INNER JOIN users ON posts.user = users.id ORDER BY posts.id LIMIT ".intval($iter).", ".intval($it2).";";
    $result = $conn->prepare($sql);
    $result->execute();
    $postsList = array();

    $it = 0;
    while ($row = $result->fetch()) {
      $postsList[$it]['id'] = $row['id'];
      $postsList[$it]['path'] = $row['path'];
      $postsList[$it]['caption'] = $row['caption'];
      $postsList[$it]['login'] = $row['login'];
        $postsList[$it]['created_at'] = $row['created_at'];
        $postsList[$it]['likes'] = $row['likes'];
        $postsList[$it]['comment'] = $row['comment'];
      $it++;
    }
        $avatar = User::getAvatars();
      // echo "<pre>";
      // print_r($postsList);
      // echo "</pre>";
    require_once(ROOT.'/views/posts/infinity.php');
    return ;
  }
}
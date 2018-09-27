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

  public static function getInfinity($iter, $sort) {
  $conn = Db::getConnection();
  $iter = intval($iter);
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
    INNER JOIN users ON posts.user = users.id ";
    if ($sort) {
      if ($sort == 'liking') {
        $sql .= 'ORDER BY posts.likes DESC, posts.comment DESC LIMIT 4 OFFSET ?;';
      } else if ($sort == 'commenting') {
        $sql .= 'ORDER BY posts.comment DESC, posts.likes DESC LIMIT 4 OFFSET ?;';
      } else {
        $sql .= 'WHERE users.login = ? ORDER BY posts.id DESC LIMIT 4 OFFSET ?;';
      }
    } else {
      $sql .= 'ORDER BY posts.id DESC LIMIT 4 OFFSET ?;';
    }
    $result = $conn->prepare($sql);
    if ($sort != 'liking' && $sort != 'commenting' && $sort != '' ) {
      $result->bindValue(1, $sort, PDO::PARAM_STR);
      $result->bindValue(2, $iter, PDO::PARAM_INT);
    } else {
      $result->bindValue(1, $iter, PDO::PARAM_INT);
    }
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
      // echo "<div><pre>";
      // print_r([count($postsList), $sql, $iter]);
      // echo "</pre><hr></div>";
    require_once(ROOT.'/views/posts/infinity.php');
    return ;
  }


  public static function getNewpost() {
    if (isset($_POST['submit'])) {
//        $image = $_FILES['photo']['name'];
        $iname = rand(0,99999);
        while (file_exists(ROOT."/img/posts/" . $iname)) {
            $iname = rand(0,9999999);
        }
        $target = ROOT."/img/posts/" . $iname. ".jpg";
        $user = $_SESSION["login"];

        if (move_uploaded_file($_FILES['photo']['tmp_name'], $target)) {
            header("Location: /");
        } else {
            echo "Failed to upload image";
        }
    }
    return true;
    }

  public static function getNewpostLive() {
      if (isset($_POST['submit'])) {
          $data = $_POST['photo'];
          $arr = explode(',', $data);
          $s1 = base64_decode($arr[1]);
          if ($_POST['gender'] === "male") {$over_name = "fr2.png";}
          else if ($_POST['gender'] === "female") {$over_name = "fr1.png";}
          else if ($_POST['gender'] === "other") {$over_name = "fr3.png";}
          else {$over_name = "empty.png";}
          $overlay = imagecreatefrompng(ROOT.'/img/overlays/' . $over_name);
          $rand = rand(0, 99999);
          while (file_exists(ROOT."/img/posts/" . $rand . ".png")) {$rand = rand(0, 99999);}
          $fd = fopen(ROOT."/img/posts/" . $rand . ".png", 'w+') or die("Unable to open file!");
          fwrite($fd, $s1);
          fclose($fd);
          $im = imagecreatefrompng(ROOT."/img/posts/". $rand . ".png");
          $sx = imagesx($overlay);
          $sy = imagesy($overlay);
          $mright = 0;
          $mbottom = 0;
          imagecopy($im, $overlay, imagesx($im) - $sx - $mright, imagesy($im) - $sy - $mbottom, 0, 0, imagesx($overlay), imagesy($overlay));
          header('Content-type: image/png');
          imagepng($im, ROOT."/img/posts/" . $rand . ".png");
          imagedestroy($im);
          $image = $rand . '.png';
          if (file_exists(ROOT."/img/posts/" . $image)) {
              header("Location: /");
          } else {
              echo "Ooops, something's gone wrong... <a href='/'> Press to return to the homepage</a>";
      }
    }
    return true;
    }
}
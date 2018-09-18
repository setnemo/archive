    <main role="main" class="container">
        <!-- <h1 class="mt-5">Sticky footer with fixed navbar</h1> -->
        <!-- <pre><?php print_r($_SESSION) ?></pre> -->
        <div class="row mt-5">
            <?php foreach ($postsList as $post): ?>
            <div class="col-lg-3 col-md-6 col-sm-9 col-xs-9">
                <div class="card profile-card-2">
                    <div class="card-img-block">
                        <a href="/post/<?php echo $post['login']."/".$post['id'] ?>"><img class="img-fluid" src="/img/posts/<?php echo $post['path']; ?>" alt="<?php echo $post['caption']; ?>"></a>
                    </div>
                    <div class="card-body pt-5">
                        <a href="/post/<?php echo $post['login']; ?>"><img src="/img/profile/<?php echo $post['login']; ?>.jpg" alt="profile-image" class="profile"/></a>
                        <div class="icon-block"><a href="http://twitter.com/share?text=<?php echo "Post by ".$post['login']." at http://". $_SERVER['HTTP_HOST']."/".$post['login']."/".$post['id'] ?>&url=<?php echo $_SERVER['HTTP_HOST']."/".$post['login']."/".$post['id'] ?>" title="Поделиться ссылкой в Твиттере" onclick="window.open(this.href, this.title, 'toolbar=0, status=0, width=548, height=325'); return false" target="_parent""> <i class="fa fa-twitter share1"></i></a><a href="https://plus.google.com/share?url=http://<?php echo $_SERVER['HTTP_HOST']."/".$post['login']."/".$post['id'] ?>" onclick="javascript:window.open(this.href,
  '', 'menubar=no,toolbar=no,resizable=yes,scrollbars=yes,height=600,width=600');return false;"> <i class="fa fa-google-plus share2"></i></a></div>
                        <p class="card-text"><?php echo $post['caption'] ?></p>
                    </div>
                </div>
                <p class="mt-3 w-100 float-left text-center"></p>
            </div>
            <?php endforeach; ?>
    <?php

$subject = 'the subject';
$headers = "From: test@camagru.com" . "\r\n";
$headers .= "Reply-To: test@camagru.com".  "\r\n";
$headers .= "MIME-Version: 1.0\r\n";
$headers .= "Content-Type: text/html; charset=UTF-8\r\n";

$message = '<html><body style="width: 100%;">';
$message .= '<div style="padding: 0px;position: relative;margin-top: 30px;margin-left: auto;margin-right: auto;background-color: #fff;border-top: 1px;border-bottom: 1px;border-left: 1px;border-right: 1px;border-radius: 10px;border-style: solid;border-color: #aaa;width: 300px;height: 330px;text-align: center;box-shadow: 1px 11px 95px #aaa;">';
$message .= '<p style="color: #03519b;font-family: "PT Sans", sans-serif;font-size: 25px;font-weight: bold;line-height: 35px;text-align: center;">';
$message .= '<br><br><br>Вхід на сайт за посиланням<br>';
$message .= '</p></a>';
$message .= '</div>';
$message .= '</body></html>';
$to = "setnemo@gmail.com";

$tmp = mail($to, $subject, $message, $headers);


echo "<pre>";
echo $tmp;
echo "</pre>";
?>            </div>
</main>

<?php if ($postsList) { ?>
<?php foreach ($postsList as $post): ?>
<?php if ($post) { ?>
<div class="col-lg-3 col-md-6 col-sm-9 col-xs-9">
    <div class="card profile-card-2">
        <div class="card-img-block">
            <a href="/post/<?php echo $post['login']."/".$post['id'] ?>"><img class="img-fluid" src="/img/posts/<?php echo $post['path']; ?>" alt="<?php echo $post['caption']; ?>"></a>
        </div>
        <div class="card-body pt-5">
            <a href="/post/<?php echo $post['login']; ?>"><img src="//www.gravatar.com/avatar/<?php echo $avatar[$post['login']]; ?>.jpg" alt="profile-image" class="profile"/></a>
            <div class="icon-block"><a href="http://twitter.com/share?text=<?php echo "Post by ".$post['login']." at http://". $_SERVER['HTTP_HOST']."/".$post['login']."/".$post['id'] ?>&url=<?php echo $_SERVER['HTTP_HOST']."/".$post['login']."/".$post['id'] ?>" title="Поделиться ссылкой в Твиттере" onclick="window.open(this.href, this.title, 'toolbar=0, status=0, width=548, height=325'); return false" target="_parent""> <i class="fa fa-twitter share1"></i></a><a href="https://plus.google.com/share?text=http://<?php echo $_SERVER['HTTP_HOST']."/".$post['login']."/".$post['id'] ?>" onclick="javascript:window.open(this.href,'', 'menubar=no,toolbar=no,resizable=yes,scrollbars=yes,height=600,width=600');return false;"> <i class="fa fa-google-plus share2"></i></a>
                <?php if (isset($_SESSION['login'])) { ?><i class="fa fa-heart likes" name="<?php echo $post['id']; ?>" ></i><span class="likes-count"><?php echo $post['likes'];} ?></span>
                <?php if (isset($_SESSION['login'])) { ?><i class="fa fa-comment comment" name="<?php echo $post['id']; ?>" ></i><span class="comment-count"><?php echo $post['comment'];} ?></span>
            </div>
            <p class="card-text"><?php echo $post['caption'] ?></p>
        </div>
    </div>
    <p class="mt-3 w-100 float-left text-center"></p>
</div>
<?php }
endforeach;
} else { echo "null"; }
?>
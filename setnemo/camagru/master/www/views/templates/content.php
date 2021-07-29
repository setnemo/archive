    <main role="main" class="container">
        <!-- <h1 class="mt-5">Sticky footer with fixed navbar</h1> -->
        <!-- <pre><?php print_r($postsList) ?></pre> -->
        <div class="row mt-5">
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
                            <?php if (isset($post['likes'])) { ?><i class="fa fa-heart likes" name="<?php echo $post['id']; ?>" ></i><span class="likes-count"><?php echo $post['likes'];} ?></span>
                            <?php if (isset($post['comment'])) { ?><i class="fa fa-comment comment" name="<?php echo $post['id']; ?>" ></i><span class="comment-count"><?php echo $post['comment'];} ?></span>
                        </div>
                        <p class="card-text"><?php echo $post['caption'] ?></p>
                    </div>
                </div>
                <p class="mt-3 w-100 float-left text-center"></p>
            </div>
            <?php }
            endforeach; ?>
</div>
<div id="pagemode" name="<?php echo $pagemode; ?>"></div>
<div id="infcontainer">
</div>

</main>
<script>

//infinity scroll
var distToBottom, data;
var page = 7;
var pollingForData = false;
var infinity = new XMLHttpRequest();
var newInfo = document.querySelector("#infcontainer");

function getDistFromBottom () {
  
  var scrollPosition = window.pageYOffset;
  var windowSize     = window.innerHeight;
  var bodyHeight     = document.body.offsetHeight;

  return Math.max(bodyHeight - (scrollPosition + windowSize), 0);

}
function insertBefore(referenceNode, newNode) {
    referenceNode.parentNode.insertBefore(newNode, referenceNode);
}

infinity.onload = function() {
  if(infinity.status === 200) {

    pollingForData = false;
    data = infinity.responseText

    if (this.readyState == 4) {
        if (this.status == 200 && infinity.responseText != "null" ) {
            let div = window.top.document.createElement('div');
            div.className = "row mt-5";
            div.innerHTML = this.responseText;
            insertBefore(newInfo, div);

            const   newlike = new XMLHttpRequest();
            var     likes = [...document.querySelectorAll(".likes")];
            var     likesCount = [...document.querySelectorAll(".likes-count")];
            var     tempindex;

            function likeIt(post, index) {
                post.onclick = function() {
                    var     data = new FormData();
                    tempindex = index;
                    data.append("post", post.getAttribute('name'));
                    newlike.open("POST", '/action/like/add/');
                    newlike.send(data);
                }
                
            }

            if (likes)
            {
                newlike.onreadystatechange = function() {
                    likesCount[tempindex].innerHTML = this.responseText;
                };
                likes.forEach(likeIt);
            }
        }
    }
  }
};
var info = new FormData;
var pagemode = document.querySelector("#pagemode");
info.append("sort", pagemode.getAttribute('name'));
infinity.open('POST', '/action/infinity/8', true);
infinity.send(info);
pollingForData = true;

document.addEventListener('scroll', function() {
        distToBottom = getDistFromBottom();
        // console.log('scrolling', getDistFromBottom());

        if (!pollingForData && distToBottom > 0 && distToBottom <= 2000) {
          pollingForData = true;
          page += 4;
          info.append("sort", pagemode.getAttribute('name'));
          infinity.open('POST', '/action/infinity/'+page, true);
          infinity.send(info);

        }
});

</script>
<?php

?>            

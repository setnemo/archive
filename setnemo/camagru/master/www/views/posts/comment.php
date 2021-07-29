<div class="photo">
        <div class="avatar" style="background-image: url('//www.gravatar.com/avatar/<?php echo $printdata['avatar']; ?>')"></div>
</div>
<div class="comment-block">
        <p class="comment-text"><?php echo htmlspecialchars($printdata['text']); ?></p>
        <div class="bottom-comment">
                <ul class="comment-actions">
                        <li class="complain"><a href="/post/<?php echo $printdata['login']; ?>/"><?php echo $printdata['login']; ?></a></li>
                        <li class="reply"><?php echo $printdata['date']; ?></li>
                </ul>
        </div>
</div>

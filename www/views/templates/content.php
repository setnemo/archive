    <div id="content">
      <?php foreach ($postsList as $post): ?>
      <figure class="imgteaser">
        <img width='500px' src="<?php echo $post['path']?>">
      <figcaption><strong>ЗАГОЛОВОК</strong>прозрачная область</figcaption>
      </figure>
      <?php endforeach; ?>
    </div>
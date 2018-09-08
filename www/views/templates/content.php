    <main role="main" class="container">
        <h1 class="mt-5">Sticky footer with fixed navbar</h1>
        <div class="row">
            <?php foreach ($postsList as $post): ?>
<div class="col-lg-3 col-md-6 col-sm-12 col-xs-12">
                <div class="card profile-card-2">
                    <div class="card-img-block">
                        <img class="img-fluid" src="<?php echo $post['path']?>" alt="Card image cap">
                    </div>
                    <div class="card-body pt-5">
                        <img src="https://randomuser.me/api/portraits/men/64.jpg" alt="profile-image" class="profile"/>
                        <p class="card-text">Some quick example text to build on the card title and make up the bulk of the card's content.</p>
                        <div class="icon-block"><a href="#"><i class="fa fa-facebook"></i></a><a href="#"> <i class="fa fa-twitter"></i></a><a href="#"> <i class="fa fa-google-plus"></i></a></div>
                    </div>
                </div>
                <p class="mt-3 w-100 float-left text-center"></p>
            </div>
            <?php endforeach; ?>
        </div>
    </main>
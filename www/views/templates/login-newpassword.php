    <main role="main" class="container">
        <div class="row mt-5">
        <div class="loginmodal-container">
<?php if ($status) { ?>
              <h3>New password generated</h3><br>
              <p>Please check your email address!</p>
<?php } else { ?>
              <h3>Error! </h3><br>
              <p>New password does not been generated</p>
              <p>Please check your input data!</p>
              </div>
<?php } ?>
          </div>
        </div>
    </main>
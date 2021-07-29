    <main role="main" class="container">
        <div class="row mt-5">
        <div class="loginmodal-container">
<?php if ($status) { ?>
              <h3>Email confirmed</h3><br>
              <p>Please login to CAMAGRU via login form (menu in head of page)</p>
<?php } else { ?>
              <h3>Fail email confirmed!</h3><br>
              <p>Please check your confirmed link!</p>
              </div>
<?php } ?>
          </div>
        </div>
    </main>
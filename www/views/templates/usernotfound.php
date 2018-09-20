    <main role="main" class="container">
        <!-- <h1 class="mt-5">Sticky footer with fixed navbar</h1> -->
        <!-- <pre><?php print_r($_SESSION) ?></pre> -->
        <div class="row mt-5">
        <div class="loginmodal-container">
            <h5>Error! No such user or bad password!</h5>
              <br><h3>Login to Your Account</h3><br>
              <form action="/login/" method="POST">
                <input type="text" name="login" placeholder="Username">
                <input type="password" name="pass" placeholder="Password">
                <input type="submit" class="login loginmodal-submit" value="Login">
              </form>
                  
              <div class="login-help">
              <a href="#">Register</a> - <a href="#">Forgot Password</a>
              </div>
          </div>
        </div>
    </main>

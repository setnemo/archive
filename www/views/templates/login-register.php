    <main role="main" class="container">
        <div class="row mt-5">
        <div class="loginmodal-container">
              <h3>Registration</h3><br>
              <form action="/login/add/" method="POST">
                <input type="text" name="login" placeholder="Username">
                <input type="password" name="pass" placeholder="Password">
                <input type="email" name="email" placeholder="email">
                <input type="text" name="firstname" placeholder="firstname">
                <input type="text" name="lastname" placeholder="lastname">
                <input type="submit" class="login loginmodal-submit" value="SIGN UP">
              </form>
                  
              <div class="login-help">
              <a href="/login/recovery/">Forgot Password</a>
              </div>
          </div>
        </div>
    </main>

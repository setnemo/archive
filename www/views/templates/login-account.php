    <main role="main" class="container">
        <div class="row mt-5">
        <div class="loginmodal-container">
              <h3>Change account information</h3><br>
              <form action="/login/edit/" method="POST">
                <p>Current login: <b><?php echo $account_data['login'];?></b></p>
                <p>Current email: <b><?php echo $account_data['email'];?></b></p>
                <p>Current first name: <b><?php echo $account_data['firstname'];?></b></p>
                <p>Current last name: <b><?php echo $account_data['lastname'];?></b></p>
                <p>Change gravatar at <a href="https://en.gravatar.com/site/login" target="_blank">gravatar.com</a></p>
                <input type="text" name="login" placeholder="new login">
                <input type="password" name="password" placeholder="old password">
                <input type="password" name="passn1" placeholder="new password">
                <input type="password" name="passn2" placeholder="new password (repeat)">
                <input type="email" name="email" placeholder="new email">
                <input type="text" name="firstname" placeholder="new firstname">
                <input type="text" name="lastname" placeholder="new lastname">
                <input type="submit" class="login loginmodal-submit" value="CHANGE">
              </form>
              <div class="login-help">
              <a href="/login/recovery/">Forgot Password</a>
              </div>
          </div>
        </div>
    </main>

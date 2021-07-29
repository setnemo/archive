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
                <input type="text" id="username" onchange="return validateForm();"  name="login" placeholder="new login">
                <input type="password" name="password" placeholder="old password">
                <input type="password"  id="password1" onchange="return validateForm();" name="passn1" placeholder="new password">
                <input type="password"  id="password2" onchange="return validateForm();" name="passn2" placeholder="new password (repeat)">
                <input type="email" name="email" placeholder="new email">
                <input type="text" name="firstname" placeholder="new firstname">
                <input type="text" name="lastname" placeholder="new lastname">
                <label>Receive notifications <input type="checkbox" name="action"<?php if ($account_data['action'] == 1) echo " checked";?>></label>
                <input type="submit" class="login loginmodal-submit"  id="signup" value="CHANGE">
              </form>
              <div class="login-help">
              <a href="/login/recovery/">Forgot Password</a>
              </div>
          </div>
        </div>
    </main>
<script>
var textBoxUser = document.getElementById("username");
var textBoxPass1 = document.getElementById("password1");
var textBoxPass2 = document.getElementById("password2");
function validateForm() {
    if (textBoxUser.textLength <= 2 || textBoxUser.textLength > 20) {
        alert("Username length need 3-20 symbols!");
        document.getElementById("signup").disabled = true;
        return false;
    }
    if (textBoxPass1.textLength <= 5 || textBoxPass1.textLength > 20) {
        alert("Password1 length need 6-20 symbols!");
        document.getElementById("signup").disabled = true;
        return false;
    }
    if (textBoxPass2.textLength <= 5 || textBoxPass2.textLength > 20) {
        alert("Password2 length need 6-20 symbols!");
        document.getElementById("signup").disabled = true;
        return false;
    }
    if (textBoxUser.value.match(/\W/)) {
        alert('You have special characters on username field.');
        document.getElementById("signup").disabled = true;
        return false;
    }
    document.getElementById("signup").disabled = false;
    return true;
}
</script>
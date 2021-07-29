    <main role="main" class="container">
        <div class="row mt-5">
        <div class="loginmodal-container">
              <h3>Registration</h3><br>
              <form action="/login/add/" method="POST">
                <input type="text" id="username" name="login" placeholder="Username" onchange="return validateForm();" required>
                <input type="password" id="password" name="pass" placeholder="Password" onchange="return validateForm();" required>
                <input type="email" name="email" placeholder="email" required>
                <input type="text" name="firstname" placeholder="firstname">
                <input type="text" name="lastname" placeholder="lastname">
                <input type="submit" class="login loginmodal-submit" id="signup" value="SIGN UP">
              </form>
                  
              <div class="login-help">
              <a href="/login/recovery/">Forgot Password</a>
              </div>
          </div>
        </div>
    </main>
<script>
var textBoxUser = document.getElementById("username");
var textBoxPass = document.getElementById("password");
function validateForm() {
    if (textBoxUser.textLength <= 2 || textBoxUser.textLength > 20) {
        alert("Username length need 3-20 symbols!");
        document.getElementById("signup").disabled = true;
        return false;
    }
    if (textBoxPass.textLength <= 5 || textBoxPass.textLength > 20) {
        alert("Password length need 6-20 symbols!");
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
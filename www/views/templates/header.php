    <header>
        <nav class="topnav" id="myTopnav">
          <a href="/" class="active">Home</a>
          <a href="/">Most popular</a>
          <a href="/">Most comment</a>
          <?php if (isset($_SESSION['auth']) && $_SESSION['auth'] == session_id()) { ?><a href="#" id="myBtn">Account</a><?php } else { ?><a href="#" id="myBtn">Login</a><?php } ?>
          <a href="javascript:void(0);" class="icon" onclick="myFunction()">
            <i class="fa fa-bars"></i>
          </a>
        </nav>
        <script>
        function myFunction() {
            var x = document.getElementById("myTopnav");
            if (x.className === "topnav") {
                x.className += " responsive";
            } else {
                x.className = "topnav";
            }
        }
        </script>

    </header>
<div class="modalc" id="myModal">
    <div class="loginmodal-container">
        <span id="closed">&times;</span>
        <h1>Login to Your Account</h1><br>
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
<script>
var modal = document.getElementById('myModal');
var btn = document.getElementById("myBtn");
var span = document.getElementById("closed");
btn.onclick = function() {
    modal.style.display = "block";
}
span.onclick = function() {
    modal.style.display = "none";
}

</script>
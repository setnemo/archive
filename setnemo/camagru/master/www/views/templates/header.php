    <header>
        <nav class="topnav" id="myTopnav">
          <a href="/" class="active">Home</a>
          <a href="/home/liking/">Most popular</a>
          <a href="/home/commenting/">Most comment</a>
          <?php if ($_SERVER['REQUEST_URI'] != '/login/') { if (isset($_SESSION['auth']) && $_SESSION['auth'] == session_id()) { ?><a href="/login/account/" class="myBtn">Account</a><?php } else { ?><a href="#" id="myBtn">Login</a><?php } }?>
          <?php if (isset($_SESSION['auth']) && $_SESSION['auth'] == session_id()) { ?><a href="/post/create/live/"><i class="fa fa-plus"></i></a><a href="/login/logout/" class="myBtn">Logout</a><?php } ?>
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
<?php //fix console error login modal ?>
<?php if (!isset($_SESSION['auth'])) { ?>
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
      <a href="/login/register/">Register</a> - <a href="/login/recovery/">Forgot Password</a>
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
<?php } ?>
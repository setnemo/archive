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
<div class="modal" id="myModal">
  <div class="modal-dialog">
    <div class="loginmodal-container">
        <span class="closed">&times;</span>
        <h1>Login to Your Account</h1><br>
      <form>
        <input type="text" name="user" placeholder="Username">
        <input type="password" name="pass" placeholder="Password">
        <input type="submit" name="login" class="login loginmodal-submit" value="Login">
      </form>
          
      <div class="login-help">
      <a href="#">Register</a> - <a href="#">Forgot Password</a>
      </div>
    </div>
  </div>
</div>
<!--   <div class="modal" id="myModal">
    <div class="modal-dialog">
      <div class="modal-content">
        <div class="modal-header">
          <h5 class="modal-title">Modal Heading</h5>
          <button type="button" class="close closed2">&times;</button>
        </div>
        <div class="modal-body">
          Modal body..
        </div>
        <div class="modal-footer">
          <button type="button" class="btn btn-secondary">Close</button>
        </div>
        
      </div>
    </div>
  </div> -->
<script>
var modal = document.getElementById('myModal');
var btn = document.getElementById("myBtn");
var span = document.getElementsByClassName("closed")[0];
btn.onclick = function() {
    modal.style.display = "block";
}
span.onclick = function() {
    modal.style.display = "none";
}
window.onclick = function(event) {
    if (event.target == modal) {
        modal.style.display = "none";
    }
}
</script>
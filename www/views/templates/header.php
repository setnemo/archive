    <header>
        <nav class="topnav" id="myTopnav">
          <a href="/" class="active">Home</a>
          <a href="/">Most popular</a>
          <a href="/">Most comment</a>
          <a href="#" id="myBtn">Login</a>
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
<div id="myModal" class="modal">

  <!-- Modal content -->
  <div class="modal-content">
    <span class="closed">&times;</span>
    <p>Some text in the Modal..</p>
  </div>

</div>
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
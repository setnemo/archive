<html>
	<head>
		<title>ft_minishop</title>
		<meta name="viewport" content="width=device-width, initial-scale=1">
		<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
		<style>

			.drop {
				width: 98%;
				display: block;
				margin: 0 auto;
			}
			.drop_menu {
				background:#565454;
				padding:0;
				margin:0;
				list-style-type:none;
				height:30px;
			}
			.drop_menu li {
				float:left;
			}
			.drop_menu li a {
				padding:9px 20px;
				display:block;
				color:#fff;
				text-decoration:none;
				font:12px arial, verdana, sans-serif;
			}
			.drop_menu ul {
				position:absolute;
				left:-9999px;
				top:-9999px;
				list-style-type:none;
			}
			.drop_menu li:hover {
				position:relative;
				background:#fbba00;
				cursor: pointer;
			}
			.drop_menu li:hover ul {
				left:0px;
				top:30px;
				background:#fbba00;
				padding:0px;
				cursor: pointer;
			}

			.drop_menu li:hover ul li a {
				padding:5px;
				display:block;
				width:168px;
				text-indent:15px;
				background-color:#fbba00;
				cursor: pointer;
			}
			.drop_menu li:hover ul li a:hover {
				background:#fbba00;
				cursor: pointer;
			}


			body {
				background: #fbba00;
			}
			.container h1 {
				padding: 17px 17px 0px 27px ;
				font-size: 24px;
			}
			h2 {
				color: #565454;
			}
			h3 {
				color: #565454;
			}
			hr {
				max-width: 98%;
				clear: right;
			}
			.login-b button {
				background-color: #565454;
				color: white;
				float: right;
				padding: 14px 20px;
				margin: 8px 0;
				border: none;
				cursor: pointer;
				right: 20px;
				top: 3px;
				position: absolute;
			}
			.login-b .adm {
				background-color: #565454;
				color: white;
				float: right;
				padding: 14px 20px;
				margin: 8px 0;
				border: none;
				cursor: pointer;
				right: 100px;
				top: 3px;
				position: absolute;
			}
			.modal {
				display: none; /* Hidden by default */
				position: fixed; /* Stay in place */
				z-index: 1; /* Sit on top */
				left: 0;
				top: 0;
				width: 100%; /* Full width */
				height: 100%; /* Full height */
				overflow: auto; /* Enable scroll if needed */
				background-color: rgb(0,0,0); /* Fallback color */
				background-color: rgba(0,0,0,0.4); /* Black w/ opacity */
				padding-top: 60px;
			}
			.container {
				width: 90%;
				min-height: 90%;
				max-width: 90%;
				max-height: 90%;
				margin: auto;
				font-family: "Roboto", sans-serif;]
				box-shadow: 0 0 20px 0 rgba(0, 0, 0, 0.2), 0 5px 5px 0 rgba(0, 0, 0, 0.24);
				position: relative;
				z-index: 1;
				background: #FFFFFF;
				border-radius: 10px;
			}
			.login-page {
				width: 360px;
				padding: 8% 0 0;
				margin: auto;
				font-family: "Roboto", sans-serif;
			}
			.form {
				position: relative;
				z-index: 2;
				background: #FFFFFF;
				max-width: 360px;
				margin: 0 auto 100px;
				padding: 45px;
				text-align: center;
				box-shadow: 0 0 20px 0 rgba(0, 0, 0, 0.2), 0 5px 5px 0 rgba(0, 0, 0, 0.24);
			}
			.form input {
				font-family: "Roboto", sans-serif;
				outline: 0;
				background: #f2f2f2;
				width: 100%;
				border: 0;
				margin: 0 0 15px;
				padding: 15px;
				box-sizing: border-box;
				font-size: 14px;
			}
			.form .submit {
				font-family: "Roboto", sans-serif;
				text-transform: uppercase;
				outline: 0;
				background: #565454;
				width: 100%;
				border: 0;
				padding: 15px;
				color: #FFFFFF;
				font-size: 14px;
				-webkit-transition: all 0.3 ease;
				transition: all 0.3 ease;
				cursor: pointer;
			}
			.login-b button:hover, .form .submit:hover,.form .submit:active,.form .submit:focus {
				background: #fbba00;
			}
			.form .message {
				margin: 15px 0 0;
				color: #565454;
				font-size: 14px;
			}
			.form .message a {
				color: #fbba00;
				text-decoration: none;
			}
			.close {
				position: absolute;
				right: 25px;
				top: 0;
				color: #000;
				font-size: 35px;
				font-weight: bold;
			}
			.close:hover {
				cursor: pointer;
				color: #fbba00;
			}
			.form .message a:hover {
				cursor: pointer;
			}
		</style>
	</head>
	<body>
		<div class="container">
		<?php
			function admcheck($login) {
				$arr = unserialize(file_get_contents("../private/passwd"));
				foreach ($arr as $key => $inarr) {
					if ($inarr['login'] === $login && $inarr['admin'] === 1) {
						return (true);
					}
				}
				return (false);
			}
			session_start();
			if (admcheck($_SESSION['authorized_user'])) {
		?>
			<h1>Project Shop Admin Panel</h1>
				<div class="login-b">
					<button class="adm" onclick="window.location.href='index.php'">Shop</button>
					<?php
					if ($_SESSION['authorized_user'] === 'admin') {
					?>
					<button class="adm" onclick="window.location.href='admin.php'">ADM</button>
					<?php
					}
					if ($_SESSION['authorized_user']) {
					?>
					<button onclick="window.location.href='logout.php'" style="width:auto;">Logout</button>
					<?php
					} else {
					?>
					<button onclick="document.getElementById('login-modal-form').style.display='block'" style="width:auto;">Login</button>
					<?php 
					}
					?>
					<div id="login-modal-form" class="modal">
						<div id="loginform" class="login-page">
							<form class="form" action="login.php" method="POST">
							<div class="imgcontainer">
							  <span onclick="document.getElementById('login-modal-form').style.display='none'" class="close" title="Close Modal">&times;</span>
							</div>
								<h2>Sign in</h2>
								<input type="text" placeholder="login" name="login" value="" />
								<input type="password" placeholder="password" name="passwd" value="" />
								<input class="submit" type="submit" name="submit" value="OK" />
								<p class="message">Are you not registered? <a onclick="opentab('createform')">Create account</a></p>
							</form>
						</div>
						<div id="createform" class="login-page" style="display:none">
							<form class="form" action="create.php" method="POST">
							<div class="imgcontainer">
							  <span onclick="document.getElementById('login-modal-form').style.display='none'" class="close" title="Close Modal">&times;</span>
							</div>
								<h2>Create account</h2>
								<input type="text" placeholder="login" name="login" value="" />
								<input type="password" placeholder="password" name="passwd" value="" />
								<input class="submit" type="submit" name="submit" value="OK" />
								<p class="message">Are you registered? <a onclick="opentab('loginform')">Sign in</a></p>
							</form>
						</div>
					</div>
				</div>
			<hr>


<div class="drop">
<ul class="drop_menu">
	<li><a onclick="opentab('users')" >USERS</a>
	<li><a onclick="opentab('products')">PRODUCTS</a>
	<li><a onclick="opentab('another')">ANOTHER</a>
</ul>
</div>
<hr>
<div class="content" id="users">
<?php
	echo "<pre>";
	$arr = unserialize(file_get_contents("../private/passwd"));
	foreach ($arr as $key => $inarr) {
		print_r($inarr);
			}
	echo "</pre>";
?>
</div>
<div class="content" id="products" style="display:none">
2
</div>
<div class="content" id="another" style="display:none">
3
</div>


		<?php }
		else { ?>
		<div id="login-modal-form5" class="modal" style="display:block">
				<div id="loginform" class="login-page">
					<form class="form">
						<h2>Only authorized user!</h2>
						<a class="submit" onclick="window.location.href='index.php'">HOME PAGE</a>
					</form>
				</div>
		</div>
		<?php } ?>
		</div>


<script>
function opentab(tabname) {
	var i;
	var x = document.getElementsByClassName("content");
	for (i = 0; i < x.length; i++) {
	   x[i].style.display = "none";  
	}
	document.getElementById(tabname).style.display = "block";  
}
</script>
	</body>
</html>
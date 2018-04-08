<?php
	session_start();
	// echo session_id() . PHP_EOL;
?>
<html>
	<head>
		<title>ft_minishop</title>
		<meta charset="utf-8">
		<meta name="viewport" content="width=device-width, initial-scale=1.0">
		<meta http-equiv="X-UA-Compatible" content="IE=edge">
		<style>
		.footer {
			left: 0;
			bottom: 0;
			width: 100%;
			background-color: #fbba00;
			color: white;
			cursor: unset;
			text-align: center;
		}
		.footer p {
			display: block;
			margin: 0 auto;
			padding: 10px;
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
			h4 {
				color: #565454;
			}
			hr {
				max-width: 98%;
				clear: right;
			}
			.content-products {
				width: 98%;
				margin: 15px;
				padding: 15px;
			}
			.content-products h2 {
				color: #565454;
				font-size: 18px;
				margin: 5px;
			}
			.content-products .product-line {
				width: 98%
				margin: 5px;
			}
			.content-products .product-line .product{
				width: 19%;
				margin: 10px;
				border: 1px solid #E2E2E2;
				border: 5px solid #ffffff;
				-webkit-box-shadow: 0 0 10px rgba(0, 0, 0, 0.15);
				-moz-box-shadow: 0 0 10px rgba(0, 0, 0, 0.15);
				box-shadow: 0 0 10px rgba(0, 0, 0, 0.15);
				padding: 1em;
				float:left;
			}
			.product img {
				min-height: 5vw;
				max-height: 10vw;
				max-width: 100%;
				display: block;
				margin: 0 auto;
				border: 1px solid #ffffff;
				-webkit-box-shadow: 0 0 13px rgba(0, 0, 0, 1);
				-moz-box-shadow: 0 0 13px rgba(0, 0, 0, 1);
				box-shadow: 0 0 13px rgba(0, 0, 0, 1);
			}
			.product h3 {
				text-align: center;
				display: block;
				margin: 10px auto;
				margin-top: 25px;
				margin-bottom: 25px;
			}
			.product h4 {
				text-align: center;
				display: block;
				margin: 10px auto;
				margin-top: 25px;
				margin-bottom: 25px;
				font-style: italic;
				font-weight: 900;
				text-shadow:5px 5px 30px #fbba00;
			}
			.product button {
				background-color: #565454;
				color: white;
				padding: 10px 40px;
				margin: 0 auto;
				display: block;
				border: none;
				cursor: pointer;
			}
			@media (max-width : 758px) {
				.product button {
				background-color: #565454;
				color: white;
				padding: 5px 20px;
				margin: 0 auto;
				display: block;
				border: none;
				cursor: pointer;
				font-size: 10px;
			}
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
				max-width: 1500px;
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
			.adm, .login-b button:hover, .form .submit:hover,.form .submit:active,.form .submit:focus {
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
			<h1>Project Shop</h1>
				<div class="login-b">
					<?php
					function admcheck($login) {
						$arr = unserialize(file_get_contents("../private/passwd"));
						foreach ($arr as $key => $inarr) {
							if ($inarr['login'] === $login && $inarr['admin'] == 1) {
								return (true);
							}
						}
						return (false);
					}
					if (admcheck($_SESSION['authorized_user'])) {
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
								<input type="text" placeholder="e-mail" class="email-ch" name="email" value="" />
								<input type="text" placeholder="telephone" name="phone" value="" />
								<input class="submit" type="submit" name="submit" value="OK" />
								<p class="message">Are you registered? <a onclick="opentab('loginform')">Sign in</a></p>
							</form>
						</div>
					</div>
				</div>
			<hr>
	<?php 
		if (!file_exists('../private/product')) {
		mkdir("../private/product");
		}
		if (!file_exists('../private/product/product')) {
			file_put_contents('../private/product/product', null);
		}
		if (!file_exists('../private/p_l')) {
			mkdir("../private/p_l");
		}
		if (!file_exists('../private/p_l/p_l')) {
			file_put_contents('../private/p_l/p_l', null);
		}
		$list = unserialize(file_get_contents('../private/p_l/p_l'));
		foreach ($list as $key => $value) {
			echo "<hr><div class=\"content-products\"><h2>" . $value . "</h2><div class=\"product-line\">"  . PHP_EOL ;
			$account = unserialize(file_get_contents('../private/product/product'));
			foreach ($account as $val) {
				$i = 0;
				if (in_array($value, $val['type_of_product'])) {
					echo "<div class=\"product\"><img title=\"" . $val['description'] ."\" src=\"" . $val['url'] ."\"><h3>" . $val['name_of_product'] . "</h3><h4>" . $val['price'] ."UAH</h4><button>BUY</button></div>"  . PHP_EOL ;
				}
			}
			echo "</div></div><div style=\"clear:left\"><hr>" . PHP_EOL ;
		}	
		?>
</div></div>

<?php include 'inc_error_create.php';
?>

<div class="footer">
	<p>ft_minishop &copy; apakhomo:bgres
</div>
		</div>

<script>
var modal = document.getElementById('id01');
window.onclick = function(event) {
	if (event.target == modal) {
		modal.style.display = "none";
	}
}
function opentab(tabname) {
	var i;
	var x = document.getElementsByClassName("login-page");
	for (i = 0; i < x.length; i++) {
	   x[i].style.display = "none";  
	}
	document.getElementById(tabname).style.display = "block";  
}
</script>
	</body>
</html>
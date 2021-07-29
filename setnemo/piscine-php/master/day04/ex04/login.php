<html>
	<head>
		<title>CHAT 42</title>
		<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
		<style>
			body {
				background: #b36ea4;
			}
			.page {
				padding: 8% 0 0;
				font-family: "Roboto", sans-serif;
				position: relative;
				z-index: 1;
				background: #FFFFFF;
				max-width: 600px;
				margin: 10% auto ;
				padding: 45px;
				text-align: center;
				box-shadow: 0 0 20px 0 rgba(0, 0, 0, 0.2), 0 5px 5px 0 rgba(0, 0, 0, 0.24);
			}
			.login-page {
				width: 360px;
				padding: 8% 0 0;
				margin: auto;
				font-family: "Roboto", sans-serif;
			}
			.form {
				position: relative;
				z-index: 1;
				background: #FFFFFF;
				max-width: 360px;
				margin: 0 auto 100px;
				padding: 45px;
				text-align: center;
				box-shadow: 0 0 20px 0 rgba(0, 0, 0, 0.2), 0 5px 5px 0 rgba(0, 0, 0, 0.24);
			}
			.form input {
				color: #FFFFFF;
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
			.exit input {
				font-family: "Roboto", sans-serif;
				outline: 0;
				background: #5e2f62;
				width: 33%;
				border: 0;
				margin: 0 0 15px;
				padding: 15px;
				box-sizing: border-box;
				font-size: 10px;
			}
			.form .submit {
				font-family: "Roboto", sans-serif;
				text-transform: uppercase;
				outline: 0;
				background: #6c1f55;
				width: 100%;
				border: 0;
				padding: 15px;
				color: #FFFFFF;
				font-size: 14px;
				-webkit-transition: all 0.3 ease;
				transition: all 0.3 ease;
				cursor: pointer;
			}
			.exit .submit {
				font-family: "Roboto", sans-serif;
				text-transform: uppercase;
				outline: 0;
				background: #6c1f55;
				width: 33%;
				border: 0;
				padding: 7px;
				color: #FFFFFF;
				font-size: 12px;
				-webkit-transition: all 0.3 ease;
				transition: all 0.3 ease;
				cursor: pointer;
			}
			.form .exit .submit:hover,.form .submit:active,.form .submit:focus {
				background: #5e2f62;
			}
			.form .message {
				margin: 15px 0 0;
				color: #b3b3b3;
				font-size: 12px;
			}
			.form .message a {
				color: #4CAF50;
				text-decoration: none;
			}
		</style>
	</head>
	<body>
	<?php
		session_start();

		include 'auth.php';

		if (auth($_POST['login'], hash("whirlpool", $_POST['passwd']))) {
?>
		<?php
			$_SESSION['authorized_user'] = $_POST['login'];
		?>
		<div class="page">
				<h1>CHAT 42</h1>
			<iframe name="chat" src="chat.php" width="100%" height="550px"></iframe>
			<iframe name="speak" src="speak.php" width="100%" height="50px"></iframe>
			<form class="exit" action="logout.php" method="POST"><input class="submit" type="submit" name="submit" value="LOG OUT" /></form>
		</div>
		<?php
		} 
		if (!(auth($_POST['login'], hash("whirlpool", $_POST['passwd']))) ){
			$_SESSION['authorized_user'] = "";
		?>
		<div class="login-page">
			<form class="form" action="login.php" method="POST">
				<h2>CHAT 42</h2>
				<h3>Error! You are not authorized!</h3>
				<p class="message">You are registered? <a href="index.html">Sign in an account</a></p>
				<p class="message">You are registered? <a href="modif.html">Change password</a></p>
				<p class="message">Not registered? <a href="create.html">Create an account</a></p>
			</form>
		</div>
		<?php
		}
		?>
	</body>
</html>

<?php
	session_start();

	if ($_GET['submit'] === "OK") {
		$_SESSION['login'] = $_GET['login'];
		$_SESSION['passwd'] = $_GET['passwd'];
	}
?>
<html>
	<head>
		<style>
			.login-page {
				width: 360px;
				padding: 8% 0 0;
				margin: auto;
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
			.form .submit:hover,.form .submit:active,.form .submit:focus {
				background: #5e2f62;
			}
			body {
				background: #b36ea4;
			}
		</style>
	</head>
	<body>
		<div class="login-page">
			<form class="form" action="index.php" method="GET">
				<input type="text" placeholder="login" name="login" value="<?php echo $_SESSION['login']; ?>" />
				<input type="password" placeholder="password" name="passwd" value="<?php echo $_SESSION['passwd']; ?>" />
				<input class="submit" type="submit" name="submit" value="OK" />
			</form>
		</div>
	</body>
</html>
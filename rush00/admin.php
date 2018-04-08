<html>
	<head>
		<title>ft_minishop</title>
		<meta name="viewport" content="width=device-width, initial-scale=1">
		<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
		<style>

.custom-select {
  position: relative;
  margin-bottom: 20px;
}
.custom-select select {
  display: none;
    margin-bottom: 20px;
}
.select-selected {
  background-color: #565454;
}

.select-selected:after {
  position: absolute;
  content: "";
  top: 14px;
  right: 10px;
  width: 0;
  height: 0;
  border: 6px solid transparent;
  border-color: #fff transparent transparent transparent;
}
.select-selected.select-arrow-active:after {
  border-color: transparent transparent #fff transparent;
  top: 7px;
}
.select-items div,.select-selected {
  color: #FFFFFF;
  padding: 8px 16px;
  border: 1px solid transparent;
  border-color: transparent transparent rgba(0, 0, 0, 0.1) transparent;
  cursor: pointer;
  user-select: none;
}
.select-items {
  position: absolute;
  background-color: #fbba00;
  top: 100%;
  left: 0;
  right: 0;
  z-index: 99;
}
.select-hide {
  display: none;
}
.select-items div:hover {
  background-color: rgba(0, 0, 0, 0.1);
}


#userstable {
    font-family: "Trebuchet MS", Arial, Helvetica, sans-serif;
    border-collapse: collapse;
}

#userstable td, #userstable th {
    border: 1px solid #ddd;
    padding: 8px;
}

#userstable tr:nth-child(even){background-color: #f2f2f2;}

#userstable tr:hover {background-color: #ddd;}
#userstable img {width: 20px;}
#userstable .admin {width: 100px;}
#userstable .pic {width: 20px;}

#userstable th {
    padding-top: 12px;
    padding-bottom: 12px;
    text-align: left;
    background-color: #fbba00;
    color: white;
}
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
			#products, #users {
				width: 98%;
				margin: 0 auto;
			}
			#products .addproductb {
				background-color: #565454;
				color: white;
				padding: 14px 20px;
				margin: auto 3px;
				border: none;
				cursor: pointer;
				right: 20px;
				top: 3px;
				float: left;
			}
			#products .delproductb {
				background-color: #565454;
				color: white;
				padding: 14px 20px;
				margin: auto 3px;
				border: none;
				cursor: pointer;
				right: 20px;
				top: 3px;
				float: left;
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
				display: none;
				position: fixed;
				z-index: 5;
				left: 0;
				top: 0;
				width: 100%;
				height: 100%;
				overflow: auto;
				background-color: rgb(0,0,0);
				background-color: rgba(0,0,0,0.4);
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
				z-index: 12;
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
					if ($inarr['login'] === $login && $inarr['admin'] == 1) {
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
					
					<?php
					if (admcheck($_SESSION['authorized_user'])) {
					?>
					<button class="adm" onclick="window.location.href='index.php'">Shop</button>
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
	echo "<table id=\"userstable\"><tbody><tr><th>login</th><th>email</th><th>telephone</th><th class=\"admin\">admin rights</th><th class=\"pic\">edit</th><th class=\"pic\">del</th></tr>";
	$arr = unserialize(file_get_contents("../private/passwd"));
	foreach ($arr as $key => $inarr) {
			echo "<tr>";
			foreach ($inarr as $line => $value) {
				if ($line != 'passwd' && $line != 'admin') {
					echo "<td>" . $inarr[$line] . "</td>";
					}
				if ($line == 'admin') {
					if ($inarr[$line] == 1) {
						echo "<td class=\"admin\"> + </td>";
					}
					else {
						echo "<td class=\"admin\"> - </td>";
					}
				echo "<td class=\"pic\">
						<a onclick=\"document.getElementById('edit-" . $inarr['login'] . "-modal-form').style.display='block'\"><img src=\"./img/edit.png\"></a>
						</td><td class=\"pic\">
						<a><img src=\"./img/delete.png\"><a>
						</td></tr>";
				}
			}
			}
	echo "</tbody></table>";

	foreach ($arr as $key => $inarr) {
			foreach ($inarr as $line => $value) {
			echo "	
			<div class=\"login-b\">
			<div id=\"edit-" . $inarr['login'] . "-modal-form\" class=\"modal\" >
			<div class=\"login-page\">
			<form class=\"form\" action=\"modif.php\" method=\"POST\">
			<div class=\"imgcontainer\">
			<span onclick=\"document.getElementById('edit-" . $inarr['login'] . "-modal-form').style.display='none'\" class=\"close\" title=\"Close Modal\">&times;</span>
			</div>
			<h2>USER: " . $inarr['login'] . "</h2>
			<h3>e-mail: " . $inarr['email'] . "</h3>
			<h3>phone: " . $inarr['phone'] . "</h3>
			<input type=\"text\" placeholder=\"new e-mail\" name=\"login\" style=\"display:none;\" value=\"" . $inarr['login'] . "\" />
			<input type=\"text\" placeholder=\"new e-mail\" name=\"email\" value=\"\" />
			<input type=\"text\" placeholder=\"new telephone\" name=\"phone\" value=\"\" />";
			if ($inarr['login'] != "admin") {
				echo "<div class=\"custom-select\" ><select name=\"select\">
				<option value=\"0\">do not choose</option>
				<option value=\"2\">USER</option>
				<option value=\"1\">ADMIN</option>
			</select></div>";
			}
			echo "<input class=\"submit\" type=\"submit\" name=\"submit\" value=\"OK\" />
			</form>
			</div>
			</div>
			</div>
			
			";
			}
			}


?>
</div>
<div class="content" id="products" style="display:none">


				<div class="products-tab">
					<button class="addproductb" onclick="document.getElementById('addproduct').style.display='block'" style="width:auto;">add product</button>
					<div id="addproduct" class="modal">
						<div id="loginform" class="login-page">
							<form class="form" action="add_product.php" method="POST">
							<div class="imgcontainer">
							  <span onclick="document.getElementById('addproduct').style.display='none'" class="close"  title="Close Modal">&times;</span>
							</div>
								<h2>add product</h2>
								<input type="type_of_product" placeholder="type_of_product" name="type_of_product" value="" />
								<input type="name_of_product" placeholder="name_of_product" name="name_of_product" value="" />
									<input type="hidden" name="MAX_FILE_SIZE" value="30000">
									<input enctype="multipart/form-data" name="userfile" type="file">
									<input class="submit" type="submit" name="submit" value="OK" />
							</form>
						</div>
					</div>
				</div>
				<div class="delproduct">
					<button class="delproductb" onclick="document.getElementById('delproduct').style.display='block'" style="width:auto;">del_products</button>
					<div id="delproduct" class="modal">
						<div id="delproduct" class="delзroducts">
							<form class="form" action="del_product.php" method="POST">
							<div class="imgcontainer">
							  <span onclick="document.getElementById('delproduct').style.display='none'" class="close"  title="Close Modal">&times;</span>
							</div>
								<h2>Delit priduct</h2>
								<input type="type_of_product" placeholder="type_of_product" name="type_of_product" value="" />
								<input type="name_of_product" placeholder="name_of_product" name="name_of_product" value="" />
								<input class="submit" type="submit" name="submit" value="OK" />
							</form>
						</div>
					</div>
				</div> <hr style="clear:left; margin:auto 3px">
				<div class="product_tabl">
					<?php
							if (!file_exists('../private/product')) {
								mkdir("../private/product");
							}
							if (!file_exists('../private/product/product')) {
								file_put_contents('../private/product/product', null);
							}
						$txt = unserialize(file_get_contents('../private/product/product'));
							echo "<table id=\"userstable\">" . "<th>NAME</th><th>CATEGORY</th><th>IMAGE</th>";
						foreach ($txt as $k => $v) {
							echo "<tr>";
							echo "<td>name=".$v['name_of_product']."   </td>";
							echo "<td>type_of_product=";
							foreach ($v['type_of_product'] as $key => $value) {
								echo"$value   ";
							}
							echo "</td>";
							echo "<td>".$txt['img']."</td>";
							echo "</tr>";
							echo "</br>";
						}
						echo "</table>";
					?>
				</div>







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
<script>
var x, i, j, selElmnt, a, b, c;
x = document.getElementsByClassName("custom-select");
for (i = 0; i < x.length; i++) {
  selElmnt = x[i].getElementsByTagName("select")[0];
  a = document.createElement("DIV");
  a.setAttribute("class", "select-selected");
  a.innerHTML = selElmnt.options[selElmnt.selectedIndex].innerHTML;
  x[i].appendChild(a);
  b = document.createElement("DIV");
  b.setAttribute("class", "select-items select-hide");
  for (j = 1; j < selElmnt.length; j++) {
    c = document.createElement("DIV");
    c.innerHTML = selElmnt.options[j].innerHTML;
    c.addEventListener("click", function(e) {
        var i, s, h;
        s = this.parentNode.parentNode.getElementsByTagName("select")[0];
        h = this.parentNode.previousSibling;
        for (i = 0; i < s.length; i++) {
          if (s.options[i].innerHTML == this.innerHTML) {
            s.selectedIndex = i;
            h.innerHTML = this.innerHTML;
            break;
          }
        }
        h.click();
    });
    b.appendChild(c);
  }
  x[i].appendChild(b);
  a.addEventListener("click", function(e) {
      e.stopPropagation();
      closeAllSelect(this);
      this.nextSibling.classList.toggle("select-hide");
      this.classList.toggle("select-arrow-active");
    });
}
function closeAllSelect(elmnt) {
  var x, y, i, arrNo = [];
  x = document.getElementsByClassName("select-items");
  y = document.getElementsByClassName("select-selected");
  for (i = 0; i < y.length; i++) {
    if (elmnt == y[i]) {
      arrNo.push(i)
    } else {
      y[i].classList.remove("select-arrow-active");
    }
  }
  for (i = 0; i < x.length; i++) {
    if (arrNo.indexOf(i)) {
      x[i].classList.add("select-hide");
    }
  }
}
document.addEventListener("click", closeAllSelect);
</script>

	</body>
</html>
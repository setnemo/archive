<!doctype html>
<html lang="ru">
		<head>
				<!-- Required meta tags -->
				<meta charset="utf-8">
				<meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
				<link rel="shortcut icon" type="image/x-icon"  href="/icon_uf.png" >
				<!-- Bootstrap CSS -->
				<link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css" integrity="sha384-MCw98/SFnGE8fJT3GXwEOngsV7Zt27NXFoaoApmYm81iuXoPkFOJwJ8ERdknLPMO" crossorigin="anonymous">
				<link rel="stylesheet" type="text/css" href="https://cdn.datatables.net/v/bs4/dt-1.10.18/datatables.min.css"/>
				<link rel="stylesheet" type="text/css" href="style.css"/>
				<title>Rage Against The aPi</title>
				<!-- Optional JavaScript -->
				<!-- jQuery first, then Popper.js, then Bootstrap JS -->
				<script src="https://code.jquery.com/jquery-3.3.1.min.js" integrity="sha256-FgpCb/KJQlLNfOu91ta32o/NMZxltwRo8QtmkMRdAu8=" crossorigin="anonymous"></script>
				<script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.3/umd/popper.min.js" integrity="sha384-ZMP7rVo3mIykV+2+9J3UJ46jBk0WLaUAdn689aCwoqbBJiSnjAK/l8WvCWPIPm49" crossorigin="anonymous"></script>
				<script src="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/js/bootstrap.min.js" integrity="sha384-ChfqqxuZUCnJSK3+MXmPNIyE6ZbWh2IMqE241rYiqJxyMiZ6OW/JmZQ5stwEULTy" crossorigin="anonymous"></script>
				<script type="text/javascript" src="https://cdn.datatables.net/v/bs4/dt-1.10.18/datatables.min.js"></script>
				<script type="text/javascript" src="script.js"></script>
		</head>
		<body>
<div class="container">
<h1 class="form-heading">Rage Against The aPi</h1>
<div class="login-form">
<div class="main-div">
    <div class="panel">
   <h2></h2>
   <p>Please enter place</p>
   </div>
    <form id="Login" class='row'>
        <div class="form-group col-md-6" id='src1'>
            <input type="text" class="form-control" id="inputEmail" placeholder="Start Place">
        </div>
        <div class="form-group col-md-6" id='dst1'>
            <input type="text" class="form-control" id="inputPassword" placeholder="Finish Place">
        </div>
        <button type="submit" class="btn btn-danger">SEARCH PLACE</button>
        <div class="form-group col-md-6" id='src2'>
        	<hr>
			<label class="radio">Place1
				<input type="radio" checked="checked" name="is_company">
				<span class="checkround"></span>
			</label>
			<label class="radio">Place2
				<input type="radio" name="is_company">
				<span class="checkround"></span>
			</label>
			<label class="radio">Place3
				<input type="radio" name="is_company">
				<span class="checkround"></span>
			</label>
			<label class="radio">Place4
				<input type="radio" name="is_company">
				<span class="checkround"></span>
			</label>
        </div>
        <div class="form-group col-md-6" id='dst2'>
        	<hr>
			<label class="radio">Place5
				<input type="radio" checked="checked" name="is_company2">
				<span class="checkround"></span>
			</label>
			<label class="radio">Place6
				<input type="radio" name="is_company2">
				<span class="checkround"></span>
			</label>
			<label class="radio">Place7
				<input type="radio" name="is_company2">
				<span class="checkround"></span>
			</label>
			<label class="radio">Place8
				<input type="radio" name="is_company2">
				<span class="checkround"></span>
			</label>
        </div>
        <button type="submit" class="btn btn-primary">SELECT PlACE</button>
    </form>
    </div>
<p class="botto-text">apakhomo, mgayduk &copy; 2018</p>
</body>
</html>
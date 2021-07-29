<?php
// Open the file
date_default_timezone_set('Europe/Kiev'); 

$fp = @fopen('../command_log.csv', 'r'); 

// Add each line to an array
if ($fp) {
	 $array = explode("\n", fread($fp, filesize('../command_log.csv')));
}
?>
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
				<!-- Custom styles for this template -->
				<title>K.I.F.T. Logs</title>
				<!-- Optional JavaScript -->
				<!-- jQuery first, then Popper.js, then Bootstrap JS -->
				<script src="https://code.jquery.com/jquery-3.3.1.min.js" integrity="sha256-FgpCb/KJQlLNfOu91ta32o/NMZxltwRo8QtmkMRdAu8=" crossorigin="anonymous"></script>
				<script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.3/umd/popper.min.js" integrity="sha384-ZMP7rVo3mIykV+2+9J3UJ46jBk0WLaUAdn689aCwoqbBJiSnjAK/l8WvCWPIPm49" crossorigin="anonymous"></script>
				<script src="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/js/bootstrap.min.js" integrity="sha384-ChfqqxuZUCnJSK3+MXmPNIyE6ZbWh2IMqE241rYiqJxyMiZ6OW/JmZQ5stwEULTy" crossorigin="anonymous"></script>
				<script type="text/javascript" src="https://cdn.datatables.net/v/bs4/dt-1.10.18/datatables.min.js"></script>
		</head>
<body>
		<!-- Begin page content -->
		<main role="main" class="container">
				<h2 class="mt-5">K.I.F.T Project. JOPA Assistant Logs</h2>
				<?php if (isset($array)) { ?>
				<div style="max-width: 100%; overflow: auto;">
						<div class="container">
							<div class="row">
								<div class="col-lg-12 mx-auto m-3">
									<input class="form-control" id="search" type="text" placeholder="Type anything...">
								</div>
							</div>
						</div>
						<table class="table table-striped" >
							<thead>
								<tr>
									<th scope="col" data-placement="auto" title="Time execute">Time</th>
									<th scope="col" data-placement="auto" title="Time execute">Command</th>
									<th scope="col" data-placement="auto" title="Time execute">Answer</th>
								</tr>
							</thead>
							<tbody id="alldata">
								<?php foreach ($array as $key => $value) { ?>
								<tr>
									<?php $tmp =  explode(",", $value);
									if ($tmp[0]) { ?>
									<td><?php echo date('m/d/Y H:i:s', trim($tmp[0], '"')); ?></td>
									<td><?php echo trim($tmp[1], '"');?></td>
									<td><?php echo trim($tmp[2], '"'); ?></td>
								</tr>
								<?php } } ?>
							</tbody>
						</table>
						<?php } else { ?>
						<h4>Log file not found!</h4>
						<?php } ?>
				</div>
		</main>

<script>
$(document).ready(function(){
	$("#search").on("keyup", function() {
		var value = $(this).val().toLowerCase();
		$("#alldata tr").filter(function() {
			$(this).toggle($(this).text().toLowerCase().indexOf(value) > -1)
		});
	});
});
window.onload = function() {
	setTimeout(yeah, 10000);
}
function yeah() {
	$.ajax({
			type:"POST",
			url: 'refresh.php',
		data: {},
			success: function(response){
				$('#alldata').html(response);
		}
	});
	setTimeout(yeah, 10000);
}

</script>
</body>
</html>
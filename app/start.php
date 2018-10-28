<?php

require_once('RatpClient.php'); 

if (isset($_POST['first']) && isset($_POST['last']) && strlen($_POST['first']) && strlen($_POST['last']) )
{
	$c = new RatpClient();
	$r1 = $c->getMetro($_POST['first']);
	// echo "<pre>";
	// print_r($r1);
	// echo "</pre>";
	?><div class="form-group col-md-6" id='src2'><hr><?php
	foreach ($r1 as $key) { ?>
        <label class="radio"><?php echo $key['label']; ?>
            <input type="radio" checked="checked" name="is_company">
            <span class="checkround"></span>
        </label>
<?php }
	?></div><?php
	$r2 = $c->getMetro($_POST['last']);
	// echo "<pre>";
	// print_r($r2);
	// echo "</pre>";
	
}	?><div class="form-group col-md-6" id='dst2'><hr><?php
	foreach ($r2 as $key) { ?>
        <label class="radio"><?php echo $key['label']; ?>
            <input type="radio" checked="checked" name="is_company2">
            <span class="checkround"></span>
        </label>
<?php }
	?></div>

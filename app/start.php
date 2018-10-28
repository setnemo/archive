<?php

require_once('RatpClient.php'); 

if (isset($_POST['first']) && isset($_POST['last']) && strlen($_POST['first']) > 0 && strlen($_POST['last']) > 0 )
{
	$c = new RatpClient();
	$r1 = $c->getMetro($_POST['first']);
	$r2 = $c->getMetro($_POST['last']);
	?><div class="form-group col-md-6" id='src2'><hr><?php
	if (count($r1) == 0 || count($r2) == 0) { exit ;}
	foreach ($r1 as $key) { ?>
        <label class="radio"><?php echo $key['label']; ?>
            <input type="radio" checked="checked" name="is_company" value="><?php echo $key['label']; ?>">
            <span class="checkround"></span>
        </label>
<?php }
	?></div><?php
?><div class="form-group col-md-6" id='dst2'><hr><?php
	foreach ($r2 as $key) { ?>
        <label class="radio"><?php echo $key['label']; ?>
            <input type="radio" checked="checked" name="is_company2" value="><?php echo $key['label']; ?>">
            <span class="checkround"></span>
        </label>
<?php }
	}	?></div>

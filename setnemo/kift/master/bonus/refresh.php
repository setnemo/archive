<?php
// Open the file
date_default_timezone_set('Europe/Kiev'); 

$fp = @fopen('../command_log.csv', 'r'); 

// Add each line to an array
if ($fp) {
	 $array = explode("\n", fread($fp, filesize('../command_log.csv')));
}
?>
<?php if (isset($array)) { ?>
		<?php foreach ($array as $key => $value) { ?>
		<tr>
			<?php $tmp =  explode(",", $value);
			if ($tmp[0]) { ?>
			<td><?php echo date('m/d/Y H:i:s', trim($tmp[0], '"')); ?></td>
			<td><?php echo trim($tmp[1], '"');?></td>
			<td><?php echo trim($tmp[2], '"'); ?></td>
		</tr>
		<?php } } ?>

<?php } else { ?>
<h4>Log file not found!</h4>
<?php } ?>
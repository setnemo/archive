<?php

include_once('Lannister.class.php');

Class Tyrion extends Lannister {
	public function sleepWith($obj) {
		if (is_subclass_of($obj, 'Lannister'))
			echo "Not even if I'm drunk !" . PHP_EOL;
		else
			echo "Let's do this." . PHP_EOL;
	}
}

?>

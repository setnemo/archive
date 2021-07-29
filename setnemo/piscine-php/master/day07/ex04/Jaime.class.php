<?php

include_once('Lannister.class.php');

Class Jaime extends Lannister {
	public function sleepWith($obj) {
		if (is_subclass_of($obj, 'Lannister')) {
			if (get_class($obj) === 'Cersei')
				echo "With pleasure, but only in a tower in Winterfell, then." . PHP_EOL;
			else
				echo "Not even if I'm drunk !" . PHP_EOL;
		}
		else
			echo "Let's do this." . PHP_EOL;
	}
}

?>

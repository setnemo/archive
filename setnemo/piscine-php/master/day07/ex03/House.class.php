<?php
Class House {
	public function introduce() {
		$str = 'House ' . $this->getHouseName() . ' of ' . $this->getHouseSeat() . " : \"" . $this->getHouseMotto() . "\"";
		echo $str . PHP_EOL;
		return ;
	}
}
?>

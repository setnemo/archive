<?php

Class NightsWatch {
	public function recruit($obj){
		if ($obj instanceof IFighter)
			$obj->fight();
	}
	public function fight(){
		return ;
	}
}

?>

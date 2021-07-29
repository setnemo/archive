#!/usr/bin/php
<?PHP
	function ft_is_sort($arr)
	{
		$for_sort = $arr;
		$for_sort_r = $arr;
		sort($for_sort);
		rsort($for_sort_r);
		if ($for_sort === $arr || $for_sort_r === $arr)
			return (true);
		else
			return (false);
	}
?>

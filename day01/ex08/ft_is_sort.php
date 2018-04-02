#!/usr/bin/php
<?PHP
	function ft_is_sort($arr)
	{
		$for_sort = $arr;
		sort($for_sort);
		if ($for_sort === $arr)
			return (true);
		else
			return (false);
	}
?>

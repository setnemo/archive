<?php
	if ($_POST['type_of_product'] && $_POST['name_of_product']  && $_POST['submit'] && $_POST['submit'] === "OK") {
		if (!file_exists('../private/product')) {
			mkdir("../private/product");
		}
		if (!file_exists('../private/product/product')) {
			file_put_contents('../private/product/product', null);
		}
		$account = unserialize(file_get_contents('../private/product/product'));
		if ($account) {
			$exist = 0;
			foreach ($account as $k =>$v) {
				if ($v['name_of_product'] === $_POST['name_of_product']) {
					foreach ($v['type_of_product'] as $key => $value) {
						if ($value == $_POST['type_of_product'])
							$exist = 1;
					}
				}
			}
		}
		if ($exist > 0) {
			echo "such product already exists\n";
		} else {
			$arrayName = preg_split("/ *, */", $_POST['type_of_product']);
			$tmp['type_of_product'] = $arrayName;
			$tmp['name_of_product'] = $_POST['name_of_product'];
			$account[] = $tmp;
			file_put_contents('../private/product/product', serialize($account));
			header("Location: admin.php",TRUE,301);
		}
	} else {
		echo "asdasdsad".$_POST['img'];
		echo "<p>not all fields are filled</p>";
	}
?>
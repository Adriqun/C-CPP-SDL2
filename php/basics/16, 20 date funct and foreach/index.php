<html>
<head>
	<meta charset="=UTF-8">
	<title>Title</title>
</head>
<body>
	
	<?php
		$dayofweek = date('w');
		echo $dayofweek."<br>";

		$array = array("Arek", "Czarek", "Burek");
		foreach ($array as $data) {
			echo "My name is ".$data."<br>";
		}
	?>
</body>
</html>


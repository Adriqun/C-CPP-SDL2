<html>
<head>
	<meta charset="=UTF-8">
	<title>Title</title>
</head>

<body>
	
	<?php
		$x = 5;

		function sth($x) {
			echo $GLOBALS['x'];
		}

		sth(0);
	?>
</body>
</html>


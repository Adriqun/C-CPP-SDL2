<html>
<head>
	<meta charset="=UTF-8">
	<title>Title</title>
</head>
<body>

	<form method="GET">
		<input type="text" name="number">
		<button>SQUARE IT</button>
	</form>
	
	<?php
		$nr = $_GET['number'];
		echo $nr**2;

		$myarray = array('a', 'b', 'c');
		echo $myarray['1'];
	?>
</body>
</html>


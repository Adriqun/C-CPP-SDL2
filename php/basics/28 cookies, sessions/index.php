<html>
<head>
	<meta charset="=UTF-8">
	<title>Title</title>
</head>

<body>
	<?php
		setcookie("name", "Daniel", time() +86400); // if negative - destroys itself instantly time() -1

		$_SESSION['name'] = "12";
	?>
</body>
</html>


<html>
<head>
	<meta charset="=UTF-8">
	<title>Title</title>
</head>

<body>

	<form method="POST">
		<input type="hidden" name="name" value="Daniel">
		<button type="submit">PRESS ME</button>
	</form>
	
	<?php
		function echoGet($n) {
			echo $_GET[$n];
		}

		function echoPost($n) {
			echo $_POST[$n];
		}

		echoPost("name");
	?>
</body>
</html>


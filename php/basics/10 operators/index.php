<html>
<head>
	<meta charset="=UTF-8">
	<title>Title</title>
</head>
<body>

	<?php
		// Comparison operators
		$a = 10;
		$b = 10.0;
		$c = "10";

		if($a === $b)
		{
			echo "Same data type, same value";
		}
		else if($a !== $c)
		{
			echo "Different data type, same value"."<br>";
		}

		if($a <> $c)
		{

		}
		else
		{
			echo "Values are the same";
		}
	?>
</body>
</html>


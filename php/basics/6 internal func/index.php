<html>
<head>
	<meta charset="=UTF-8">
	<title>Title</title>
</head>
<body>

	<form method="GET">
		<input type="text" name="person">
		<button>SUBMIT</button>
	</form>
	
	<?php
		$name = $_GET['person'];
		echo "Amount of chars: ".strlen($name)."<br>";
		echo "Number of words: ".str_word_count($name)."<br>";
		echo "Reversed word: ".strrev($name)."<br>";
		echo 'Position of letter "a": '.strpos($name, 'a')."<br>";
		echo 'Letter "a" replace with "b": '.str_replace('a', 'b', $name)."<br>";
	?>
</body>
</html>


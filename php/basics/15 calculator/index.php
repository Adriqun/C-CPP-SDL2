<html>
<head>
	<meta charset="=UTF-8">
	<title>Title</title>
</head>
<body>
	
	<form>
		<input type="text" name="num1" placeholder="number I">
		<input type="text" name="num2" placeholder="number II">
	

	<select name="operator">
		<option>Add</option>
		<option>Substract</option>
		<option>Multiply</option>
		<option>Divide</option>
	</select>
	<br>
	<button type="submit" name="submit" value="submit">Calculate</button>
	</form>
	<br>
	
	<?php
		echo "Result: ";
		if (isset($_GET['submit']))
		{
			$num1 = $_GET['num1'];
			$num2 = $_GET['num2'];
			$operator = $_GET['operator'];
			switch($operator)
			{
				case "Add": echo $num1 +$num2;
				break;

				case "Substract": echo $num1 -$num2;
				break;

				case "Multiply": echo $num1 *$num2;
				break;

				case "Divide": echo $num1 /$num2;
				break;
			}
		}
	?>
</body>
</html>


function odliczanie()
	{
		var today = new Date();

		var day = today.getDate();
		var month = today.getMonth()+1;
		var year = today.getFullYear();

		var hour = today.getHours();
		var minute = today.getMinutes();
		var second = today.getSeconds();

		if( day < 10 )
			day = "0" + day;

		if( month < 10 )
			month = "0" + month;

		if( hour < 10 )
			hour = "0" + hour;

		if( minute < 10 )
			minute = "0" + minute;

		if( second < 10 )
			second = "0" + second;

		document.getElementById( "zegar" ).innerHTML = day + "/" + month + "/" + year + " | " + hour + ":" + minute + ":" + second;

		setTimeout( "odliczanie()", 1000 );
	}
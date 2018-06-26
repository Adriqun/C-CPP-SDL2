var iterate = ( function()
{
	var i = 1;
	return function()
	{
		document.getElementById( "demo" ).innerHTML = i;
		return i++;
	}
})();
using System;

namespace if_else
{
	class MainClass
	{
		public static void Main (string[] args)
		{
			int zmienna;
			zmienna = Convert.ToInt32 (Console.ReadLine ());
			if (zmienna < 100)
				Console.WriteLine ("Wpisales liczbe mniejsze od 100");
			else if(zmienna == 100)
				Console.WriteLine ("Wpisales liczbe 100");
			else
				Console.WriteLine ("Wpisales liczbe wieksza od 100");
		}
	}
}

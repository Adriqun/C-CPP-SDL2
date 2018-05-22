using System;

namespace petle
{
	class MainClass
	{
		public static void Main (string[] args)
		{
			for (int i = 0; i < 2; i++) 
			{
				Console.Write (i);
				Console.Write("<- to jest petla for \n");
			}
			Console.WriteLine ("\n");

			int j = 0;
			while(j < 5)
			{
				Console.Write(j);
				Console.Write("<- to jest petla while \n");
				j++;
			}
			Console.WriteLine ("\n");

			j = 0;
			do 
			{
				Console.Write(j);
				Console.Write("<- to jest petla do while \n");
			} while(j > 4);
			Console.ReadKey ();
		}
	}
}

using System;

namespace switch_beta
{
	class MainClass
	{
		public static string imie, nazwisko, wiek;

		public static void wyswietl_menu()
		{
			Console.Clear ();
			Console.WriteLine (" Formularz ");
			Console.WriteLine ("I.   Imie");
			Console.WriteLine ("II.  Nazwisko");
			Console.WriteLine ("III. Wiek");
			Console.WriteLine ("IV.  Wyswietl formularz");
		}
		public static void wyswietl_formularz( )
		{
			Console.Clear ();
			Console.Write ("Twoje imie: ");
			Console.Write (imie);
			Console.Write ("\nTwoje nazwisko: ");
			Console.Write (nazwisko);
			Console.Write ("\nTwoj wiek: ");
			Console.Write (wiek);
			Console.Write ("\nNacisnij dowolny klawisz");
			char z = Convert.ToChar (Console.ReadLine ());
		}
		public static void menu()
		{
			char znak;
			string input = Console.ReadLine();

			while (true) {
				wyswietl_menu ();
				znak = Convert.ToChar (Console.ReadLine ());
					
						switch (znak) {
						case '1':
							Console.Clear ();
							Console.WriteLine ("Wpisz swoje imie: ");
							imie = Convert.ToString (Console.ReadLine ());
							break;
						case '2':
							Console.Clear ();
							Console.WriteLine ("Wpisz swoje nazwisko: ");
							nazwisko = Convert.ToString (Console.ReadLine ());
							break;
						case '3':
							Console.Clear ();
							Console.WriteLine ("Wpisz swoj wiek: ");
							wiek = Convert.ToString (Console.ReadLine ());
							break;
						case '4':
							wyswietl_formularz ();
							break;
						default:
							Console.WriteLine ("Zly wybor! ");
							System.Threading.Thread.Sleep (2000);
							break;
						}
					
			}
		}
		
		public static void Main (string[] args)
		{
			wyswietl_menu ();
			menu ();
		}
	}
}

package constructors;

public class Main {
	
	public static void main(String[] args) {
		Example ex1 = new Example();
		Example ex2 = new Example(0);
		
		System.out.printf("Ex1 value: %d\n", ex1.GetValue());
		System.out.printf("Ex1 value: %d\n", ex2.GetValue());
	}
}

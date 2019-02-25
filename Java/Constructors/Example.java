package constructors;

public class Example {
	int value;
	
	// no parameters
	public Example() {
		value = 0xFF;
	}
	
	// with parameters
	public Example(int newValue) {
		this.value = newValue;
	}
	
	public int GetValue() {
		return this.value;
	}
}

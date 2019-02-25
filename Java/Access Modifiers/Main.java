package access_mod;



public class Main {

	public static void main(String[] args) {
		
		Main main = null;
		main = new Main();
		System.out.println(main.getFormat());
	}
	
	private String format = "14";

	public String getFormat() {
		return this.format;
	}

	public void setFormat(String format) {
	   this.format = format;
	}
   
	protected boolean open() {
		/*Implementation*/
		return false;
	}
}

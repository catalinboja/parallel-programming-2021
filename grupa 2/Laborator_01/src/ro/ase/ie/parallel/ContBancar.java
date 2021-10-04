package ro.ase.ie.parallel;

public class ContBancar {
	
	double sold;

	public ContBancar(double sold) {
		super();
		this.sold = sold;
	}

	public double getSold() {
		return sold;
	}
	
	public synchronized void plata(double suma) {
		System.out.println(String.format("Sold disponibil = %f, de platit = %f", sold, suma));
		if(suma <= sold) {
			System.out.println("Plata acceptata pentru suma " + suma);
			this.sold -= suma;
		}
		System.out.println("Sold ramas = " + sold);
	}

}

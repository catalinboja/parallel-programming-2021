package ro.ase.ie.parallel;

public class ContBancar {
	
	double balanta;

	public ContBancar(double balanta) {
		this.balanta = balanta;
	}

	public double getBalanta() {
		return balanta;
	}
	
	public synchronized void plata(double suma) {
		System.out.println(String.format("Sold existent = %f, validare plata pentru suma %f", balanta, suma));
		if(suma <= this.balanta) {
			System.out.println("Plata acceptata pentru " + suma);
			this.balanta -= suma;
		}	
	}
}

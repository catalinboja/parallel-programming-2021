package ro.ase.ie.parallel;

import java.util.Random;

public class Card implements Runnable{
	
	ContBancar cont;
	String nume;
	
	
	public Card(ContBancar cont, String nume) {
		super();
		this.cont = cont;
		this.nume = nume;
	}


	@Override
	public void run() {
		
		Random random = new Random();
		
		while(cont.getSold() > 0) {
			int suma = random.nextInt(10);
			System.out.println(String.format("%s incearca o plata de %d lei", nume, suma));
			this.cont.plata(suma);
		}
		
	}
	
}

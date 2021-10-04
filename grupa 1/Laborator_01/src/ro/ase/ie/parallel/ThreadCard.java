package ro.ase.ie.parallel;

import java.util.Random;

public class ThreadCard implements Runnable{
	
	ContBancar cont;
	String numeCard;
	
	public ThreadCard(ContBancar cont, String numeCard) {
		super();
		this.cont = cont;
		this.numeCard = numeCard;
	}

	@Override
	public void run() {
		
		Random  random  = new Random();
		
		while(this.cont.getBalanta() > 0) {
			double suma = random.nextInt(10);
			this.cont.plata(suma);
			System.out.println("Sold disponibil: " + this.cont.getBalanta());
		}
		
	}

}

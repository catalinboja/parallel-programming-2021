package ro.ase.ie.parallel.cachevolatile;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class TestCacheVolatile {
	
	
	public static class Tombola extends Thread {
		
		volatile int nrExtras;
		int nrIteratii;
		
		List<Integer> numereExtrase = new ArrayList<>();
		
		public Tombola(int nrIteratii) {
			this.nrIteratii = nrIteratii;
		}

		@Override
		public void run() {
			while(this.nrIteratii > 0) {
				this.nrIteratii--;
				//Random random  = new Random();
				//this.nrExtras = random.nextInt(50);
				
				this.nrExtras += 1; 
				this.numereExtrase.add(this.nrExtras);
				
				//System.out.println("Numarul extras este " + this.nrExtras);
			}
			
			System.out.println("Joc terminat");
			
			this.nrExtras = -1;
		}

		public int getNrExtras() {
			return nrExtras;
		}
		
		public boolean aFostExtras(int nrNorocos) {
			return this.numereExtrase.contains(nrNorocos);
		}
		
	}
	
	public static class Jucator extends Thread{
		String nume;
		int numarNorocos;
		Tombola tombola;
		
		public Jucator(String nume, int numarNorocos, Tombola tombola) {
			super();
			this.nume = nume;
			this.numarNorocos = numarNorocos;
			this.tombola = tombola;
		}

		@Override
		public void run() {
			
			int nrExtras = tombola.getNrExtras();
			
			while(nrExtras != -1 && ! tombola.aFostExtras(numarNorocos)) {
				nrExtras = tombola.getNrExtras();
			}
			
			if(tombola.aFostExtras(numarNorocos)) {
				System.out.println(this.nume + " a castigat un premiu");
			}
		}	
	}

	public static void main(String[] args) throws InterruptedException {
		
		Tombola tombola = new Tombola(100);
		Jucator alice = new Jucator("Alice", 3, tombola);
		Jucator john = new Jucator("John", 13, tombola);
		
		alice.start();
		john.start();
		tombola.start();
		
		alice.join();
		john.join();
		tombola.join();
		
	}

}

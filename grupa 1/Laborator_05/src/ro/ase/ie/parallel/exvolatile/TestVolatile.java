package ro.ase.ie.parallel.exvolatile;

import java.util.Random;

public class TestVolatile {
	
	
	public static class Tombola extends Thread {
		
		public static volatile int numarNorocos;
		private int nrIteratii;
		private int nrJucatori;
		private int nrConfirmari;
		
		public Tombola(int nrIteratii, int nrJucatori) {
			super();
			this.nrIteratii = nrIteratii;
			this.nrJucatori = nrJucatori;
			this.nrConfirmari = nrJucatori;
		}

		public int getNumarNorocos() {
			return numarNorocos;
		}
		
		public synchronized void confirma() {
			this.nrConfirmari += 1;
		}

		@Override
		public void run() {
			Random random = new Random();
			System.out.println("Start tombola");
			while(nrIteratii > 0) {
				//this.numarNorocos = random.nextInt(50);
				
				if(nrConfirmari >= nrJucatori) {
					System.out.println("Nr confirmari "+ nrConfirmari);
					this.numarNorocos += 1;
					//System.out.println("Numarul norocos este = " + this.numarNorocos);
					this.nrIteratii--;
					this.nrConfirmari = 0;
				}
			}
			this.numarNorocos = -1;
			System.out.println("Sfarsit joc");
		}	
	}
	
	public static class Jucator extends Thread{
		Tombola tombola;
		int numarJucator;
		int numarAnterior;
		String nume;
		
		public Jucator(Tombola tombola, int numarJucator, String nume) {
			super();
			this.tombola = tombola;
			this.numarJucator = numarJucator;
			this.nume = nume;
		}

		@Override
		public void run() {
			while(Tombola.numarNorocos != -1 && Tombola.numarNorocos != numarJucator) {
			//while(tombola.getNumarNorocos() != -1 && tombola.getNumarNorocos() != numarJucator) {
				if(Tombola.numarNorocos != numarAnterior) {
					tombola.confirma();
					this.numarAnterior = Tombola.numarNorocos;
				}
			}
			if(tombola.getNumarNorocos() == numarJucator) {
				System.out.println(this.nume + " a castigat un premiu");
			}
		}
	}

	public static void main(String[] args) {
		Tombola tombola = new Tombola(100, 2);
		Jucator alice = new Jucator(tombola,3,"Alice");
		Jucator john = new Jucator(tombola,13,"John");
		
		alice.start();
		john.start();
		tombola.start();
		
		System.out.println("Sfarsit joc");
	}

}

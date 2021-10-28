package ro.ase.ie.parallel.deadlock;

public class TestDeadlock {
	
	public static class Persoana {
		String nume;

		public Persoana(String nume) {
			this.nume = nume;
		}
		
		public synchronized void salut(Persoana prieten) {
			System.out.println(String.format("%s saluta pe %s", this.nume, prieten.nume));
			prieten.raspunsSalut(this);
		}
		
		public synchronized void raspunsSalut(Persoana persoana) {
			System.out.println(
					String.format("%s raspunde la Salut catre %s", this.nume, persoana.nume));
		}
	}
	
	public static class ThreadPersoana extends Thread {
		Persoana persoana;
		Persoana prieten;

		public ThreadPersoana(Persoana persoana, Persoana prieten) {
			super();
			this.persoana = persoana;
			this.prieten = prieten;
		}

		@Override
		public void run() {
			persoana.salut(prieten);
		}
	}

	public static void main(String[] args) throws InterruptedException {
		
		Persoana alice = new Persoana("Alice");
		Persoana john = new Persoana("John");
		
		ThreadPersoana t1 = new ThreadPersoana(alice, john);
		ThreadPersoana t2 = new ThreadPersoana(john, alice);
		
		t1.start();
		t2.start();
		
		t1.join();
		t2.join();
	
		System.out.println("Sfarsit exemplu");
		
	}

}

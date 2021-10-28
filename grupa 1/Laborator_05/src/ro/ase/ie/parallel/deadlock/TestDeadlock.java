package ro.ase.ie.parallel.deadlock;

public class TestDeadlock {
	
	public static class Persoana {
		String nume;

		public Persoana(String nume) {
			super();
			this.nume = nume;
		}
		
		public synchronized void salut(Persoana prieten) {
			System.out.println(String.format("%s spune Salut lui %s", this.nume, prieten.nume));
			prieten.raspundeSalut(this);
		}
		
		public synchronized void raspundeSalut(Persoana prieten) {
			System.out.println(
					String.format("%s raspunde cu Ce mai faci ? lui %s", prieten.nume, this.nume));
		}	
	}
	
	public static class ThreadPrieten extends Thread {
		Persoana persoana;
		Persoana prieten;

		public ThreadPrieten(Persoana persoana, Persoana prieten) {
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
		
		Thread tAlice = new ThreadPrieten(alice, john);
		Thread tJohn = new ThreadPrieten(john, alice);
		
		tAlice.start();
		tJohn.start();
		
		tAlice.join();
		tJohn.join();
		
		System.out.println("Sfarsit exemplu");
	}

}

package ro.ase.ie.parallel.solutie.paralela;

import java.util.concurrent.atomic.AtomicLong;

public class Contor {
	
	long valoare = 0;
	
	public synchronized void incrementare() {
		this.valoare += 1;
	}
	
	public long get() {
		return this.valoare;
	}

}

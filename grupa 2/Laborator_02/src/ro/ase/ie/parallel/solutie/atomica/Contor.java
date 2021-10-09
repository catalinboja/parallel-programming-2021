package ro.ase.ie.parallel.solutie.atomica;

import java.util.concurrent.atomic.AtomicLong;

public class Contor {
	
	AtomicLong valoare = new AtomicLong(0);
	
	public void incrementare() {
		this.valoare.incrementAndGet();
	}
	
	public long get() {
		return this.valoare.get();
	}

}

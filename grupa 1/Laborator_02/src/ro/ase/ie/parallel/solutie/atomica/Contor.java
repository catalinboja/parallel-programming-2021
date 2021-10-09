package ro.ase.ie.parallel.solutie.atomica;

import java.util.concurrent.atomic.AtomicLong;

public class Contor {
	
	AtomicLong contor = new AtomicLong(0);
	
	public void increment() {
		this.contor.incrementAndGet();
	}
	
	public long get() {
		return this.contor.get();
	}
}

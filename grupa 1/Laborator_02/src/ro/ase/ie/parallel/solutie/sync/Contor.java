package ro.ase.ie.parallel.solutie.sync;

import java.util.concurrent.atomic.AtomicLong;

public class Contor {
	
	long contor = 0;
	
	public void increment() {
		this.contor += 1;
	}
	
	public long get() {
		return this.contor;
	}
}

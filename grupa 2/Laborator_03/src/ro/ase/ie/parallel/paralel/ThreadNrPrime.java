package ro.ase.ie.parallel.paralel;

import ro.ase.ie.parallel.secvential.ContorNrPrime;

public class ThreadNrPrime extends Thread {
	
	long limitaInferioara;
	long limitaSuperioara;
	long nrPrime;
	long durata;
	
	public ThreadNrPrime(long limitaInferioara, long limitaSuperioara) {
		super();
		this.limitaInferioara = limitaInferioara;
		this.limitaSuperioara = limitaSuperioara;
	}

	public long getNrPrime() {
		return nrPrime;
	}

	public long getDurata() {
		return durata;
	}

	@Override
	public void run() {
		long tStart = System.currentTimeMillis();
		this.nrPrime = ContorNrPrime.getNrPrime(limitaInferioara, limitaSuperioara);
		long tFinal = System.currentTimeMillis();
		this.durata = tFinal - tStart;
	}

}

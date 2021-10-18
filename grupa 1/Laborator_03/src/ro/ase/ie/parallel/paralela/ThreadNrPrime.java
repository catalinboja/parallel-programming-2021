package ro.ase.ie.parallel.paralela;

import ro.ase.ie.parallel.secvential.ContorNrPrime;

public class ThreadNrPrime extends Thread{
	
	long limitaInferioara;
	long limitaSuperioara;
	long contor = 0;
	double durata = 0;
	
	

	public ThreadNrPrime(long limitaInferioara, long limitaSuperioara) {
		super();
		this.limitaInferioara = limitaInferioara;
		this.limitaSuperioara = limitaSuperioara;
	}

	@Override
	public void run() {	
		double tStart = System.currentTimeMillis();
		this.contor = ContorNrPrime.getNrPrime(limitaInferioara, limitaSuperioara);	
		double tFinal = System.currentTimeMillis();
		this.durata = (tFinal - tStart)/1000.0;
	}

	public long getContor() {
		return contor;
	}

	public double getDurata() {
		return durata;
	}

}

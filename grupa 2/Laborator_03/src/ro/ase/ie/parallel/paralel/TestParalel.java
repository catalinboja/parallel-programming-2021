package ro.ase.ie.parallel.paralel;

import ro.ase.ie.parallel.Util;

public class TestParalel {

	public static void main(String[] args) throws InterruptedException {
		
		System.out.println("Test solutie paralela cu intervale egale");
		
		int nrProcesoare = Runtime.getRuntime().availableProcessors();
		System.out.println("Nr procesoare: " + nrProcesoare);
		
		long interval = Util.LIMITA / nrProcesoare;
		
		Thread fireExecutie[] = new Thread[nrProcesoare];
		
			
		for(int i = 0; i < nrProcesoare; i++) {
			long limitaInferioara = i*interval;
			long limitaSuperioara = (i == nrProcesoare-1) ? Util.LIMITA : (i+1)*interval;
			fireExecutie[i] = new ThreadNrPrime(limitaInferioara, limitaSuperioara);
		}
		
		long tStart = System.currentTimeMillis();
		
		for(Thread t : fireExecutie) {
			t.start();
		}
		
		for(Thread t : fireExecutie) {
			t.join();
		}
		
		long tFinal = System.currentTimeMillis();
		
		int nrPrime = 0;
		for(Thread t : fireExecutie) {
			ThreadNrPrime tPrime = (ThreadNrPrime) t;
			nrPrime += tPrime.getNrPrime();
			System.out.println("Durata thread = " + tPrime.getDurata()/1000.0);
		}
		
		System.out.println(String.format(
				"Rezultat = %d cu durata %f",
				nrPrime,
				(tFinal-tStart)/1000.0
				));
		
	}

}

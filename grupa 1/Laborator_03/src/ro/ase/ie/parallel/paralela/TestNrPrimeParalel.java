package ro.ase.ie.parallel.paralela;

import javax.swing.UIDefaults.LazyInputMap;

import ro.ase.ie.parallel.Util;

public class TestNrPrimeParalel {

	public static void main(String[] args) throws InterruptedException {
		
		System.out.println("Test paralel cu intervale egale");
		
		int nrProcesoare = Runtime.getRuntime().availableProcessors();
		Thread[] fireExecutie = new Thread[nrProcesoare];
		
		long interval = Util.LIMITA / nrProcesoare;
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
		
		long nrPrime = 0;
		for(Thread t : fireExecutie) {
			nrPrime += ((ThreadNrPrime)t).getContor();
			System.out.println("Durata thread = " + ((ThreadNrPrime)t).getDurata());
		}
		System.out.println(String.format(
				"Rezultat = %d cu durata %f",
				nrPrime,
				(tFinal - tStart)/1000.0
				));
		
		
	}

}

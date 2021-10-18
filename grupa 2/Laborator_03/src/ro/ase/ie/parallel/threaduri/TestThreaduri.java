package ro.ase.ie.parallel.threaduri;

import ro.ase.ie.parallel.Util;

public class TestThreaduri {

	public static void main(String[] args) throws InterruptedException {
		
		System.out.println("Test solutie paralela cu mai multe thread-uri");
		
		int nrProcesoare = Runtime.getRuntime().availableProcessors();
		System.out.println("Nr procesoare: " + nrProcesoare);
		
		Thread fireExecutie[] = new Thread[nrProcesoare];
		
		long nrPrime = 0;
		
		long tStart = System.currentTimeMillis();
		
		for(long i = 0; i < Util.LIMITA / nrProcesoare; i++) {
			for(int j = 0; j < nrProcesoare; j++) {
				fireExecutie[j] = new ThreadVerificarePrim(i*nrProcesoare + j);
				fireExecutie[j].start();
			}
			for(int j = 0; j < nrProcesoare; j++) {
				fireExecutie[j].join();
			}
			for(int j = 0; j < nrProcesoare; j++) {
				nrPrime += ((ThreadVerificarePrim)fireExecutie[j]).getRezultat();
			}
		}
		
		long nrRamase = (Util.LIMITA % nrProcesoare);
		
		for(int j = 0; j < nrRamase; j++) {
				fireExecutie[j] = new ThreadVerificarePrim(Util.LIMITA - nrRamase + j);
				fireExecutie[j].start();
		}
		for(int j = 0; j < nrRamase; j++) {
				fireExecutie[j].join();
		}
		for(int j = 0; j < nrRamase; j++) {
				nrPrime += ((ThreadVerificarePrim)fireExecutie[j]).getRezultat();
		}
		
		long tFinal = System.currentTimeMillis();
		
		System.out.println(String.format(
				"Rezultat = %d cu durata %f",
				nrPrime,
				(tFinal-tStart)/1000.0
				));
		
	}

}

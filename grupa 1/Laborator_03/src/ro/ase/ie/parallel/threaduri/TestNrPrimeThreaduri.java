package ro.ase.ie.parallel.threaduri;

import ro.ase.ie.parallel.Util;
import ro.ase.ie.parallel.paralela.ThreadNrPrime;

public class TestNrPrimeThreaduri {

	public static void main(String[] args) throws InterruptedException {
		
		
		System.out.println("Test cu mai multe thread-uri create pentru fiecare numar");
		
		long nrPrime = 0;
		
		int nrProcesoare = Runtime.getRuntime().availableProcessors();
		Thread fireExecutie[] = new Thread[nrProcesoare];
		
		long tStart = System.currentTimeMillis();
		
		for(long i = 0; i < Util.LIMITA/nrProcesoare; i++) {
			for(int j = 0 ; j < nrProcesoare; j++) {
				fireExecutie[j] = new ThreadVerificareNumar(nrProcesoare*i+j);
				fireExecutie[j].start();
			}
			for(Thread t : fireExecutie) {
				t.join();
			}
			for(Thread t : fireExecutie) {
				nrPrime += ((ThreadVerificareNumar)t).getRezultat();
				
			}
		}
		
		for(long i = Util.LIMITA - (Util.LIMITA % nrProcesoare); i < Util.LIMITA; i++) {
			for(int j = 0 ; j < nrProcesoare; j++) {
				fireExecutie[j] = new ThreadVerificareNumar(nrProcesoare*i+j);
				fireExecutie[j].start();
			}
			for(Thread t : fireExecutie) {
				t.join();
			}
			for(Thread t : fireExecutie) {
				nrPrime += ((ThreadVerificareNumar)t).getRezultat();
				System.out.println(nrPrime);
			}
		}
		
		long tFinal = System.currentTimeMillis();
		System.out.println(String.format(
				"Rezultat = %d cu durata %f",
				nrPrime, (tFinal - tStart)/1000.0
				));
	}

}

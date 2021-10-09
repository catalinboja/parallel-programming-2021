package ro.ase.ie.parallel.solutie.paralela;

import java.util.ArrayList;
import java.util.List;

public class TestParalel {

	public static void main(String[] args) throws InterruptedException {

		System.out.println("Test solutie paralela");
		
		final long LIMITA = (long) 1e10;
		
		List<Thread> fireExecutie = new ArrayList<>();
		
		int nrProcesoare = Runtime.getRuntime().availableProcessors();
		
		//int nrProcesoare = 40000;
		
		System.out.println("Nr procesoare  = " + nrProcesoare);
		
		Contor contor = new Contor();
		long interval = LIMITA / nrProcesoare;
		
		for(int i = 0; i < nrProcesoare; i++) {
			long limitaInferioara = i*interval;
			long limitaSuperioara = (i == nrProcesoare - 1) ? LIMITA : (i+1)*interval;
			fireExecutie.add(
					new ThreadNrValoriPare(contor, limitaInferioara, limitaSuperioara));
		}
		
		double tStart = System.currentTimeMillis();
		
		for(Thread t : fireExecutie) {
			t.start();
		}
		
		for(Thread t : fireExecutie) {
			t.join();
		}
		
		double tFinal = System.currentTimeMillis();
		
		System.out.println(String.format("Rezultat  = %d cu durata de %f s",
				contor.get(), (tFinal - tStart)/1000));
		
		for(Thread t : fireExecutie) {
			ThreadNrValoriPare thread = (ThreadNrValoriPare) t;
			System.out.println("Durata thread = " + thread.durata);
		}
		
	}

}

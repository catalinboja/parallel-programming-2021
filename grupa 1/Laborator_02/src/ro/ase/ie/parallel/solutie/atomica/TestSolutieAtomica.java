package ro.ase.ie.parallel.solutie.atomica;

import java.util.ArrayList;
import java.util.List;

public class TestSolutieAtomica {

	public static void main(String[] args) throws InterruptedException {
		
		final long LIMITA = (long)1e10;
		
		int nrProcesoare = Runtime.getRuntime().availableProcessors();
		
		System.out.println("Test pe " + nrProcesoare + " procesoare");
		
		List<Thread> fireExecutie = new ArrayList<>();
		
		long interval = LIMITA / nrProcesoare;
		Contor contor = new Contor();
		
		for(int i = 0; i < nrProcesoare; i++) {
			long limitaInferioara = i*interval;
			long limitaSuperioara = (i == nrProcesoare-1) ? LIMITA : (i+1)*interval;
			Thread t = new ThreadContor(contor, limitaInferioara, limitaSuperioara);
			fireExecutie.add(t);
		}
		
		double tStart = System.currentTimeMillis();
		
		for(Thread t : fireExecutie) {
			t.start();
		}
		
		for(Thread t : fireExecutie) {
			t.join();
		}
		
		double tFinal = System.currentTimeMillis();
		
		System.out.println(String.format("Nr valori pare = %d. Durata %f s", 
				contor.get(), (tFinal - tStart)/1000));
		
		for(Thread t : fireExecutie) {
			ThreadContor thread = (ThreadContor) t;
			System.out.println("Durata thread = " + thread.durata);
		}
	}
		
}


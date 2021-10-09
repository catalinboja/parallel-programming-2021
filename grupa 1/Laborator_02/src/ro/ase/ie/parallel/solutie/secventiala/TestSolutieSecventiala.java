package ro.ase.ie.parallel.solutie.secventiala;

public class TestSolutieSecventiala {

	public static void main(String[] args) {
		
		final long LIMITA = (long)1e10;
		
		System.out.println("Test solutie secventiala");
		
		for(int i =0 ; i < 5; i++) {
		
		double tStart = System.currentTimeMillis();
				
		long nrValoriPare = SolutieSecventiala.getNumarValoriPare(0, LIMITA);
		
		double tFinal = System.currentTimeMillis();
		
		System.out.println(String.format("Nr valori pare = %d. Durata %f s", 
				nrValoriPare, (tFinal - tStart)/1000));
		}
	}

}

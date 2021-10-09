package ro.ase.ie.parallel.solutie.secventiala;

public class TestSecvential {

	public static void main(String[] args) {
		
		System.out.println("Test secvential");
		
		final long LIMITA = (long) 1e10;
		
		for(int i = 0; i < 5; i++) {
		
		double tStart = System.currentTimeMillis();
		
		long nrValoriPare = ContorNrPareSecvential.getNrValoriPare(0, LIMITA);
		
		double tFinal = System.currentTimeMillis();
		
		System.out.println(String.format("Rezultat  = %d cu durata de %f s",
				nrValoriPare, (tFinal - tStart)/1000));
		}
	}

}

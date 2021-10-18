package ro.ase.ie.parallel.secvential;

import ro.ase.ie.parallel.Util;

public class TestSecvential {

	public static void main(String[] args) {
		
		System.out.println("Test solutie secventiala ");
		
		long tStart = System.currentTimeMillis();
		
		long nrPrime = ContorNrPrime.getNrPrime(0, Util.LIMITA);
		
		long tFinal = System.currentTimeMillis();
		
		System.out.println(String.format(
				"Rezultat = %d cu durata %f",
				nrPrime,
				(tFinal-tStart)/1000.0
				));
	}

}

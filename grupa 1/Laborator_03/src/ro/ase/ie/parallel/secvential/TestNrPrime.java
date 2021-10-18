package ro.ase.ie.parallel.secvential;

import ro.ase.ie.parallel.Util;

public class TestNrPrime {

	public static void main(String[] args) {
		
		System.out.println("Test secvential");
		
		long tStart = System.currentTimeMillis();
		
		long nrPrime = ContorNrPrime.getNrPrime(0, Util.LIMITA);
		
		long tFinal = System.currentTimeMillis();
		
		double durata = (tFinal-tStart)/1000.0;
		System.out.println(String.format(
				"Rezultat = %d cu durata %f",
				nrPrime,
				durata
				));
		
		
	}

}

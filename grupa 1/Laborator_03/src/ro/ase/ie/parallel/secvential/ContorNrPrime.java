package ro.ase.ie.parallel.secvential;

public class ContorNrPrime {
	public static long getNrPrime(long limitaInferioara, long limitaSuperioara) {
		long contor = 0;
		for(long i  = limitaInferioara; i < limitaSuperioara; i++) {
			boolean estePrim = true;
			for(long j = 2; j < i/2; j++) {
				if(i % j == 0) {
					estePrim = false;
					break;
				}
			}
			
			if(estePrim) 
				contor += 1;
		}
		
		return contor;
	}
}

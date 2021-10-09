package ro.ase.ie.parallel.solutie.secventiala;

public class SolutieSecventiala {
	
	public static long getNumarValoriPare(long limitaInferioara, long limitaSuperioara) {
		long contor = 0;
		for(long i = limitaInferioara; i < limitaSuperioara; i++) {
			if(i % 2 == 0) {
				contor += 1;
			}
		}
		return contor;
	}

}

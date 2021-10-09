package ro.ase.ie.parallel.solutie.atomica;

public class ThreadNrValoriPare extends Thread{
	
	Contor contor;
	long limitaInferioara;
	long limitaSuperioara;
	
	public double durata;
		
	public ThreadNrValoriPare(Contor contor, long limitaInferioara, long limitaSuperioara) {
		super();
		this.contor = contor;
		this.limitaInferioara = limitaInferioara;
		this.limitaSuperioara = limitaSuperioara;
	}

	@Override
	public void run() {
	
		double tStart = System.currentTimeMillis();
		for(long i = limitaInferioara; i < limitaSuperioara; i++) {
			if(i % 2 == 0) {
				contor.incrementare();
			}
		}
		double tFinal = System.currentTimeMillis();
		this.durata = (tFinal - tStart)/1000;
	}
	
	
	

}

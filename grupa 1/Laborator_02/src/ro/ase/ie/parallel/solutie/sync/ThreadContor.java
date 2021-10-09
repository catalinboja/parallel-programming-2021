package ro.ase.ie.parallel.solutie.sync;

public class ThreadContor extends Thread{
	
	Contor contor;
	long limitaInferioara;
	long limitaSuperioara;
	public long durata = 0;

	
	public ThreadContor(Contor contor, long limitaInferioara, long limitaSuperioara) {
		super();
		this.contor = contor;
		this.limitaInferioara = limitaInferioara;
		this.limitaSuperioara = limitaSuperioara;
	}


	@Override
	public void run() {
		long tStart = System.currentTimeMillis();
		for(long i = limitaInferioara; i < limitaSuperioara; i++) {
			if(i % 2 == 0) {
				contor.increment();
			}
		}
		long tFinal = System.currentTimeMillis();
		this.durata = tFinal-tStart;
	}
}

package ro.ase.ie.parallel;

public class Test {
	
	
	static class CustomThread extends Thread {
		
		@Override
		public void run() {			
			try {
				Thread.sleep(2000);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
			System.out.println("Custom Hello");		
		}
	}
	
	static class RunnableThread implements Runnable {

		@Override
		public void run() {
			
			try {
				Thread.sleep(1000);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
			System.out.println("Special Hello");
		}	
	}

	public static void main(String[] args) throws InterruptedException {
		
		System.out.println("Start test");
		
		Thread customThread = new CustomThread();
		Thread runnableThread = new Thread(new RunnableThread());
		
		//apel secvential
		//customThread.run();
		//apel secvential
		//runnableThread.run();
		
		customThread.start();
		runnableThread.start();
		
		//definim o bariera pentru thread-urile secundare
		customThread.join();
		runnableThread.join();
		
		
		//simulare race-condition
		ContBancar contBancar = new ContBancar(1000);
		Thread tSot = new Thread(new ThreadCard(contBancar, "John"));
		Thread tSotie = new Thread(new ThreadCard(contBancar, "Alice"));
		
		tSotie.start();
		tSot.start();
		
		tSotie.join();
		tSot.join();
		
		
		System.out.println("Hello");
		
	}
	
	

}

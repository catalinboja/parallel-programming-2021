package ro.ase.ie.parallel;

public class Test {
	
	public static class CustomThread extends Thread {
		
		@Override
		public void run() {
			
			try {
				Thread.sleep(2000);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
			
			System.out.println("Custom Hello");		
		}
	}
	
	public static class RunnableThread implements Runnable{

		@Override
		public void run() {
			
			try {
				Thread.sleep(1000);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
			System.out.println("Runnable Hello");
			
		}
		
	}

	public static void main(String[] args) throws InterruptedException {
		
		System.out.println("Start test");
		
		CustomThread t1 = new CustomThread();
		Thread t2 = new Thread(new RunnableThread());
		
		//apel secvential
		//t1.run();
		//t2.run();
		
		t1.start();
		t2.start();
		
		
		//bariera prin care sincronizeaza thread-urile secundare cu main thread
		t1.join();
		t2.join();
		
		//race condition
		
		ContBancar cont = new ContBancar(1000);
		
		Thread tSot = new Thread(new Card(cont, "Gigel"));
		Thread tSotie = new Thread(new Card(cont, "Ana"));
		
		tSotie.start();
		tSot.start();
		
		tSotie.join();
		tSot.join();
		
		
		System.out.println("Bye");

	}
}

package ro.ase.ie.parallel;

import java.util.Random;

public class TestMinim {
	
	//metoda ce trebuie folosita pentru a compara 2 valori
	static boolean esteMaiMic(int a, int b) {
		int rez = 0;

		for(int i = 0 ; i< 1600; i++) {
			float temp = (float)a/i;
			rez += (int) temp;
		}
		
		for(int i = 0 ; i< 1600; i++) {
			float temp = (float)a/i;
			rez += (int) temp;
		}
		
		return (a <= b);
	}
	
	static int getMinim(int[] valori) {
		int minim = valori[0];
		for(int valoare : valori) {
			if(esteMaiMic(valoare, minim)) {
				minim = valoare;
			}
		}
		return minim;
	}

	public static void main(String[] args) {
		
		int nrProcesoare = Runtime.getRuntime().availableProcessors();
		System.out.println("Nr procesoare: " + nrProcesoare);
		
		final int LIMITA = 10000;
		int nrElemente = (int) 1e8;
		int[] valori = new int[nrElemente];
		int[] valoriSortateDesc = new int[nrElemente];
		
		
		System.out.println("Generare valori random...");
		
		//generam valorile random
		Random random = new Random(1000);
		for(int i = 0; i < nrElemente; i++) {
			valori[i] = random.nextInt(LIMITA);
			valoriSortateDesc[i] = nrElemente - i;
		}
		
		System.out.println("Start teste");
		
		//pentru fiecare vector de valori
		//benchmark solutie secventiala determinare minim
		//benchmark solutie paralela cu minim partajat (se poate folosi synchronized sau un tip atomic)
		//benchmark solutie paralela fara orchestrare si fara a sincroniza firele de executie - se vor folosi toate core-urile 
		
		long tStart = System.currentTimeMillis();
		
		int minim = getMinim(valori);
		
		long tFinal = System.currentTimeMillis();
		
		System.out.println("Minim = " + minim);
		System.out.println("Durata varianta secventiala - secventa random " + (tFinal- tStart));
		
		tStart = System.currentTimeMillis();
		
		minim = getMinim(valoriSortateDesc);
		
		tFinal = System.currentTimeMillis();
		
		System.out.println("Minim = " + minim);
		System.out.println("Durata varianta secventiala - secventa desc " + (tFinal- tStart));
			
	}

}
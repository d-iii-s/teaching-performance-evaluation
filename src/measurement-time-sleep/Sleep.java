import java.util.Random;

public class Sleep {
	public static final int LOOPS = 1000;

	public static volatile int dummy = 0;

	public static void main (String args []) throws InterruptedException {

		Random generator = new Random ();

		System.out.println ("loop,sleep,time");
		for (int i = 0; i < LOOPS; i++) {
			for (int ns = 0; ns < 1000*1000*2; ns += 100000) {

				dummy = generator.nextInt (65536);
				while (dummy > 0) dummy --;

				int nanos = ns % (1000 * 1000);
				int millis = ns / (1000 * 1000);

				long start = System.nanoTime ();
				Thread.sleep (millis, nanos);
				long end = System.nanoTime ();

				System.out.printf ("%d,%d,%d\n", i, ns, end - start);
			}
		}
	}
}

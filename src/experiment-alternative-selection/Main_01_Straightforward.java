public class Main_01_Straightforward {

	static int N = 1000000;

	public static void main (String[] params) {

		if (params.length == 1) {
			N = Integer.parseInt (params[0]);
		}

		BenchIface b1 = new BenchImpl1 ();
		long time1 = java.lang.System.nanoTime ();
		for (int i = 0 ; i < N ; i++) {
			b1.method (i);
		}
		time1 = java.lang.System.nanoTime () - time1;

		BenchIface b2 = new BenchImpl2 ();
		long time2 = java.lang.System.nanoTime ();
		for (int i = 0; i < N; i++) {
			b2.method (i);
		}
		time2 = java.lang.System.nanoTime () - time2;

		System.out.println ("One: " + time1);
		System.out.println ("Two: " + time2);
	}
}

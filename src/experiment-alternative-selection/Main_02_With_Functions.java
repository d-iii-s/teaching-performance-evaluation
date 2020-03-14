public class Main_02_With_Functions {

	private static long test1 (int N) {
		BenchIface b1 = new BenchImpl1 ();
		long time = System.nanoTime ();
		for (int i = 0; i < N; i++) {
			b1.method (i);
		}
		return (System.nanoTime () - time);
	}

	private static long test2 (int N) {
		BenchIface b2 = new BenchImpl2 ();
		long time = System.nanoTime ();
		for (int i = 0; i < N; i++) {
			b2.method (i);
		}
		return (System.nanoTime () - time);
	}

	static int N = 1000000;

	public static void main (String[] params) {

		if (params.length == 1) {
			N = Integer.parseInt (params[0]);
		}

		long time1 = test1 (N);
		long time2 = test2 (N);

		System.out.println ("One: " + time1);
		System.out.println ("Two: " + time2);
	}
}

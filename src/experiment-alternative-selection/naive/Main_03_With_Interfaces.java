public class Main_03_With_Interfaces {

	static int N = 1000000;

	private static long test (BenchIface b) {
		long time = System.nanoTime ();
		for (int i = 0 ; i < N ; i++) {
			b.method (i);
		}
		return (System.nanoTime () - time);
	}

	public static void main (String[] params) {

		if (params.length == 1) {
			N = Integer.parseInt (params[0]);
		}

		long time1 = test (new BenchImpl1 ());
		long time2 = test (new BenchImpl2 ());

		System.out.println ("One: " + time1);
		System.out.println ("Two: " + time2);
	}
}
